#include "Display.h"
#include "SDL.h"
#include <iostream>
#include <format>

using namespace std;
using std::format;

namespace Tau {

    //////////////
    // DisplayInfo
    //////////////
    ostream& operator << (ostream& os, const DisplayInfo& rhs) {
        cout << std::format("display {:d}, posit x {:d} y {:d}\n", rhs.displayIndex, rhs.posit.x, rhs.posit.y);
        cout << std::format("display {:d}, size w {:d} h {:d}\n", rhs.displayIndex, rhs.size.w, rhs.size.h);
        cout << endl;
        return os;
    }

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
            info.posit = Display::GetDesktopDisplayPosit(i);
            info.size = Display::GetDisplaySize(i);
            info.desktopBounds = { info.posit, info.size };
            DisplayInfos.emplace_back(info);
        }
    }

    ostream& operator << (ostream& os, const Displays& rhs) {
        ranges::for_each(rhs.DisplayInfos, [] (const DisplayInfo& info) { cout << info; } );
        return os;
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
        SDL_Window* window = SDL_CreateWindow("", posit.x, posit.y, size.w, size.h, SDL_WINDOW_OPENGL );
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
