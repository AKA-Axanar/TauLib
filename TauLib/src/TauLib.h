#pragma once
#include "SDL_mixer.h"

///
/// @file
/// @brief Header file for TauLib initialization and exit routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 
/// Info:
/// #if defined(__linux__)                           // Linux OS
/// #if defined(_WINDOWS_)                           // Windows OS
/// #if defined(__x86_64__) || defined(_M_X64)       // Intel/AMD CPU
/// #if defined(_M_ARM64)                            // Arm CPU

///
/// @namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief Init_SDL(int audioFormats = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC)
/// Initialize SDL, Audio mixer, TTF fonts, etc.
/// audioFormats available: MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG, MIX_INIT_MID, MIX_INIT_OPUS
/// audioFormats default: MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC
/// 
bool Init_SDL(int audioFormats = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);

///
/// @brief Quit_SDL Quit SDL, Audio mixer, TTF fonts, etc
/// 
void Quit_SDL();

} // end namespace Tau


