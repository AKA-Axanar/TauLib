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
// Init SDL
// 
bool Init_SDL() {
    // init almost everything
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "SDL_Init failed" << endl;
        return false;
    }

    return true;
}

//
// Init Fonts
//
bool Init_TTF() {
    // init fonts
    if (TTF_Init() == -1) {
        cerr << "TTF_Init failed" << endl;
        return false;
    }

    return true;
}

//
// Init Audio mixer
// audioFormats available: MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG, MIX_INIT_MID, MIX_INIT_OPUS
// audioFormats default: MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC
// 
bool Init_Mixer(int audioFormats) {
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Mix_OpenAudio failed" << endl;
        return false;
    }

    return true;
}

//
// Init SDL, TTF, Audio
//
bool Init_All(int audioFormats) {
    bool ok {true};

    if (!Init_SDL())
        ok = false;
    if (!Init_TTF())
        ok = false;
    if (!Init_Mixer(audioFormats))
        ok = false;

    return ok;
}

//
// Quit Audio mixer
// 
void Quit_Mixer() {
    Mix_CloseAudio();
    Mix_Quit();
}

//
// Quit_TTF (fonts)
// 
void Quit_TTF() {
    TTF_Quit();
}

//
// Quit_SDL 
// 
void Quit_SDL() {
    IMG_Quit();
    SDL_Quit();
}

//
// Quit Audio, TTF, SDL
//
void Quit_All() {
    Quit_Mixer();
    Quit_TTF();
    Quit_SDL();
}

} // end namespace Tau