#include "TauLib.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <iostream>

using namespace std;
namespace Tau { // too avoid conflict with other libraries

//
// Init
//
bool Init_SDL() {
    // init almost everything
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "SDL_Init failed" << endl;
        return false;
    }

    // init fonts
    if (TTF_Init() == -1) {
        cerr << "TTF_Init failed" << endl;
        return false;
    }

    // init audio
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Mix_OpenAudio failed" << endl;
        return false;
    }

    return true;
}

//
// Quit_SDL
//
void Quit_SDL() {
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}