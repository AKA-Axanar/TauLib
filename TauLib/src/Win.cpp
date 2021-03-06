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
    drawAreaRect = bounds;                   // this will get updated later
    flagsWin = _flagsWin;               // https://wiki.libsdl.org/SDL_WindowFlags
    flagsRenderer = _flagsRenderer;

    //cout << "SDL_CreateWindow" << endl;
    window = SDL_CreateWindow(title.c_str(), bounds.x, bounds.y, bounds.w, bounds.h, flagsWin);
    if (window == nullptr) {
        cerr << "SDL_CreateWindow failed" << endl;
        assert(false);
        return false;
    }

    //cout << "SDL_CreateRenderer" << endl;
    renderer = SDL_CreateRenderer(window, -1, flagsRenderer);
    if (renderer == nullptr) {
        cerr << "SDL_CreateRenderer failed" << endl;
        assert(false);
        return false;
    }

    if (flagsWin & (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN))
        windowIsEntireDisplay = true;

    if (windowIsEntireDisplay) {
        // if this is not display #0 then SDL_GetWindowPosition will return an x value that is across the entire
        // multi-display desktop and not at 0.  so set the position relative to the display corner.
        displayRelativeRect.SetPoint({0,0});
    }
    else
        SDL_GetWindowPosition(window, &displayRelativeRect.x, &displayRelativeRect.y);

    SDL_GetWindowSize(window, &displayRelativeRect.w, &displayRelativeRect.h);

    // This is the window.  So the winRect is the entire window.
    drawAreaRect = { {0,0}, displayRelativeRect.GetSize() };

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