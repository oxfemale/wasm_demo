# wasm_demo
wasm_demo marion intro, StarWars blackstar outro
Web graphic demo with pc speaker beep music
Detect hardware, run background video/audio layers and play intro
Part 1 Playing Mario Music
Part 2 Playing StarWars Music
used DSL wasm, WebGL, cpp, js, html, stdc11++
brew + emsdk + vi

build types:
.z00mba/emcc -Werror -Wno-pointer-sign -Wno-int-conversion -O2 -s INITIAL_MEMORY=16MB -lSDL -lGL ./tests/sdl_alloctext.c -o ./tests/1A_sdl_alloctext.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js ./tests/browser_reporting.js -I./tests -include ./tests/report_result.h ./tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s SINGLE_FILE --proxy-to-worker -s GL_TESTING ./tests/single_file_static_initializer.cpp -o ./tests/1A_single_file_static_initializer.html


./emcc -Werror -Wno-pointer-sign -Wno-int-conversion ./tests/browser_test_hello_world.c -o ./tests/1A_browser_test_hello_world.html --proxy-to-worker -s SINGLE_FILE -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js ./tests/browser_reporting.js -I./tests -include ./tests/report_result.h ./tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -Os -s ASSERTIONS -s DISABLE_EXCEPTION_CATCHING=0 -profiling -s SAFE_HEAP -lSDL -s ASYNCIFY ./tests/sdl_audio_beep_sleep.cpp -o ./tests/1A_sdl_audio_beep_sleep.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js ./tests/browser_reporting.js -I./tests -include ./tests/report_result.h ./tests/report_result.cpp


./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -lSDL -lGL --pre-js reftest.js -s GL_TESTING ./tests/sdl_canvas_alpha.c -o ./tests/1A_sdl_canvas_alpha.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js ./tests/browser_reporting.js -I./tests -include ./tests/report_result.h ./tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion --pre-js flag_0.js -lSDL -lGL --pre-js reftest.js -s GL_TESTING ./tests/sdl_canvas_alpha.c -o ./tests/1A_sdl_canvas_alpha.html


 -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp
ok

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -lSDL -lGL -s GL_TESTING ./tests/sdl_canvas_blank.c -o ./tests/A1_sdl_canvas_blank.html

 -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp
ok
./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -lSDL -lGL -s GL_TESTING ./tests/sdl_canvas_palette.c -o ./tests/1A_sdl_canvas_palette.html

 -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp


./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s GL_TESTING ./tests/hello_world_sdl.cpp -o ./tests/1A_hello_world_sdl.html




./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s USE_SDL=2 ./tests/sdl2_canvas_write.cpp -o ./tests/1A_sdl2_canvas_write.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js ./tests/browser_reporting.js -I./tests -include ./tests/report_result.h ./tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion --preload-file cursor.bmp -s USE_SDL=2 ./tests/sdl2_custom_cursor.c -o ./tests/A1sdl2_custom_cursor.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp



./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s LEGACY_GL_EMULATION -s USE_SDL=2  -s GL_TESTING ./tests/sdl2_glclipplane_gllighting.c -o ./tests/1Asdl2_glclipplane_gllighting.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s LEGACY_GL_EMULATION -s USE_SDL=2 -s GL_TESTING ./tests/sdl2_gldrawelements.c -o ./tests/1Asdl2_gldrawelements.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s LEGACY_GL_EMULATION -s USE_SDL=2 -s GL_TESTING ./tests/sdl2_glmatrixmode_texture.c -o ./tests/1Asdl2_glmatrixmode_texture.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion --preload-file pudinha.mp3 -DSOUND_PATH="pudinha.mp3" -DFLAGS=MIX_INIT_MP3 -s USE_SDL=2 -s USE_SDL_MIXER=2 -s SDL2_MIXER_FORMATS=["mp3"] -s INITIAL_MEMORY=33554432 /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/sdl2_mixer_music.c -o ./tests/1Asdl2_mixer_music.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/emcc -Werror -Wno-pointer-sign -Wno-int-conversion --preload-file alarmvictory_1.ogg -DSOUND_PATH="alarmvictory_1.ogg" -DFLAGS=MIX_INIT_OGG -s USE_SDL=2 -s USE_SDL_MIXER=2 -s SDL2_MIXER_FORMATS=["ogg"] -s INITIAL_MEMORY=33554432 /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/sdl2_mixer_music.c -o /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/1Asdl2_mixer_music.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/emcc -Werror -Wno-pointer-sign -Wno-int-conversion --preload-file the_entertainer.wav -DSOUND_PATH="/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/sounds/" -DFLAGS=0 -s USE_SDL=2 -s USE_SDL_MIXER=2 -s "SDL2_MIXER_FORMATS=[]" -s INITIAL_MEMORY=33554432 /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/sdl2_mixer_music.c -o /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/1Asdl2_mixer_music.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

est_sdl2_mixer_wav_dash_s (test_browser.browser) ... Not clearing existing test directory
shared:DEBUG: successfully executed /Users/z00mba/etc/wasm/emsdk/upstream/emscripten

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion --preload-file /Users/z00mba/etc/wasm/test/emscripten/tests/sound.wav -s INITIAL_MEMORY=33554432 -s USE_SDL=2 -s USE_SDL_MIXER=2 /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/sdl2_mixer_wav.c -o /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/1Asdl2_mixer_wav.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp




./emcc -Werror -Wno-pointer-sign -Wno-int-conversion /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/manual_wasm_instantiate.cpp -o /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/1Amanual_wasm_instantiate.html -fsanitize=address -s INITIAL_MEMORY=128MB -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s LEGACY_GL_EMULATION -lGL -lSDL /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/gl_matrix_identity.c -o /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/1Agl_matrix_identity.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp



_sdl1 (test_browser.browser) ... Not clearing existing test directory
shared:DEBUG: successfully executed /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/emcc -Werror -Wno-pointer-sign -Wno-int-conversion -lSDL -lGL --pre-js reftest.js -s GL_TESTING /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/hello_world_sdl.cpp -o test.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp
shared:DEBUG: successfully executed /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s USE_SDL -lGL --pre-js reftest.js -s GL_TESTING /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/hello_world_sdl.cpp -o test.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp
ok
test_sdl1_es6 (test_browser.browser) ... Not clearing existing test directory
shared:DEBUG: successfully executed /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/emcc -Werror -Wno-pointer-sign -Wno-int-conversion -s USE_SDL -lGL -s EXPORT_ES6 --pre-js reftest.js -s GL_TESTING /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/hello_world_sdl.cpp -o test.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp
ok
test_sdl1_in_emscripten_nonstrict_mode (test_browser.browser) ... Not clearing existing test directory
shared:DEBUG: successfully executed /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/emcc -Werror -Wno-pointer-sign -Wno-int-conversion --pre-js reftest.js -s GL_TESTING /Users/z00mba/etc/wasm/e

--shell-file /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/hello_world_gles_shell.html -s FULL_ES2=1 -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp
ok
test_glgears_deriv (test_browser.browser) ... Not clearing existing test directory
shared:DEBUG: successfully executed /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/emcc -Werror -Wno-pointer-sign -Wno-int-conversion -DHAVE_BUILTIN_SINCOS -lGL -lglut --pre-js reftest.js -s GL_TESTING /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/hello_world_gles_deriv.c -o test.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -DHAVE_BUILTIN_SINCOS -DLONGTEST -lGL -lglut -DANIMATE /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/hello_world_gles.c -o /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/1Ahello_world_gles.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

./emcc -Werror -Wno-pointer-sign -Wno-int-conversion -DHAVE_BUILTIN_SINCOS -DLONGTEST -lGL -lglut -DANIMATE --proxy-to-worker /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/hello_world_gles.c -o /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/1Ahello_world_gles.html -s IN_TEST_HARNESS -DEMTEST_PORT_NUMBER=8888 --pre-js /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/browser_reporting.js -I/Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests -include /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.h /Users/z00mba/etc/wasm/emsdk/upstream/emscripten/tests/report_result.cpp

