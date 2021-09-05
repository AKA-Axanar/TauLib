#pragma once

///
/// @file
/// @brief Header file for Win class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include <string>
#include "TauLib.h"
#include "SDL.h"
#include "SDL_Shared.h"
#include "Tau_Rect.h"
#include "TTF_Font_Shared.h"
#include "Tau_Color.h"
#include <vector>
#include "DrawArea.h"

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief Win SDL_Window class
///
struct Win : public DrawArea
{
    unsigned int displayIndex = 0;                  ///< physical display index starting at 0

    std::string title;                              ///< title of window if not full screen

    SDL_Shared<SDL_Window> window = nullptr;
    bool windowIsEntireDisplay = false;

    Tau_Posit windowPosit;      // the window position and size on the display or multi-display desktop
    Tau_Size windowSize;
    Tau_Rect windowRect;        // combined as a rect

    bool isOpen = false;

    Win() {}

    ///
    /// @brief InitWin - Initialize the Window.  posit and size are in separate args.
    ///
    /// @param title
    /// @param posit position of the window
    /// @param size size of the window
    /// @param flagsWin [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    /// @param flagsRenderer [SDL_RendererFlags] (https://wiki.libsdl.org/SDL_RendererFlags)
    /// @return bool success/fail
    ///
    bool InitWin(const std::string& title,  //if either FULLSCREEN flags are set the window is borderless and there is no title bar.

        const Tau_Posit& posit, // to get a window in a particular display pass SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex) or
                                // SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) for BOTH x and y.  Note: the display index begins at 0.

        const Tau_Size& size,   // the size of the window.  or if SDL_WINDOW_FULLSCREEN is set the new resolution of the display

        Uint32 flagsWin = 0,    // set SDL_WINDOW_FULLSCREEN_DESKTOP to get an entire (borderless) display window at the current resolution.
                                // set SDL_WINDOW_FULLSCREEN to get an entire display window at a NEW resolution (see size).

        Uint32 flagsRenderer = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
    {
        return InitWin(title, { posit, size }, flagsWin, flagsRenderer);
    }

    ///
    /// @brief InitFullscreenWin.  For when you want a borderless window taking the entire display at the current resolution.
    ///
    bool InitFullscreenWin(int displayIndex) {
        Tau_Posit posit = getDisplayPositFlag(displayIndex);
        return  InitWin("", { posit, { 0,0 } }, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    ///
    /// @brief InitFullscreenWinNewResolution.  For when you want a borderless window taking the entire display at a new resolution.
    ///
    bool InitFullscreenWinNewResolution(int displayIndex, Tau_Size resolution) {
        Tau_Posit posit = getDisplayPositFlag(displayIndex);
        return  InitWin("", { posit, resolution }, SDL_WINDOW_FULLSCREEN);
    }

    ///
    /// @brief InitWin
    /// @param _title
    /// @param bounds bounding rectangle of the window
    /// @param flagsWin [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    /// @param flagsRenderer [SDL_RendererFlags] (https://wiki.libsdl.org/SDL_RendererFlags)
    /// @return bool success/fail
    ///
    bool InitWin(const std::string& _title, 
                const Tau_Rect& bounds, 
                Uint32 flagsWin, 
                Uint32 flagsRenderer = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    ///
    /// @brief ~Win destructor
    ///
    ~Win();

    ///
    /// @brief Close - close the window
    ///
    void Close();

    /// @brief GetNumberOfDisplays - returns the number of displays.  the first display is isndex 0.
    static int GetNumberOfDisplays() { return SDL_GetNumVideoDisplays(); }

    /// @brief isValidDisplay - returns if the passed displayIndex is valid.
    /// @param displayIndex the display index to test if it's a valid index
    static bool isValidDisplay(int displayIndex) { return displayIndex < GetNumberOfDisplays(); }

    /// @brief getDisplayPositFlag
    /// @param displayIndex the display index
    /// @note to create the window position for a certain display you need to pass a special flag value for the x and y.
    /// the display index starts at 0
    static Tau_Posit getDisplayPositFlag(int displayIndex);
};

 } // end namespace Tau