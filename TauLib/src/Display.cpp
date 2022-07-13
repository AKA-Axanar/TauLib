#include "Display.h"
#include "SDL.h"

using namespace std;

namespace Tau {

    // GetDisplayInfos -  return info about the displays attached to the system
    vector<DisplayInfo> Display::GetDisplayInfos() {
        unsigned int count = GetNumberOfDisplays();
        vector<DisplayInfo> ret;

        for (unsigned int i = 0; i < count; ++i) {
            DisplayInfo info;
            info.displayIndex = i;
            info.posit = GetDisplayPosit(i);
            info.size = GetDisplaySize(i);
            info.bounds = { info.posit, info.size };

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
    Tau_Posit Display::GetDisplayPosit(int displayIndex) {
        return { (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex), (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) };
    }

    // getDisplaySize - return display size
    Tau_Size Display::GetDisplaySize(int displayIndex) {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(displayIndex, &DM);
        return { DM.w, DM.h };
    }

}
