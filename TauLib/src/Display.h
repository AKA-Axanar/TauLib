#pragma once

#include "Win.h"

///
/// @file
/// @brief Header file for Display class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

namespace Tau {

/// @struct Display A Display is a Win (Window) that takes over the entire display.
/// There is no title bar or border as the window fills the entire display.
/// There are two options when creating the full screen window.
/// 1) SDL_WINDOW_FULLSCREEN and you specify a resolution of the display, the display switches to that resolution.  The window is the full screen at that resolution.
/// 2) SDL_WINDOW_FULLSCREEN_DESKTOP where you take over the entire display at the current resolution.
/// 
/// To make a Window that is not full screen use a Win object instead.
///
struct Display : public Win {

    Display() : Win() { }
    
    /// @brief InitDisplay Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP and takes over the entire display at the current resolution.
    bool InitDisplay(unsigned int _displayIndex);

    /// @brief InitDisplay Uses flag SDL_WINDOW_FULLSCREEN and takes over the display at the new resolution
    bool InitDisplay(int _displayIndex, Tau_Size newResolution);

    Tau_Rect displayBounds;
    Tau_Size displayResolution;

    static int GetNumberOfDisplays() { return SDL_GetNumVideoDisplays(); }
};

}
