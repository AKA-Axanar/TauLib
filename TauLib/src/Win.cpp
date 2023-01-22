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
#include <ranges>

using namespace std;

namespace Tau { // to avoid conflict with other libraries

//
// CreateWin
// displayIndex starts at 0.  the displayIndex is saved for info only.  the bounds is what determines
// the position and size of the window and if you are specifying a full screen on a specific display.
//
bool Win::CreateWin(const string& _title, const Tau_Posit& posit, const Tau_Size& size, Uint32 flagsWin, Uint32 flagsRenderer) {
    title = _title;
    drawAreaRect = { posit, size };     // this will get updated later

    window = SDL_CreateWindow(title.c_str(), posit.x, posit.y, size.w, size.h, flagsWin);
    if (window == nullptr) {
        cerr << "SDL_CreateWindow failed" << endl;
        assert(false);
        return false;
    }

    // the window is inherited from DrawArea.
    // renderer is in DrawArea as the draw routines need to know the renderer to draw in the window.
    renderer = SDL_CreateRenderer(window, -1, flagsRenderer);
    if (renderer == nullptr) {
        cerr << "SDL_CreateRenderer failed" << endl;
        assert(false);
        return false;
    }

    SDL_GetWindowPosition(window, &displayWindowPosit.x, &displayWindowPosit.y);
    SDL_GetWindowSize(window, &displayWindowSize.w, &displayWindowSize.h);
    displayWindowRect = { displayWindowPosit, displayWindowSize };

    if (flagsWin & (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN))
        windowIsEntireDisplay = true;

    // This is the window drawAreaRect.  This is the entire window but 0,0 is the relative corner of the window.
    // When you draw at 0,0 in the drawArea you are drawing at the corner of the window regardless of the position
    // of the window on the display.
    drawAreaRect = { {0,0}, displayWindowSize };

    isOpen = true;
    return isOpen;
}

bool Win::CreateWinOnDisplay(int displayIndex, const std::string& title, const Tau_Posit& posit, const Tau_Size& size, Uint32 flagsWin, Uint32 flagsRenderer) {
    Tau_Posit positOnDesktop = posit;
    positOnDesktop += Displays::GetInstance().DisplayInfos[displayIndex].posit;

    return CreateWinOnDesktop(title, positOnDesktop, size, flagsWin, flagsRenderer);
}

bool Win::CreateWinCenteredOnDisplay(int displayIndex, const std::string& title, const Tau_Size& size, Uint32 flagsWin, Uint32 flagsRenderer) {
    Tau_Posit posit = CenterSizeInRect(size, Displays::GetInstance().DisplayInfos[displayIndex].desktopBounds);
    return CreateWinOnDesktop(title, posit, size, flagsWin, flagsRenderer);
}

void Win::ChangeWinPosit(const Tau_Posit& posit) {
    SDL_SetWindowPosition(window, posit.x, posit.y);
    displayWindowPosit = posit;
    displayWindowRect = { posit, displayWindowSize };
}

void Win::ChangeWinSize(const Tau_Size& size) {
    SDL_SetWindowSize(window, size.w, size.h);
    displayWindowSize = size;
    displayWindowRect = { displayWindowPosit, size };
}

// returns -1 on error
int Win::FindDisplayIndexOfX(int x) {
    for (const auto& info : Displays::GetInstance().DisplayInfos) {
        if (x >= info.posit.x && x < info.posit.x + info.size.w)
            return info.displayIndex;
    }
    return -1;
}

#if 0
//
// CreateCenteredWin - Creates a centered Window.
//
// @param title
// @param size size of the window
// @param flagsWin [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
// @param flagsRenderer [SDL_RendererFlags] (https://wiki.libsdl.org/SDL_RendererFlags)
// @return bool success/fail
//
bool Win::CreateCenteredWin(int displayIndex,
    const std::string& title,           // if either FULLSCREEN flags are set the window is borderless and there is no title bar.

    const Tau_Size& size,               // the size of the window.  or if SDL_WINDOW_FULLSCREEN is set the new resolution of the display

    Uint32 flagsWin,                    // set SDL_WINDOW_FULLSCREEN_DESKTOP to get an entire (borderless) display window at the current resolution.
                                        // set SDL_WINDOW_FULLSCREEN to get an entire display window at a NEW resolution (see size).
                                        // if you don't set either of those flags you get a centered window of size in the displayIndex display.

    Uint32 flagsRenderer) {
    Tau_Posit posit = { (int)SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex), (int)SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex) };
    return CreateWin(title, posit, size, flagsWin, flagsRenderer);        
}
#endif

//
// CreateFullscreenWin.  For when you want a borderless window taking the entire display at the current resolution.
//
bool Win::CreateFullscreenWin(int displayIndex, Uint32 flagsWin, Uint32 flagsRenderer) {
    Tau_Posit posit = Display::GetCenteredDisplayPosit(displayIndex);
    return  CreateWin("", posit, { 0,0 }, flagsWin | SDL_WINDOW_FULLSCREEN_DESKTOP, flagsRenderer);
    }

//
// CreateFullscreenWinNewResolution.  For when you want a borderless window taking the entire display at a new resolution.
//
bool Win::CreateFullscreenWinNewResolution(int displayIndex, const Tau_Size& resolution, Uint32 flagsWin, Uint32 flagsRenderer) {
    Tau_Posit posit = Display::GetCenteredDisplayPosit(displayIndex);
    return  CreateWin("", posit, resolution, flagsWin | SDL_WINDOW_FULLSCREEN, flagsRenderer);
    }
//
// ~Win destructor
//
Win::~Win() {
    if (isOpen)
        DestroyWin();
}

///
/// @brief Win::DestroyWin - close the window
///
void Win::DestroyWin() {
    if (isOpen) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        renderer = nullptr;     // SDL_Shared dtor takes care of calling the proper destroy routine
        window = nullptr;       // SDL_Shared dtor takes care of calling the proper destroy routine
        isOpen = false;
    }
}

} // end namespace Tau
