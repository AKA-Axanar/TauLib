#pragma once

#include "Tau_Rect.h"
#include <vector>

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau {

/// @brief DisplayInfo - the size and desktop position and bounds on the desktop of a display
struct DisplayInfo {
    unsigned int displayIndex { 0 };
    Tau_Size size;              // display resolution
                                // the desktop spans the entire multiple displays.
    int desktopXPosit;          // the x position of the upper left corner of the desktop.
    Tau_Rect desktopBounds;     // the bounds of the display on the desktop

    friend std::ostream& operator << (std::ostream& os, const DisplayInfo& rhs);
};

///
/// @brief GetDisplayInfos -  return info about the displays attached to the system
///
class Displays {
    Displays() {};     // private

    void GetDisplayInfos();

    public:
    ~Displays() {}
    Displays(Displays const &) = delete;
    Displays &operator=(Displays const &) = delete;

    std::vector<DisplayInfo> DisplayInfos;

    // GetInstance
    static Displays& GetInstance() {
        static bool inited { false };
        static Displays displays;
        if (!inited) {
            displays.GetDisplayInfos();
            inited = true;
        }
        return displays;
    }

    friend std::ostream& operator << (std::ostream& os, const Displays& rhs);
};

///
///
///
struct Display {
    /// @brief GetNumberOfDisplays - returns the number of displays.  the first display is index 0.
    static unsigned int GetNumberOfDisplays();

    /// @brief GetDesktopDisplayPosit
    /// @param displayIndex - the display index.  the display index starts at 0.
    /// @note this figures out the desktop screen position by creating a centered window in a display with
    /// a size of the entire display.  then by calling SDL_GetWindowPosition to find the upper left corner position of the
    /// display.  the position is the position across an entire desktop of multiple displays.  you can then create
    /// a window offset from that position to create a window any where in that display.
    //
    //                  x on desktop                x on desktop                        x on desktop
    //                  x = -2560                   x = 0                               x = 3480
    //                  +-----------------------+   +-------------------------------+   +-----------------------+
    //                  |                       |   |                               |   |                       |
    //                  |      display 1        |   |          display 0            |   |      display 2        |
    //                  |                       |   |                               |   |                       |
    //                  |     2560 x 1440       |   |         3840 x 2160           |   |     2560 x 1440       |
    //                  |                       |   |                               |   |                       |
    //                  |                       |   |                               |   |                       |
    //                  +-----------------------+   |                               |   +-----------------------+
    //                                              |                               |                                    
    //                                              |                               |                                    
    //                                              +-------------------------------+
    //
    static Tau_Posit GetDesktopDisplayPosit(int displayIndex);      // returns the actual desktop position across multiple displays

    /// @brief getDisplaySize
    /// @param displayIndex the display index
    /// @return display size
    static Tau_Size GetDisplaySize(int displayIndex);

    /// @brief getDisplayPosit
    /// @param displayIndex - the display index.  the display index starts at 0.
    /// @note to get a window in a particular display pass SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex) or
    /// SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) for BOTH x and y.  Unfortunately, creating a window
    /// using either will always create the window centered in the display.
    static Tau_Posit GetUndefinedDisplayPosit(int displayIndex);    // returns 0x1FFF000# where # is the display index
    static Tau_Posit GetCenteredDisplayPosit(int displayIndex);     // returns 0x2FFF000# where # is the display index
};
}

