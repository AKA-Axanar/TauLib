#pragma once

#include "Tau_Rect.h"
#include "SDL.h"
#include <vector>

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau {

struct DisplayInfo {
    unsigned int displayIndex { 0 };
    Tau_Posit posit;
    Tau_Size size;
    Tau_Rect bounds;
};

struct Display {
    /// @brief GetDisplayInfos -  return info about the displays attached to the system
    static std::vector<DisplayInfo> GetDisplayInfos();

    /// @brief GetNumberOfDisplays - returns the number of displays.  the first display is isndex 0.
    static unsigned int GetNumberOfDisplays() { return SDL_GetNumVideoDisplays(); }

    /// @brief getDisplayPositFlag
    /// @param displayIndex the display index
    /// @note to create the window position for a certain display you need to pass a special flag value for the x and y.
    /// the display index starts at 0
    static Tau_Posit GetDisplayPositFlag(int displayIndex) {
        return { (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex), (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) };
    }

    /// @brief getDisplaySize
    /// @param displayIndex the display index
    /// @return display size
    static Tau_Size GetDisplaySize(int displayIndex) {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(displayIndex, &DM);
        return { DM.w, DM.h };
    }
};
}

