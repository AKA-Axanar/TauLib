#include "Display.h"
#include <assert.h>

using namespace std;
using namespace Tau;

bool Display::Init(unsigned int _displayIndex)                           ///< Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP
{
    bool ret = Win::Init(_displayIndex, "", { (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex), (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex) }, { 0, 0 }, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetDisplayBounds(displayIndex, &displayBounds);
    return ret;
}

bool Display::Init(int _displayIndex, Tau_Size newResolution)   ///< Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP and passes the new resolution
{
    bool ret = Win::Init(_displayIndex, "", { (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex), (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex) }, newResolution, SDL_WINDOW_FULLSCREEN);
    SDL_GetDisplayBounds(displayIndex, &displayBounds);
    return ret;
}

