#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "renderImage.h"
#include "loadMixer.h"

using namespace std;

SDL_Texture *backgroundStartGames, *background, *backgroundEndGames, *startGames, *endGames, *story;
SDL_Texture *answer1, *answer2, *answer3, *answer4;
SDL_Texture *cellV, *cellX;
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}


void unload_SDL_And_Images(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(startGames);
    SDL_DestroyTexture(endGames);
    SDL_DestroyTexture(answer1);
    SDL_DestroyTexture(answer2);
    SDL_DestroyTexture(answer3);
    SDL_DestroyTexture(answer4);
    SDL_DestroyTexture(cellV);
    SDL_DestroyTexture(cellX);
    SDL_DestroyTexture(story);
    IMG_Quit();
}
void playerEndGames(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(answer1);
    SDL_DestroyTexture(answer2);
    SDL_DestroyTexture(answer3);
    SDL_DestroyTexture(answer4);
    SDL_DestroyTexture(cellV);
    SDL_DestroyTexture(cellX);
    IMG_Quit();
}
void load_SDL_And_Images(SDL_Window* window, SDL_Renderer* renderer)
{
    background = loadTexture("images/background.jpg", renderer);
    backgroundStartGames = loadTexture("images/backgroundStartGames.png", renderer);
    backgroundEndGames = loadTexture("images/backgroundEndGames.png", renderer);
    answer1 = loadTexture("images/answer1.png", renderer);
    answer2 = loadTexture("images/answer2.png", renderer);
    answer3 = loadTexture("images/answer3.png", renderer);
    answer4 = loadTexture("images/answer4.png", renderer);
    cellV = loadTexture("images/cellV.png", renderer);
    cellX = loadTexture("images/cellX.png", renderer);
    story = loadTexture("images/story.png", renderer);
    if (background == nullptr)
    {
        unload_SDL_And_Images(window, renderer);
        exit(1);
    }
}
void renderTexture(SDL_Texture *texture,  int x, int y, SDL_Renderer *render)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(render, texture, NULL, &dst);
}

void renderBackground(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, background, NULL, &destRect);
}
void renderBackgroundStartGames(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, backgroundStartGames, NULL, &destRect);
}
void renderBackgroundEndGames(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    SDL_Rect destRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, backgroundEndGames, NULL, &destRect);
}
void showStartGames(SDL_Window *window, SDL_Renderer* renderer)
{
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    renderBackgroundStartGames(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void showImagines(SDL_Window* window, SDL_Renderer* renderer)
{
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    renderBackground(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture(answer1, answer1X, answer1Y, renderer);
    renderTexture(answer2, answer2X, answer2Y, renderer);
    renderTexture(answer3, answer3X, answer3Y, renderer);
    renderTexture(answer4, answer4X, answer4Y, renderer);

}
void player_answer(SDL_Window* window, SDL_Renderer* renderer, int count)
{
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    if (count == 1) {
        renderTexture(cellV, 700, 100, renderer);
    } else if(count == 0) {
        renderTexture(cellX, 700, 150, renderer);
    }
}
void showEndGames(SDL_Window *window, SDL_Renderer* renderer)
{
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    renderBackgroundEndGames(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

