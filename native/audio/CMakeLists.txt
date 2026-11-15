cmake_minimum_required(VERSION 3.16)
project(hmaudio CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(HM_SDL2_ROOT "/home/mi/Decomp/ref/sdl2" CACHE PATH "SDL2 static install prefix")

add_library(hmaudio STATIC dsp.cpp ax.cpp ai.cpp)
target_include_directories(hmaudio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                   PRIVATE ${HM_SDL2_ROOT}/include/SDL2)
target_compile_definitions(hmaudio PRIVATE _REENTRANT)
target_compile_options(hmaudio PRIVATE -Wall -Wextra -Wno-unused-parameter -fno-strict-aliasing)
find_package(Threads REQUIRED)
# This SDL2 build links ALSA directly (PulseAudio is loaded dynamically); there may be no
# libasound.so dev symlink, so fall back to the runtime soname.
find_library(HM_ASOUND NAMES asound libasound.so.2)
if(NOT HM_ASOUND)
  set(HM_ASOUND /usr/lib/x86_64-linux-gnu/libasound.so.2)
endif()
target_link_libraries(hmaudio PUBLIC ${HM_SDL2_ROOT}/lib/libSDL2.a ${HM_ASOUND} Threads::Threads m ${CMAKE_DL_LIBS})

option(HMAUDIO_TESTS "Build the standalone audio test" ON)
if(HMAUDIO_TESTS)
  add_executable(audio_test test/audio_test.cpp)
  target_link_libraries(audio_test PRIVATE hmaudio)
  target_compile_definitions(audio_test PRIVATE
    HM_DSPCODE_C="${CMAKE_CURRENT_SOURCE_DIR}/../../src/sdk/DSPCode.c")
  enable_testing()
  add_test(NAME audio_test COMMAND audio_test ${CMAKE_CURRENT_BINARY_DIR}/audio_test.wav)
endif()
