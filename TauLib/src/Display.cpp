#include "Display.h"
#include "SDL.h"
#include <iostream>
#include <format>

using namespace std;
using std::format;

namespace Tau {

    // GetDisplayInfos -  return info about the displays attached to the system
    vector<DisplayInfo> Display::GetDisplayInfos() {
        unsigned int count = GetNumberOfDisplays();
        vector<DisplayInfo> ret;

        for (unsigned int i = 0; i < count; ++i) {
            DisplayInfo info;
            info.displayIndex = i;
            //info.undefinedDisplayPosit = GetUndefinedDisplayPosit(i);
            //info.centeredDisplayPosit = GetCenteredDisplayPosit(i);
            info.desktopXPosit = GetDesktopDisplayPosit(i).x;
            info.size = GetDisplaySize(i);
            info.desktopBounds = { { info.desktopXPosit, 0 }, info.size };

            //cout << format("display {:d}, undefined posit x {:d} y {:d}\n", i, info.undefinedDisplayPosit.x, info.undefinedDisplayPosit.y);
            //cout << format("display {:d}, undefined posit x {:x} y {:x}\n", i, info.undefinedDisplayPosit.x, info.undefinedDisplayPosit.y);

            //cout << format("display {:d}, centered posit x {:d} y {:d}\n", i, info.centeredDisplayPosit.x, info.centeredDisplayPosit.y);
            //cout << format("display {:d}, centered posit x {:x} y {:x}\n", i, info.centeredDisplayPosit.x, info.centeredDisplayPosit.y);

            cout << format("display {:d}, desktop X posit {:d}\n", i, info.desktopXPosit);
            //cout << format("display {:d}, desktop X  posit {:x}\n", i, info.desktopXPosit.x);

            cout << format("display {:d}, size w {:d} h {:d}\n", i, info.size.w, info.size.h);
            cout << endl;

            ret.emplace_back(info);
        }
        return ret;
    }

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
