#pragma once

#include "Win.h"

namespace Tau {

/// @struct Display A Display is a Win (Window) that takes over the entire display.
/// There is no title bar or border as the window fills the entire display.
/// There are two options when creating the full screen window.
/// 1) SDL_WINDOW_FULLSCREEN and you specify a resolution of the display, the display switches to that resolution.  The window is the full screen at that resolution.
/// 2) SDL_WINDOW_FULLSCREEN_DESKTOP where you take over the entire display at the current resolution.
/// 
struct Display : public Win {

    Display() : Win() { }
    Display(unsigned int _displayIndex) : Display() { Init(_displayIndex); }
    
    /// @brief Init Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP and takes over the entire display at the current resolution.
    bool Init(unsigned int _displayIndex);

    /// @brief Init Uses flag SDL_WINDOW_FULLSCREEN and takes over the display at the new resolution
    bool Init(int _displayIndex, Tau_Size newResolution);

    Tau_Rect displayBounds;
    Tau_Size displayResolution;

    static int GetNumberOfDisplays() { return SDL_GetNumVideoDisplays(); }
};

}
