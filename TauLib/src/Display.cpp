#include "Display.h"
#include <assert.h>
#include "Tau_Rect.h"

///
/// @file
/// @brief CPP file for Display class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

using namespace std;
using namespace Tau;

// A Display is a Win (Window) that usually takes over the entire display.
// There is no title bar or border as the window fills the entire display.
// There are two options when creating the full screen window.
// 1) SDL_WINDOW_FULLSCREEN and you specify a resolution of the display, the display switches to that resolution.  The window is the full screen at that resolution.
// 2) SDL_WINDOW_FULLSCREEN_DESKTOP where you take over the entire display at the current resolution.

/// @brief Initilaizes the LCD Display using SDL_WINDOW_FULLSCREEN_DESKTOP
bool Display::InitDisplay_FULLSCREEN_DESKTOP(unsigned int _displayIndex)
{
    int specifyDisplayNum = (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex);
    Tau_Rect bounds { { specifyDisplayNum, specifyDisplayNum }, { 0, 0 } };

    bool ret = Win::InitWin(_displayIndex, "", bounds, SDL_WINDOW_FULLSCREEN_DESKTOP,
                                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    InitDisplay_Common();
    return ret;
}

/// @brief Initilaizes the LCD Display using SDL_WINDOW_FULLSCREEN_DESKTOP
bool Display::InitDisplay_FULLSCREEN_DESKTOP(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 _flagsWin, Uint32 _flagsRenderer) {
    int specifyDisplayNum = (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex);

    bool ret = Win::InitWin(_displayIndex, _title, bounds, SDL_WINDOW_FULLSCREEN_DESKTOP | _flagsWin, _flagsRenderer);

    InitDisplay_Common();
    return ret;
}

/// @brief Initilaizes the LCD Display using SDL_WINDOW_FULLSCREEN and passes the new resolution
bool Display::InitDisplay_FULLSCREEN(unsigned int _displayIndex, Tau_Size newResolution)
{
    int specifyDisplayNum = (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex);
    Tau_Rect bounds { { specifyDisplayNum, specifyDisplayNum }, newResolution };

    bool ret = Win::InitWin(_displayIndex, "", bounds, SDL_WINDOW_FULLSCREEN,
                                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    InitDisplay_Common();
    return ret;
}

/// @brief Initilaizes the LCD Display using SDL_WINDOW_FULLSCREEN and passes the new resolution
bool Display::InitDisplay_FULLSCREEN(unsigned int _displayIndex, Tau_Size newResolution, const std::string& _title, Uint32 _flagsWin, Uint32 _flagsRenderer)
{
    int specifyDisplayNum = (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(_displayIndex);
    Tau_Rect bounds { { specifyDisplayNum, specifyDisplayNum }, newResolution };

    bool ret = Win::InitWin(_displayIndex, _title, bounds, SDL_WINDOW_FULLSCREEN | _flagsWin, _flagsRenderer);

    InitDisplay_Common();
    return ret;
}

/// @brief InitDisplay - passes all args directly to InitWin.  it might not be full screen.
bool Display::InitDisplay(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 _flagsWin, Uint32 _flagsRenderer) {
    bool ret = InitWin(_displayIndex, _title, bounds, _flagsWin, _flagsRenderer);
    InitDisplay_Common();
    return ret;
}
    
/// @brief Perform some common calls at the end of the Init routines.
void Display::InitDisplay_Common() {
    SDL_GetDisplayBounds(displayIndex, &displayBounds);
    winRect = displayBounds;  // the window bounds is the display bounds as the window is the entire display screen
    displayResolution = displayBounds.GetSize();
}

