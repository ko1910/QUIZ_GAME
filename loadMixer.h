#ifndef LOAD_MIXER_H_
#define LOAD_MIXER_H_

#include <SDL.h>
bool initAudio();
void cleanupAudio();
void playMusic(const char* filename, int loops);
bool playShortSound(const char* filename, int loops);
bool playLongSound(const char* filename, int loops);

#endif // LOAD_MIXER_H_
