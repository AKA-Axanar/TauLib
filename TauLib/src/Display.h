#pragma once

#include "Win.h"

///
/// @file
/// @brief Header file for Display class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

namespace Tau {

/// @struct Display is a Win (Window) that takes over the entire display.
/// There is no title bar or border as the window fills the entire display.
/// There are two options when creating the full screen window.
/// 1) SDL_WINDOW_FULLSCREEN_DESKTOP where you take over the entire display at the current resolution.
/// 2) SDL_WINDOW_FULLSCREEN and you specify a resolution of the display, the display switches to that resolution.  The window is the full screen at that resolution.
/// 
/// To make a Window that is not full screen call Win::InitWin() instead.
///
struct Display : public Win {

    Display() : Win() { }

    /// @brief InitDisplay - Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP and takes over the entire display at the current resolution.
    bool InitDisplay_FULLSCREEN_DESKTOP(unsigned int _displayIndex);

    /// @brief InitDisplay Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP and takes over the entire display at the current resolution.
    /// @note SDL_WINDOW_FULLSCREEN_DESKTOP is OR'd into _flagsWin
    bool InitDisplay_FULLSCREEN_DESKTOP(unsigned int _displayIndex, const std::string& _title, Uint32 _flagsWin, Uint32 _flagsRenderer);

    /// @brief InitDisplay - Uses flag SDL_WINDOW_FULLSCREEN and takes over the display at the new resolution
    bool InitDisplay_FULLSCREEN(unsigned int _displayIndex, Tau_Size newResolution);

    /// @brief InitDisplay - Uses flag SDL_WINDOW_FULLSCREEN and takes over the display at the new resolution
    /// @note SDL_WINDOW_FULLSCREEN is OR'd into _flagsWin
    bool InitDisplay_FULLSCREEN(unsigned int _displayIndex, Tau_Size newResolution, const std::string& _title, Uint32 _flagsWin, Uint32 _flagsRenderer);

    // to create the window bounds for a certain display you need to pass a special flag value for the x and y.
    // the display index starts at 0
    static Tau_Posit getDisplayIndexPositFlag(int displayIndex);
    static Tau_Rect  getDisplayIndexBoundsFlag(int displayIndex, const Tau_Size& winSize);
    static Tau_Rect  getDisplayIndexBoundsFlag(int displayIndex) { return getDisplayIndexBoundsFlag(displayIndex, { 0, 0 }); }

    static int GetNumberOfDisplays() { return SDL_GetNumVideoDisplays(); }

    /// @brief InitDisplay - passes all args directly to InitWin.  it might not be full screen.
    bool InitDisplay(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 _flagsWin, Uint32 _flagsRenderer);
};

}
