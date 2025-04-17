#include <iostream>
#include <vector>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "initSDL.h"
#include "renderImage.h"
#include "renderText.h"
#include "logic.h"
#include "loadMixer.h"


using namespace std;

/************************************************/
const char WINDOW_TITLE[] = "Quizgame";
const int SCREEN_WIDTH=1200, SCREEN_HEIGHT=600;
int main(int argc, char *argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    load_SDL_And_Images(window, renderer);

    // Ví dụ sử dụng hàm playLongSound để chạy nhạc nền
    if (!playLongSound("sounds/soundBackground.mp3", -1)) {
        cerr << "Failed to play background music." << endl;
        return 1;
    }

    // Giả lập vòng lặp chính của game
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }}
    showStartGames(window, renderer);
    SDL_RenderPresent(renderer);
    playShortSound("sounds/hello.mp3", 0);
    SDL_Event e;
    while (true)
    {
        SDL_Delay(10);
        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&e) == 0) continue;

        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;

        // Nếu nhấn phím ESC thì thoát khỏi vòng lặp
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        // Nếu chuột (mouse) được nhấn (xuống)
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int mouseX = e.button.x; // Lấy hoành độ x của chuột
            int mouseY = e.button.y; // Lấy tung độ y của chuột
            if (mouseX >= 500 && mouseX <= 690 && mouseY >= 440 && mouseY <= 495)
            {
                SDL_RenderClear(renderer);
                SDL_RenderClear(renderer);
                playGames(window, renderer, 0, 3);
                SDL_RenderPresent(renderer);
                break;
            }

        }
    }
        SDL_Delay(16); // Giả lập 60 FPS
    }

    // Dọn dẹp SDL và SDL_mixer
    cleanupAudio();
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}



