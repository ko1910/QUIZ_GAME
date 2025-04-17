#ifndef RENDER_TEXT_H_
#define RENDER_TEXT_H_

#include <SDL.h>

using namespace std;
const int fontSize = 40;

bool initSDLTTF() ;
void renderText(SDL_Window* window, SDL_Renderer* renderer, const string &text, int x, int y, int fontsize);
void showScore (SDL_Window* window, SDL_Renderer* renderer, int score, int Life);
#endif // RENDER_TEXT_H_
