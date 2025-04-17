#ifndef INIT_SDL_H_
#define INIT_SDL_H_

#include <SDL.h>


void logErrorAndExit(const char* msg, const char* error);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
void waitUntilKeyPressed();
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

#endif // INITSDL_H_
