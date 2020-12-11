#include "TauLib.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <iostream>

using namespace std;

///
/// @file
/// @brief cpp file for TauLib initialization and exit routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

namespace Tau { // to avoid conflict with other libraries

//
// Initialize SDL, Audio mixer, TTF fonts, etc.
// audioFormats available: MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG, MIX_INIT_MID, MIX_INIT_OPUS
// audioFormats default: MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC
// 
bool Init_SDL(int audioFormats) {
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
    Mix_Init(audioFormats);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Mix_OpenAudio failed" << endl;
        return false;
    }

    return true;
}

//
// Quit_SDL Quit SDL, Audio mixer, TTF fonts, etc
// 
void Quit_SDL() {
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

} // end namespace Tau