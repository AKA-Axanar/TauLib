#include "Display.h"
#include <assert.h>

using namespace std;
using namespace Tau;

// A Display is a Win (Window) that takes over the entire display.
// There is no title bar or border as the window fills the entire display.
// There are two options when creating the full screen window.
// 1) SDL_WINDOW_FULLSCREEN and you specify a resolution of the display, the display switches to that resolution.  The window is the full screen at that resolution.
// 2) SDL_WINDOW_FULLSCREEN_DESKTOP where you take over the entire display at the current resolution.

bool Display::Init(unsigned int _displayIndex)                           ///< Uses flag SDL_WINDOW_FULLSCREEN_DESKTOP
{
    int specifyDisplayNum = (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex);

    bool ret = Win::Init(_displayIndex, "", { { specifyDisplayNum, specifyDisplayNum }, { 0, 0 } }, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetDisplayBounds(displayIndex, &displayBounds);
    winRect = displayBounds;  // the window bounds is the display bounds as the window is the entire display screen
    displayResolution = displayBounds.GetSize();
    return ret;
}

bool Display::Init(int _displayIndex, Tau_Size newResolution)   ///< Uses flag SDL_WINDOW_FULLSCREEN and passes the new resolution
{
    int specifyDisplayNum = (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex);

    bool ret = Win::Init(_displayIndex, "", { { specifyDisplayNum, specifyDisplayNum }, newResolution }, SDL_WINDOW_FULLSCREEN);
    SDL_GetDisplayBounds(displayIndex, &displayBounds);
    winRect = displayBounds;  // the window bounds is the display bounds as the window is the entire display screen
    displayResolution = displayBounds.GetSize();
    return ret;
}

