#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "renderText.h"

using namespace std;
const char *fontPath = "RedditSans-VariableFont_wght.ttf";

bool initSDLTTF()
{
    if (TTF_Init() == -1) {
        cerr << "Failed to initialize SDL_ttf. Error: " << TTF_GetError() << endl;
        return false;
    }
    return true;
}

void renderText(SDL_Window* window, SDL_Renderer* renderer, const string &text, int x, int y, int fontsize)
{
    if (initSDLTTF()== false) {
        SDL_Quit();
    }
    TTF_Font* font = TTF_OpenFont(fontPath, fontsize);
    if (font == nullptr) {
        cerr << "Failed to load font. Error: " << TTF_GetError() << endl;
        return;
    }

    SDL_Color textColor = {0, 0, 0};

    // Tạo surface từ text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        cerr << "Unable to render text surface. Error: " << TTF_GetError() << endl;
        TTF_CloseFont(font);
        return;
    }

    // Tạo texture từ surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        cerr << "Unable to create texture from rendered text. Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Lấy kích thước của texture để vẽ lên màn hình
    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    // Vị trí để vẽ text lên màn hình
    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    // Vẽ texture lên renderer
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
}

void showScore (SDL_Window* window, SDL_Renderer* renderer, int score, int Life)
{
    string scoreText = "Score: " + to_string(score);
    renderText(window, renderer, scoreText, 800, 0, 40);
    string life = "Life: "+ to_string(Life);
    renderText(window, renderer, life, 1050, 0, fontSize);
}






