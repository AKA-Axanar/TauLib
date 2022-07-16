#include "Display.h"
#include "SDL.h"
#include <iostream>
#include <format>

using namespace std;
using std::format;

namespace Tau {
    ///////////
    // Displays
    ///////////

    // GetDisplayInfos -  return info about the displays attached to the system
    //
    void Displays::GetDisplayInfos() {
        unsigned int count = Display::GetNumberOfDisplays();

        for (unsigned int i = 0; i < count; ++i) {
            DisplayInfo info;
            info.displayIndex = i;
            info.desktopXPosit = Display::GetDesktopDisplayPosit(i).x;
            info.size = Display::GetDisplaySize(i);
            info.desktopBounds = { { info.desktopXPosit, 0 }, info.size };
            cout << format("display {:d}, desktop X posit {:d}\n", i, info.desktopXPosit);
            cout << format("display {:d}, size w {:d} h {:d}\n", i, info.size.w, info.size.h);
            cout << endl;

            DisplayInfos.emplace_back(info);
        }
    }

    ///////////
    // Display
    ///////////

    // GetNumberOfDisplays - returns the number of displays.  the first display is index 0.
    unsigned int Display::GetNumberOfDisplays() { return SDL_GetNumVideoDisplays(); }

    // getDisplayPosit
    // @note to get a window in a particular display pass SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex) or
    // SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) for BOTH x and y.
    // the display index starts at 0
    // SDL_WINDOWPOS_UNDEFINED_DISPLAY returns 0x1FFF000# where # is the display index
    // SDL_WINDOWPOS_CENTERED_DISPLAY returns 0x2FFF000# where # is the display index
    Tau_Posit Display::GetUndefinedDisplayPosit(int displayIndex) {
        return { (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex), (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) };
    }
    Tau_Posit Display::GetCenteredDisplayPosit(int displayIndex) {
        return { (int)SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex), (int)SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex) };
    }

    //
    // GetDesktopDisplayPosit
    // returns the actual desktop position (upper left corner) across multiple displays
    //
    Tau_Posit Display::GetDesktopDisplayPosit(int displayIndex) {
        Tau_Posit posit = GetUndefinedDisplayPosit(displayIndex);
        Tau_Size size = GetDisplaySize(displayIndex);

        // create a window the entire size of that display
        SDL_Window* window = SDL_CreateWindow("", posit.x, posit.y, size.w, size.h, 0);
        // now get the position on the desktop of that window
        Tau_Posit desktopPosit;
        SDL_GetWindowPosition(window, &desktopPosit.x, &desktopPosit.y);

        SDL_DestroyWindow(window);

        return desktopPosit;
    }

    // getDisplaySize - return display size
    Tau_Size Display::GetDisplaySize(int displayIndex) {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(displayIndex, &DM);
        return { DM.w, DM.h };
    }

}
