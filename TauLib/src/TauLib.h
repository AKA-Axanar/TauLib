#pragma once
#include "SDL_mixer.h"

///
/// @file
/// @brief Header file for TauLib initialization and exit routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 
// Info:
// #if defined(__linux__)                           // Linux OS
// #if defined(_WIN32)                              // Windows OS
// #if defined(__x86_64__) || defined(_M_X64)       // Intel/AMD CPU
// #if defined(_M_ARM64)                            // Arm CPU
// #if defined (PI_DEBUG)                           // Pi (build defined)

///
/// @namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief Init_SDL
/// 
bool Init_SDL();

///
/// @brief Init_TTF (Fonts)
/// 
bool Init_TTF();

///
/// @brief Init_Mixer (Audio)
/// @param audioFormats 
/// audio formats available: MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG, MIX_INIT_MID, MIX_INIT_OPUS
/// audioFormats default: MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC
/// 
bool Init_Mixer(int audioFormats = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);

///
/// @brief Init_All - Init SDL, TTF, Audio
/// @param audioFormats 
/// audio formats available: MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG, MIX_INIT_MID, MIX_INIT_OPUS
/// audioFormats default: MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC
///
bool Init_All(int audioFormats = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);



///
/// @brief Quit_SDL
/// 
void Quit_SDL();

///
/// @brief Quit_TTF (fonts)
/// 
void Quit_TTF();

///
/// @brief Quit_Mixer (Audio)
/// 
void Quit_Mixer();

//
// Quit Audio, TTF, SDL
//
void Quit_All();

} // end namespace Tau


