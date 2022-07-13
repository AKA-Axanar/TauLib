#pragma once

#include "Tau_Rect.h"
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

    /// @brief GetNumberOfDisplays - returns the number of displays.  the first display is index 0.
    static unsigned int GetNumberOfDisplays();

    /// @brief getDisplayPosit
    /// @param displayIndex the display index
    /// @note to get a window in a particular display pass SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex) or
    /// SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) for BOTH x and y.
    /// the display index starts at 0
    static Tau_Posit GetDisplayPosit(int displayIndex);

    /// @brief getDisplaySize
    /// @param displayIndex the display index
    /// @return display size
    static Tau_Size GetDisplaySize(int displayIndex);
};
}

