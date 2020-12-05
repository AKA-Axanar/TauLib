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

/**
 *  \brief avoid conflict with other libraries
 */
namespace Tau { // to avoid conflict with other libraries

bool Init_SDL();
void Quit_SDL();

} // end namespace Tau


