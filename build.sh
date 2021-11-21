#!/bin/sh

#    -Werror -Wno-pointer-sign -Wno-int-conversion -lSDL -lGL --pre-js reftest.js -s GL_TESTING
#emcc -Werror -Wno-pointer-sign -Wno-int-conversion -Os -lGL -lSDL -s USE_PTHREADS=1 sdl_audio_beep_sleep.cpp -o 1A_sdl_audio_beep_sleep.html
emcc -Werror -Wno-pointer-sign -Wno-int-conversion -Os -s ASSERTIONS -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s DISABLE_EXCEPTION_CATCHING=0 -profiling -s SAFE_HEAP -lGL -lSDL -s ASYNCIFY sdl_audio_beep_sleep.cpp -o 1A_sdl_audio_beep_sleep.html
# -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js ./tests/browser_reporting.js -I./tests -include ./tests/report_result.h ./tests/report_result.cpp
