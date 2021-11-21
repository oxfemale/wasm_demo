// Compile demo & run howto:
// brew install emcc / apt install emcc
//
// emcc -Werror -Wno-pointer-sign -Wno-int-conversion -Os -s ASSERTIONS -s DISABLE_EXCEPTION_CATCHING=0 -profiling -s SAFE_HEAP -lSDL -s ASYNCIFY sdl_audio_beep_sleep.cpp -o 1A_sdl_audio_beep_sleep.html
// open html file in browser
//
// Demo example by eaS7 / NeuroAlice / Bytecodevm

#include <queue>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <emscripten/html5.h>
#include <SDL.h>
#include <assert.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static int test_thread(void *data);


#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

int Demowidth, Demoheight;
SDL_Surface *screen;
int lastRectY, lastRectX;

const int tone_duration = 1000;

struct BeepObject {
  double toneFrequency;
  int samplesLeft;
};

class Beeper {
private:
  double phase;
  int frequency;
  int numChannels;
  int mutedChannel;
public:
  bool error;
  Beeper(int frequency, int numChannels, int sdlAudioFormat);
  ~Beeper();
  void beep(double toneFrequency, int durationMSecs);
  template<typename T>
  void generateSamples(T *stream, int length);
  void wait();
  std::queue<BeepObject> beeps;
  int sdlAudioFormat;
};

void audio_callback(void*, Uint8*, int);
void drawRandomPixels2( ) ;

// Pre defined standard colors
SDL_Color  White =   {0xff, 0xff, 0xff, 0};
SDL_Color Black =   {   0,    0,    0, 0};
SDL_Color Red =     {0xff,    0,    0, 0};
SDL_Color Green =   {   0, 0xff,    0, 0};
SDL_Color Blue =    {   0,    0, 0xff, 0};
SDL_Color Yellow =  {0xff, 0xff,    0, 0};
SDL_Color Purple =  {0xff,    0, 0xff, 0};
SDL_Color Cyan =    {   0, 0xff, 0xff, 0};
SDL_Color Transparent =    {   0, 0, 0, 0};
SDL_Color TrackingColor = {0x55, 0xaa,    0, 0};
SDL_Color FocusColor    = {0x00, 0xff, 0x00, 0};
SDL_Color ShadowColor   = {   0,    0,   0, 0};
SDL_Color BackgroundColor = {0, 0, 0, 128};
SDL_Color TrackingBackgroundColor = {0x20, 0x20, 0x20, 128};

Beeper *beep = 0;
const int freqs[] = { 16000, 22050, 32000, 44100, 48000, 96000 };
const int channels[] = { 1, 2 };
const int sdlAudioFormats[] = { AUDIO_U8, AUDIO_S8 };

static void sdlError(const char *str);


void report_result(int result)
{
  if (result == 0) {
    printf("Test successful!\n");
  } else {
    printf("Test failed!\n");
  }
#ifdef REPORT_RESULT
  //REPORT_RESULT(result);
#endif
}

const char *emscripten_result_to_string(EMSCRIPTEN_RESULT result) {
  if (result == EMSCRIPTEN_RESULT_SUCCESS) return "EMSCRIPTEN_RESULT_SUCCESS";
  if (result == EMSCRIPTEN_RESULT_DEFERRED) return "EMSCRIPTEN_RESULT_DEFERRED";
  if (result == EMSCRIPTEN_RESULT_NOT_SUPPORTED) return "EMSCRIPTEN_RESULT_NOT_SUPPORTED";
  if (result == EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED) return "EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED";
  if (result == EMSCRIPTEN_RESULT_INVALID_TARGET) return "EMSCRIPTEN_RESULT_INVALID_TARGET";
  if (result == EMSCRIPTEN_RESULT_UNKNOWN_TARGET) return "EMSCRIPTEN_RESULT_UNKNOWN_TARGET";
  if (result == EMSCRIPTEN_RESULT_INVALID_PARAM) return "EMSCRIPTEN_RESULT_INVALID_PARAM";
  if (result == EMSCRIPTEN_RESULT_FAILED) return "EMSCRIPTEN_RESULT_FAILED";
  if (result == EMSCRIPTEN_RESULT_NO_DATA) return "EMSCRIPTEN_RESULT_NO_DATA";
  return "Unknown EMSCRIPTEN_RESULT!";
}

#define TEST_RESULT(x) if (ret != EMSCRIPTEN_RESULT_SUCCESS) printf("%s returned %s.\n", #x, emscripten_result_to_string(ret));


#define NUM_ELEMS(x) (sizeof(x)/sizeof((x)[0]))
int f = -1;
int c = 0;
int s = 0;
int met = 0;

template<typename T>
void Beeper::generateSamples ( T *stream, int length) {
    const int AMPLITUDE = (sizeof(T) == 2) ? 28000 : 120;
    const int offset = (sdlAudioFormat == AUDIO_U8) ? 120 : 0;
    int i = 0;

    printf("exec: Beeper::generateSamples()\n");

    length /= numChannels;
    while (i < length) {
      if (beeps.empty()) {
        memset(stream + numChannels*i, 0, sizeof(T)*numChannels*(length-i));
        return;
      }
      BeepObject& bo = beeps.front();

      // In Stereo tests, mute one of the channels to be able to distinguish that Stereo output works.
      if (bo.samplesLeft > tone_duration * frequency / 2 / 1000) {
        mutedChannel = 1;
      } else {
        mutedChannel = 0;
      }

      int samplesToDo = std::min(i + bo.samplesLeft, length);
      bo.samplesLeft -= samplesToDo - i;

      while (i < samplesToDo) {
        for(int j = 0; j < numChannels; ++j) {
          stream[numChannels*i+j] = (T)(offset + (int)(AMPLITUDE * std::sin(phase * 2 * M_PI / frequency)));
          if (numChannels > 1 && j == mutedChannel) {
            stream[numChannels*i+j] = 0;
          }
        }
        phase += bo.toneFrequency;
        i++;
      }
      if (bo.samplesLeft == 0) {
        beeps.pop();
      }
    }
}

static void sdlError(const char *str) 
{
    fprintf(stderr, "Error at %s: %s\n", str, SDL_GetError());
    //emscripten_force_exit(1);
}


Beeper::Beeper(int frequency_, int numChannels_, int sdlAudioFormat_) {
    phase = 0.0;
    mutedChannel = 1;
    error = false;

    //printf("exec: Beeper::Beeper()\n");

    SDL_AudioSpec desiredSpec;

    desiredSpec.freq = frequency_;
    desiredSpec.format = sdlAudioFormat_;
    desiredSpec.channels = numChannels_;
    desiredSpec.samples = 1024;
    desiredSpec.callback = audio_callback;
    desiredSpec.userdata = this;
    SDL_AudioSpec obtainedSpec;
    SDL_OpenAudio(&desiredSpec, &obtainedSpec);
    if (obtainedSpec.freq != desiredSpec.freq || obtainedSpec.format != desiredSpec.format
      || obtainedSpec.channels != desiredSpec.channels || obtainedSpec.samples != desiredSpec.samples) {
      SDL_CloseAudio();
      error = true;
      printf("exit?\n");
      return;
    }
    frequency = obtainedSpec.freq;
    numChannels = obtainedSpec.channels;
    sdlAudioFormat = obtainedSpec.format;
    SDL_PauseAudio(0);
}


Beeper::~Beeper() {
  SDL_CloseAudio();
}


void Beeper::beep(double toneFrequency, int durationMSecs) {
  printf("exec: Beeper::beep()\n");
    BeepObject bo;
    bo.toneFrequency = toneFrequency;
    bo.samplesLeft = durationMSecs * frequency / 1000;
    SDL_LockAudio();
    beeps.push(bo);
    SDL_UnlockAudio();
}


const char *SdlAudioFormatToString(int sdlAudioType) {
    switch(sdlAudioType) {
    case AUDIO_U8: return "AUDIO_U8";
    case AUDIO_S8: return "AUDIO_S8";
    case AUDIO_U16LSB: return "AUDIO_U16LSB";
    case AUDIO_U16MSB: return "AUDIO_U16MSB";
    case AUDIO_S16LSB: return "AUDIO_S16LSB";
    case AUDIO_S16MSB: return "AUDIO_S16MSB";
    default: return "(unknown)";
    }
}


static int test_thread(void *data) {
  //while(true) {
    //emscripten_sleep( 30 );
    //drawRandomPixels2( );
  //}
  return 1;
}


void nextTest(void *unused = 0) {
  printf("exec: nextTest()\n");

  ++f;
    if (f >= NUM_ELEMS(freqs)) {
      f = 0;
      ++c;
      if (c >= NUM_ELEMS(channels)) {
        c = 0;
        ++s;
        if (s >= NUM_ELEMS(sdlAudioFormats)) {

#ifdef __EMSCRIPTEN__
      emscripten_cancel_main_loop();
#ifdef REPORT_RESULT
      REPORT_RESULT(1);
#endif
#endif

          return;
        }
      }
    }

    

  double Hz = 440;
  beep = new Beeper(freqs[f], channels[c], sdlAudioFormats[s]);
  if (beep->error) {
    printf("FAILED to play beep for %d msecs at %d Hz tone with audio format %s, %d channels, and %d samples/sec.\n",
        tone_duration, (int)Hz, SdlAudioFormatToString(sdlAudioFormats[s]), channels[c], freqs[f]);
    nextTest();
    return;
  }

  emscripten_sleep(50);
  //drawRandomPixels2( );

  printf("Playing back a beep for %d msecs at %d Hz tone with audio format %s, %d channels, and %d samples/sec.\n",
      tone_duration, (int)Hz, SdlAudioFormatToString(sdlAudioFormats[s]), channels[c], freqs[f]);

   beep->beep(Hz, tone_duration);

  if(met == 0) {
      met = 1;
  	       beep->beep(330,100);emscripten_sleep(100);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(392,100);emscripten_sleep(700);
          beep->beep(196,100);emscripten_sleep(700);
          beep->beep(262,300);emscripten_sleep(300);
          beep->beep(196,300);emscripten_sleep(300);
          beep->beep(164,300);emscripten_sleep(300);
          beep->beep(220,300);emscripten_sleep(100);
          beep->beep(246,100);emscripten_sleep(300);
          beep->beep(233,200);
          beep->beep(220,100);emscripten_sleep(300);
          beep->beep(196,100);emscripten_sleep(150);
          beep->beep(330,100);emscripten_sleep(150);
          beep->beep(392,100);emscripten_sleep(150);
          beep->beep(440,100);emscripten_sleep(300);
          beep->beep(349,100);emscripten_sleep(100);
          beep->beep(392,100);emscripten_sleep(300);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(294,100);emscripten_sleep(100);
          beep->beep(247,100);emscripten_sleep(500);
          beep->beep(262,300);emscripten_sleep(300);
          beep->beep(196,300);emscripten_sleep(300);
          beep->beep(164,300);emscripten_sleep(300);
          beep->beep(220,300);emscripten_sleep(100);
          beep->beep(246,100);emscripten_sleep(300);
          beep->beep(233,200);
          beep->beep(220,100);emscripten_sleep(300);
          beep->beep(196,100);emscripten_sleep(150);
          beep->beep(330,100);emscripten_sleep(150);
          beep->beep(392,100);emscripten_sleep(150);
          beep->beep(440,100);emscripten_sleep(300);
          beep->beep(349,100);emscripten_sleep(100);
          beep->beep(392,100);emscripten_sleep(300);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(294,100);emscripten_sleep(100);
          beep->beep(247,100);emscripten_sleep(900);
          beep->beep(392,100);emscripten_sleep(100);
          beep->beep(370,100);emscripten_sleep(100);
          beep->beep(349,100);emscripten_sleep(100);
          beep->beep(311,100);emscripten_sleep(300);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(207,100);emscripten_sleep(100);
          beep->beep(220,100);emscripten_sleep(100);
          beep->beep(262,100);emscripten_sleep(300);
          beep->beep(220,100);emscripten_sleep(100);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(294,100);emscripten_sleep(500);
          beep->beep(392,100);emscripten_sleep(100);
          beep->beep(370,100);emscripten_sleep(100);
          beep->beep(349,100);emscripten_sleep(100);
          beep->beep(311,100);emscripten_sleep(300);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(523,100);emscripten_sleep(300);
          beep->beep(523,100);emscripten_sleep(100);
          beep->beep(523,100);emscripten_sleep(1100);
          beep->beep(392,100);emscripten_sleep(100);
          beep->beep(370,100);emscripten_sleep(100);
          beep->beep(349,100);emscripten_sleep(100);
          beep->beep(311,100);emscripten_sleep(300);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(207,100);emscripten_sleep(100);
          beep->beep(220,100);emscripten_sleep(100);
          beep->beep(262,100);emscripten_sleep(300);
          beep->beep(220,100);emscripten_sleep(100);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(294,100);emscripten_sleep(500);
          beep->beep(311,300);emscripten_sleep(300);
          beep->beep(296,300);emscripten_sleep(300);
          beep->beep(262,300);emscripten_sleep(1300);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(262,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(294,100);emscripten_sleep(300);
          beep->beep(330,200);emscripten_sleep(50);
          beep->beep(262,200);emscripten_sleep(50);
          beep->beep(220,200);emscripten_sleep(50);
          beep->beep(196,100);emscripten_sleep(700);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(262,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(294,100);emscripten_sleep(100);
          beep->beep(330,100);emscripten_sleep(700);
          beep->beep(440,100);emscripten_sleep(300);
          beep->beep(392,100);emscripten_sleep(500);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(262,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(294,100);emscripten_sleep(300);
          beep->beep(330,200);emscripten_sleep(50);
          beep->beep(262,200);emscripten_sleep(50);
          beep->beep(220,200);emscripten_sleep(50);
          beep->beep(196,100);emscripten_sleep(700);
          /*Intro*/
          beep->beep(330,100);emscripten_sleep(100);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(262,100);emscripten_sleep(100);
          beep->beep(330,100);emscripten_sleep(300);
          beep->beep(392,100);emscripten_sleep(700);
          beep->beep(196,100);emscripten_sleep(700);
          beep->beep(196,100);emscripten_sleep(125);
          beep->beep(262,100);emscripten_sleep(125);
          beep->beep(330,100);emscripten_sleep(125);
          beep->beep(392,100);emscripten_sleep(125);
          beep->beep(523,100);emscripten_sleep(125);
          beep->beep(660,100);emscripten_sleep(125);
          beep->beep(784,100);emscripten_sleep(575);
          beep->beep(660,100);emscripten_sleep(575);
          beep->beep(207,100);emscripten_sleep(125);
          beep->beep(262,100);emscripten_sleep(125);
          beep->beep(311,100);emscripten_sleep(125);
          beep->beep(415,100);emscripten_sleep(125);
          beep->beep(523,100);emscripten_sleep(125);
          beep->beep(622,100);emscripten_sleep(125);
          beep->beep(830,100);emscripten_sleep(575);
          beep->beep(622,100);emscripten_sleep(575);
          beep->beep(233,100);emscripten_sleep(125);
          beep->beep(294,100);emscripten_sleep(125);
          beep->beep(349,100);emscripten_sleep(125);
          beep->beep(466,100);emscripten_sleep(125);
          beep->beep(587,100);emscripten_sleep(125);
          beep->beep(698,100);emscripten_sleep(125);
          beep->beep(932,100);emscripten_sleep(575);
          beep->beep(932,100);emscripten_sleep(125);
          beep->beep(932,100);emscripten_sleep(125);
          beep->beep(932,100);emscripten_sleep(125);
          beep->beep(1046,675);
  }else{
      if(met != 4){
      met = 4;
          beep->beep(494, 250);
          beep->beep(523, 250);
          beep->beep(587, 500);
          beep->beep(523, 250);
          beep->beep(494, 250);
          beep->beep(440, 500);
      }else{
        met = 0;
        beep->beep(440,500);
        beep->beep(440,500);
        beep->beep(440,500);
        beep->beep(349,350);
        beep->beep(523,150);

        beep->beep(440,500);
        beep->beep(349,350);
        beep->beep(523,150);
        beep->beep(440,1000);

        beep->beep(659,500);
        beep->beep(659,500);
        beep->beep(659,500);
        beep->beep(698,350);
        beep->beep(523,150);

        beep->beep(415,500);
        beep->beep(349,350);
        beep->beep(523,150);
        beep->beep(440,1000);

        beep->beep(880,500);
        beep->beep(440,350);
        beep->beep(440,150);
        beep->beep(880,500);
        beep->beep(830,250);
        beep->beep(784,250);

        beep->beep(740,125);
        beep->beep(698,125);
        beep->beep(740,250);

        beep->beep(455,250);
        beep->beep(622,500);
        beep->beep(587,250);
        beep->beep(554,250);

        beep->beep(523,125);
        beep->beep(466,125);
        beep->beep(523,250);

        beep->beep(349,125);
        beep->beep(415,500);
        beep->beep(349,375);
        beep->beep(440,125);

        beep->beep(523,500);
        beep->beep(440,375);
        beep->beep(523,125);
        beep->beep(659,1000);

        beep->beep(880,500);
        beep->beep(440,350);
        beep->beep(440,150);
        beep->beep(880,500);
        beep->beep(830,250);
        beep->beep(784,250);

        beep->beep(740,125);
        beep->beep(698,125);
        beep->beep(740,250);

        beep->beep(455,250);
        beep->beep(622,500);
        beep->beep(587,250);
        beep->beep(554,250);

        beep->beep(523,125);
        beep->beep(466,125);
        beep->beep(523,250);

        beep->beep(349,250);
        beep->beep(415,500);
        beep->beep(349,375);
        beep->beep(523,125);

        beep->beep(440,500);
        beep->beep(349,375);
        beep->beep(261,125);
        beep->beep(440,1000);
      }
  }

}


void update() {
  //printf("exec: update()\n");
    SDL_LockAudio();
    int size = beep ? beep->beeps.size() : 0;
    SDL_UnlockAudio();
    if (size == 0 && beep) {
      delete beep;
      beep = 0;

#ifdef __EMSCRIPTEN__
      emscripten_async_call(nextTest, 0, 1500);
#else
      SDL_Delay(1500);
      nextTest();
#endif

    }
}

void audio_callback(void *_beeper, Uint8 *_stream, int _length) {
  //printf("exec: audio_callback()\n");

    Beeper* beeper = (Beeper*) _beeper;

    if (beeper->sdlAudioFormat == AUDIO_U8) {
      Uint8 *stream = (Uint8*) _stream;
      beeper->generateSamples(stream, _length);
    } else if (beeper->sdlAudioFormat == AUDIO_S16LSB) {
      Sint16 *stream = (Sint16*) _stream;
      int length = _length / 2;
      beeper->generateSamples(stream, length);
    } else {
        //assert(false && "Audio sample generation not implemented for current format!\n");
    }
}





/*
void drawRandomPixels( ) {
    if (SDL_MUSTLOCK(screen4)) SDL_LockSurface(screen4);
    unsigned char *pixele = (unsigned char *)&screen4->pixels;

    for (int i=0; i < 1048576; i++) {
        char randomByte = rand() % 255;
        pixele[i] = randomByte;
    }

    if (SDL_MUSTLOCK(screen4)) SDL_UnlockSurface(screen4);
    SDL_Flip(screen4);
    SDL_UnlockSurface(screen4);
    //SDL_Quit();
}

int kek ( ) {
    SDL_Init(SDL_INIT_VIDEO);
    screen4 = SDL_SetVideoMode(60, 45, 32, SDL_SWSURFACE);
    SDL_Rect dest4 = { 30, 30, 4, 4 };
    printf("Init: %d\n", TTF_Init());
    TTF_Font *font = TTF_OpenFont("sans-serif", 24);
    SDL_Color color = { 0xcc, 0xcc, 0x00, 0x00 };
    SDL_Rect rect = { 20, 20, 8, 8 };
    SDL_Surface *text = TTF_RenderText_Solid(font, "noise", color);
    SDL_BlitSurface(text, NULL, screen4, &rect);
    //drawRandomPixels();
    emscripten_set_main_loop(drawRandomPixels, 60, 1);
    return 0;
}

int r, n=5;
const int m=16385; double knx[m], kny[m];

void Traf(double xA, double yA, double xB, double yB ,int r) { 
  knx[r]=xA; kny[r]=yA;
   knx[r+1]=(2*xA+xB)/3; kny[r+1]=(2*yA+yB)/3;
   knx[r+2]=(xB+xA)/2+(yA-yB)/(2*sqrt(3.0));
   kny[r+2]=(yB+yA)/2+(xB-xA)/(2*sqrt(3.0));
   knx[r+3]=(xA+2*xB)/3; kny[r+3]=(yA+2*yB)/3;
   knx[r+4]=xB; kny[r+4]=yB; 
 }

void Fract( ) {
     double Ax=-0.7, Ay=-0.4, Bx=0.7, By=-0.4, Cx, Cy;
    Cx=(Bx+Ax)/2+(Ay-By)*sqrt(3.0)/2;
    Cy=(By+Ay)/2+(Bx-Ax)*sqrt(3.0)/2;
    Traf(Bx,By,Ax,Ay,0); Traf(Ax,Ay,Cx,Cy,4);
    Traf(Cx,Cy,Bx,By,8);
     for(int j=0; j<n-1; j++)
   {
     double kn1x[m], kn1y[m]; r=3*pow(4.0, j+1);
           for(int i=0; i<=r; i++) { 
              kn1x[i]=knx[i]; kn1y[i]=kny[i];
            }
           for(int i=0; i<r; i++){
            Traf(kn1x[i],kn1y[i],kn1x[i+1],kn1y[i+1],4*i);
          }
   }
}


void Draw(){
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glColor3d(1.0, 0.0, 0.0);
   glLineWidth(3.0);
   glBegin(GL_LINES);
    for(int i=0; i<4*r; i++) {
        glVertex2d(knx[i], kny[i]);
        glVertex2d(knx[i+1], kny[i+1]);
    }
   glEnd();
   glPopMatrix();
   glRotated(0.5, 0.0, 0.0, 1.0);
   glutSwapBuffers();
}

 

void main2(int argc, char** argv) {
   glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
   glutInitWindowPosition(200, 200);
   glutInitWindowSize(400, 400);
   glutCreateWindow("snow");
   glClearColor(0.8, 1.0, 0.9, 1.0);
   Fract();
   glutIdleFunc(Draw);
   glutDisplayFunc(Draw);
   glutMainLoop();
}
*/

void drawRandomPixels2( ) {
  SDL_Rect rect = { 200, 200, 8, 8 };
  rect.y = lastRectY;
  rect.x = lastRectX;
  Uint32 subsystem_init;
  printf("start: drawRandomPixels2()\n");
    if(SDL_WasInit(SDL_INIT_VIDEO)!=0) {
    printf("drawRandomPixels2->SDL_INIT_VIDEO::Video is initialized.\n");
  } else {
    printf("drawRandomPixels2->SDL_INIT_VIDEO::Video is not initialized.\n");
  }
  
  Uint32 subsystem_mask=SDL_INIT_VIDEO;

if(SDL_WasInit(subsystem_mask)==subsystem_mask)
  printf("Video and Audio initialized.\n");
else
  printf("Video and Audio not initialized.\n");


  //int max = 255;
  //int min = 0;
     //int randNum = rand() % (max - min - 1) + min + 1;
    screen = SDL_GetVideoSurface();
     printf("call: drawRandomPixels2->SDL_MUSTLOCK ( screen )\n");
    if (SDL_MUSTLOCK(screen)) {
      printf("return TRUE: drawRandomPixels2->SDL_MUSTLOCK ( screen )\n");
      printf("call: drawRandomPixels2->SDL_LockSurface ( screen )\n");
      SDL_LockSurface(screen);
      printf("return: drawRandomPixels2->SDL_LockSurface ( screen )\n");
    }
    printf("return FALSE: drawRandomPixels2->SDL_MUSTLOCK ( screen )\n");

    printf("set: drawRandomPixels2->SDL_Color color;\n");
    //SDL_Color color = { 0xcc, 0x00, 0x00, 0x00 };
    //color.r = (randNum >> 8) & 0xff;
    //color.g = (randNum >> 8) & 0xff;
    //color.b = (randNum >> 8) & 0xff;

    //printf("set: drawRandomPixels2->SDL_Rect rect;\n");
    //rect.y = 2 + rand() % 80;
    //rect.x = 2 + rand() % 60;
    
    SDL_UnlockSurface(screen);

    //SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, color.r, color.g, color.b, 0xff));
    SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, 0x00, 0x00, 0x00, 0x00));
    
    //if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
    //emscripten_get_canvas_element_size("#canvas", &width, &height);
    int max = Demowidth-20;
    int min = 20;
    rect.x = rand() % (max - min - 1) + min + 1;
    max = Demoheight;
    rect.y = rand() % (max - min - 1) + min + 1;
    SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, 0x22, 0x22, 0xff, 0xff));


    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
    SDL_Flip(screen);
    SDL_UnlockSurface(screen);
    SDL_Quit();
    
    //SDL_Flip(screen);
    //SDL_UnlockSurface(screen);
    //SDL_Quit();
}

int  GraphPaintXY( int some, int argc) {

  lastRectY = 200, lastRectX = 200;
   printf("START: GraphPaintXY()\n");

  if(SDL_WasInit(SDL_INIT_VIDEO)!=0) {
    printf("GraphPaintXY->SDL_INIT_VIDEO::Video is initialized.\n");
  } else {
    printf("GraphPaintXY->SDL_INIT_VIDEO::Video is not initialized.\n");
  }


  if (SDL_Init(SDL_INIT_VIDEO) != 0) sdlError("error:  GraphPaintXY->SDL_Init\n");

  screen = SDL_SetVideoMode(Demowidth, Demoheight, 32, SDL_HWSURFACE);
  if (screen == NULL) sdlError("error:  GraphPaintXY->SDL_SetVideoMode\n");

  printf("Init: %d\n", TTF_Init());
  TTF_Font *font = TTF_OpenFont("sans-serif", 32);
  printf("Font: %p\n", font);
  TTF_Font *font2 = TTF_OpenFont("areal", 14);
  printf("Font: %p\n", font2);

  SDL_Color color = { 0xff, 0x99, 0x00, 0xff };
  SDL_Surface *text = TTF_RenderText_Solid(font, "hi, lulz, 1337", color);
  SDL_Color color2 = { 0xbb, 0, 0xff, 0xff };

  SDL_Surface *text2 = TTF_RenderText_Solid(font2, "wasmcc demo scene", color2);

  SDL_Rect dest = { 20, 20, 0, 0 };
  SDL_Rect dest2 = { 100, 100, 0, 0 };
  SDL_BlitSurface (text, NULL, screen, &dest2);
  SDL_BlitSurface (text2, NULL, screen, &dest);
  SDL_Rect rect = { 200, 200, 8, 8 };
  rect.x = lastRectX;
  rect.y = lastRectY;

  SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, 0x22, 0x22, 0xff, 0xff));
 

  SDL_Flip(screen); 

  if (SDL_LockSurface(screen) != 0) { 
    sdlError("error: GraphPaintXY->SDL_LockScreen");
  }

  SDL_UnlockSurface(screen);
  SDL_Quit();
  printf(" GraphPaintXY close\n");

  return 0;
}


int main(int argc, char** argv) {

    Demowidth = 800;
    Demoheight = 600;
    char name[] = "lulz";
    SDL_Thread *thread;
    int result;
    int some = 0;

    printf("main() 1\n");

    emscripten_set_window_title(name);
    printf("main() 2\n");
    
    GraphPaintXY( some, argc );
    printf("main() 3\n");

    thread = SDL_CreateThread(test_thread, (void *)NULL);
    printf("main() 4\n");

    if (NULL == thread) {
        SDL_Delay(30);
        printf("main() 5\n");
    } else {
        SDL_WaitThread(thread, &result);
        printf("main() 6\n");
    }
    printf("main() 7\n");

    nextTest();

    printf("main() 8\n");
  SDL_Init(SDL_INIT_AUDIO);
  printf("main() 9\n");

  printf("emscripten_set_main_loop\n");
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(update, 60, 0);
#else
  while(beep) {
    SDL_Delay(30);
    update();
  }
#endif

#ifdef REPORT_RESULT
  REPORT_RESULT(result);
#endif
  printf("EXIT\n");
  return 0;
}
