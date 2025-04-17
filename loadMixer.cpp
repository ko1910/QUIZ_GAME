#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <thread>
#include "loadMixer.h"
#include "logic.h"

using namespace std;

// Hàm khởi tạo SDL và SDL_mixer
bool initAudio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        SDL_Quit();
        return false;
    }

    return true;
}

// Hàm dọn dẹp SDL và SDL_mixer
void cleanupAudio() {
    Mix_CloseAudio();
    SDL_Quit();
}

// Hàm phát nhạc nền không chặn luồng chính
void playMusic(const char* filename, int loops) {
    Mix_Music* music = Mix_LoadMUS(filename);
    if (music == nullptr) {
        cerr << "Failed to load music from " << filename << "! SDL_mixer Error: " << Mix_GetError() << endl;
        return;
    }

    if (Mix_PlayMusic(music, loops) < 0) {
        cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << endl;
        Mix_FreeMusic(music);
        return;
    }

    // Đợi cho đến khi nhạc kết thúc hoặc bị dừng
    while (Mix_PlayingMusic()) {
        SDL_Delay(100); // Để giảm tải CPU, chờ một chút
    }

    Mix_FreeMusic(music);
}

bool playShortSound(const char* filename, int loops)
{
    if (!initAudio())
    {
        return false;
    }
    // Tải âm thanh
    Mix_Chunk* sound = Mix_LoadWAV(filename);
    if (sound == nullptr) {
        cerr << "Failed to load sound from " << filename << "! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }

    // Phát âm thanh
    if (Mix_PlayChannel(-1, sound, loops) < 0) {
        cerr << "Failed to play sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }

    // Chờ âm thanh kết thúc
    while (Mix_Playing(-1) != 0) {
        SDL_Delay(20); // Hoặc thực hiện các công việc khác ở đây
    }

    // Giải phóng âm thanh và thư viện mixer
    Mix_FreeChunk(sound);
    Mix_CloseAudio();

    return true;
}

bool playLongSound(const char* filename, int loops) {
    // Khởi tạo SDL và SDL_mixer
    if (!initAudio()) {
        return false;
    }

    // Chạy phát nhạc trên luồng riêng
    thread musicThread(playMusic, filename, loops);
    musicThread.detach();

    return true;
}
