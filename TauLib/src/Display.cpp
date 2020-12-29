#include "Display.h"
#include <assert.h>

using namespace std;
using namespace Tau;

bool Display::Init(unsigned int _displayIndex)                           ///< Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP
{
    int specifyDisplayNum = (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex);

    bool ret = Win::Init(_displayIndex, "", { { specifyDisplayNum, specifyDisplayNum }, { 0, 0 } }, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetDisplayBounds(displayIndex, &displayBounds);
    winBounds = displayBounds;  // the window display bounds is the display bounds as the window is the entire display screen
    displayResolution = displayBounds.GetSize();
    return ret;
}

bool Display::Init(int _displayIndex, Tau_Size newResolution)   ///< Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP and passes the new resolution
{
    int specifyDisplayNum = (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex);

    bool ret = Win::Init(_displayIndex, "", { { specifyDisplayNum, specifyDisplayNum }, newResolution }, SDL_WINDOW_FULLSCREEN);
    SDL_GetDisplayBounds(displayIndex, &displayBounds);
    winBounds = displayBounds;  // the window display bounds is the display bounds as the window is the entire display screen
    displayResolution = displayBounds.GetSize();
    return ret;
}

