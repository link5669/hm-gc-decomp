cmake_minimum_required(VERSION 3.16)
project(hmgpu CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# Standalone build defines the same static SDL2 interface target as native/CMakeLists.txt.
if(NOT TARGET sdl2static)
  set(SDL2_ROOT /home/mi/Decomp/ref/sdl2 CACHE PATH "static SDL2 install")
  add_library(sdl2static INTERFACE)
  target_include_directories(sdl2static INTERFACE ${SDL2_ROOT}/include/SDL2)
  target_link_libraries(sdl2static INTERFACE ${SDL2_ROOT}/lib/libSDL2.a /usr/lib/x86_64-linux-gnu/libasound.so.2 pthread dl m)
endif()

add_library(hmgpu STATIC gpu.cpp fifo.cpp regs.cpp render.cpp shadergen.cpp texcodec.cpp texcache.cpp capture.cpp)
target_include_directories(hmgpu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# only SDL headers are needed (SDL_GL_GetProcAddress); the final executable links SDL itself
target_include_directories(hmgpu PRIVATE $<TARGET_PROPERTY:sdl2static,INTERFACE_INCLUDE_DIRECTORIES>)
target_compile_options(hmgpu PRIVATE -Wall -Wno-unused-function)

# texture decode unit test (codec only, no GL)
add_executable(test_texdec tests/test_texdec.cpp texcodec.cpp)
target_include_directories(test_texdec PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(gxplay tools/gxplay.cpp)
target_link_libraries(gxplay PRIVATE hmgpu sdl2static)

add_executable(gxsynth tools/gxsynth.cpp)
