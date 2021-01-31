#include "Win.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <assert.h>
#include "Display.h"

using namespace std;

///
/// @file
/// @brief cpp file for Win class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

namespace Tau { // to avoid conflict with other libraries

//
// InitWin
//
bool Win::InitWin(unsigned int _displayIndex, const string& _title, const Tau_Rect& bounds, Uint32 _flagsWin, Uint32 _flagsRenderer) {
    assert(_displayIndex < (unsigned int)Display::GetNumberOfDisplays());

    displayIndex = _displayIndex;
    title = _title;
    winRect = bounds;
    flagsWin = _flagsWin;         // https://wiki.libsdl.org/SDL_WindowFlags
    flagsRenderer = _flagsRenderer;

    window = SDL_CreateWindow(title.c_str(), bounds.x, bounds.y, bounds.w, bounds.h, flagsWin);
    if (window == nullptr) {
        cerr << "SDL_CreateWindow failed" << endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, flagsRenderer);
    if (renderer == nullptr) {
        cerr << "SDL_CreateRenderer failed" << endl;
        return false;
    }

    if (flagsWin & (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN))
        windowIsEntireDisplay = true;

    // This is the window itself not just an area of a window.  If this is a fullscreen window then the bounds
    // is already 0,0 and the width and height of the entire display screen.
    // If it is a window smaller than the display size we need to change the corner position to be 0,0 as everything
    // drawn in that window is relative to a upper left corner point of 0,0.
    winRect.SetPoint(0, 0);

    isOpen = true;
    return isOpen;
}

//
// ~Win destructor
//
Win::~Win() {
    Close();
}

///
/// @brief Win::Close - close the window
///
void Win::Close() {
    renderer = nullptr;     // SDL_Shared dtor takes care of calling the proper destroy routine
    window = nullptr;       // SDL_Shared dtor takes care of calling the proper destroy routine
    isOpen = false;
}

} // end namespace Tau