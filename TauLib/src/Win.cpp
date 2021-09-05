///
/// @file
/// @brief CPP file for Win class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "Win.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <assert.h>

using namespace std;

namespace Tau { // to avoid conflict with other libraries

//
// InitWin
// displayIndex starts at 0.  the displayIndex is saved for info only.  the bounds is what determines
// the position and size of the window and if you are specifying a full screen on a specific display.
//
bool Win::InitWin(const string& _title, const Tau_Rect& bounds, Uint32 flagsWin, Uint32 flagsRenderer) {
    title = _title;
    drawAreaRect = bounds;                   // this will get updated later

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

    SDL_GetWindowPosition(window, &windowPosit.x, &windowPosit.y);
    SDL_GetWindowSize(window, &windowSize.w, &windowSize.h);
    windowRect = { windowPosit, windowSize };

    if (flagsWin & (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN))
        windowIsEntireDisplay = true;

    // This is the window drawAreaRect.  This is the entire window but 0,0 is the relative corner of the window.
    // When you draw at 0,0 in the drawArea you are drawing at the corner of the window regardless of the position
    // of the window on the display.
    drawAreaRect = { {0,0}, windowSize };

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

// to create the window position for a certain display you need to pass a special flag value for the x and y.
// the display index starts at 0
Tau_Posit Win::getDisplayPositFlag(int displayIndex) {
    return { (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex), (int)SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) };
}

} // end namespace Tau