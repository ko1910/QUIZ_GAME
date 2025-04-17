#ifndef RENDER_IMAGE_H_
#define RENDER_IMAGE_H_

#include <SDL.h>
const int answer1X = 50; const int answer2X = 50;const int answer3X = 50; const int answer4X = 50;
const int answer1Y = 205;const int answer2Y = 305; const int answer3Y = 405;const int answer4Y = 505;

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);
void unload_SDL_And_Images(SDL_Window* window, SDL_Renderer* renderer);
void load_SDL_And_Images(SDL_Window* window, SDL_Renderer* renderer);
void renderTexture(SDL_Texture *texture,  int x, int y, SDL_Renderer *render);
void renderBackground(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void renderBackgroundStartGames(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void renderBackgroundEndGames(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void showStartGames(SDL_Window *window, SDL_Renderer* renderer);
void showImagines(SDL_Window* window, SDL_Renderer* renderer);
void player_answer(SDL_Window* window, SDL_Renderer* renderer, int count);
void showEndGames(SDL_Window *window, SDL_Renderer* renderer);
#endif // RENDER_IMAGE_H_

