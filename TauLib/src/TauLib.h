#pragma once

/**
 *  @file
 *
 *  Header file for TauLib initialization and exit routines.
 *
 */

// Info:
// #if defined(__linux__)                           Linux OS
// #if defined(_WINDOWS_)                           Windows OS
// #if defined(__x86_64__) || defined(_M_X64)       Intel/AMD CPU
// #if defined(_M_ARM64)                            Arm CPU

///
/// @namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

bool Init_SDL();    ///< @brief Init_SDL Initialize SDL, Audio, TTF fonts, etc
void Quit_SDL();    ///< @brief Quit_SDL Quit SDL, Audio, TTF fonts, etc

} // end namespace Tau


