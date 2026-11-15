/* Multiplayer mod: 2D overlay drawing with raw GX (bitmap text, boxes). */
#include "sdk_names.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "mp_draw.h"
#include "font.h"

static int s_quads;

void mp_draw_begin(void)
{
    Mtx44 proj;
    Mtx id;

    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    C_MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    id[0][0] = 1.0f; id[0][1] = 0.0f; id[0][2] = 0.0f; id[0][3] = 0.0f;
    id[1][0] = 0.0f; id[1][1] = 1.0f; id[1][2] = 0.0f; id[1][3] = 0.0f;
    id[2][0] = 0.0f; id[2][1] = 0.0f; id[2][2] = 1.0f; id[2][3] = -0.5f;
    GXLoadPosMtxImm(id, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumIndStages(0);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0, 0, 0, 0});
}

static void quad(f32 x, f32 y, f32 w, f32 h, u32 rgba)
{
    GXBegin(GX_QUADS, GX_VTXFMT7, 4);
    GXPosition3f32(x, y, 0.0f);         GXColor1u32(rgba);
    GXPosition3f32(x + w, y, 0.0f);     GXColor1u32(rgba);
    GXPosition3f32(x + w, y + h, 0.0f); GXColor1u32(rgba);
    GXPosition3f32(x, y + h, 0.0f);     GXColor1u32(rgba);
    GXEnd();
    s_quads++;
}

void mp_draw_box(f32 x, f32 y, f32 w, f32 h, u32 rgba)
{
    quad(x, y, w, h, rgba);
}

int mp_text_width(const char *s, f32 scale)
{
    int n = 0;
    while (*s++)
        n++;
    return (int)(n * MP_FONT_W * scale);
}

static void glyphs(f32 x, f32 y, const char *s, f32 scale, u32 rgba)
{
    for (; *s; s++, x += MP_FONT_W * scale) {
        int c = (u8)*s, row, col;
        const u8 *g;
        if (c < 32 || c > 126)
            c = '?';
        g = mp_font[c - 32];
        for (row = 0; row < MP_FONT_H; row++) {
            u8 bits = g[row];
            col = 0;
            while (bits) {
                /* merge horizontal runs of lit pixels into one quad */
                if (bits & 0x80) {
                    int run = 0;
                    while (bits & 0x80) {
                        run++;
                        bits <<= 1;
                    }
                    quad(x + col * scale, y + row * scale, run * scale, scale, rgba);
                    col += run;
                } else {
                    bits <<= 1;
                    col++;
                }
            }
        }
    }
}

void mp_draw_text(f32 x, f32 y, const char *s, f32 scale, u32 rgba)
{
    /* 1px dark outline for readability over the scene */
    glyphs(x - scale, y, s, scale, 0x000000C0);
    glyphs(x + scale, y, s, scale, 0x000000C0);
    glyphs(x, y - scale, s, scale, 0x000000C0);
    glyphs(x, y + scale, s, scale, 0x000000C0);
    glyphs(x, y, s, scale, rgba);
}

void mp_draw_text_centered(f32 cx, f32 y, const char *s, f32 scale, u32 rgba)
{
    mp_draw_text(cx - mp_text_width(s, scale) * 0.5f, y, s, scale, rgba);
}
