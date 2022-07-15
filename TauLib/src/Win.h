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
#include "Display.h"

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief Win SDL_Window class
///
struct Win : public DrawArea
{
    bool isOpen = false;
    unsigned int displayIndex = 0;                  ///< physical display index starting at 0
    std::string title;                              ///< title of window if not full screen

    SDL_Shared<SDL_Window> window = nullptr;
    bool windowIsEntireDisplay = false;

    Tau_Posit windowPosit;      // the window position and size on the display or multi-display desktop
    Tau_Size windowSize;
    Tau_Rect windowRect;        // combined as a rect

    Win() {}

    ///
    /// @brief CreateWin - Creates the Window.  posit and size are in separate args.
    ///
    /// @param title
    /// @param posit position of the window
    /// @param size size of the window
    /// @param flagsWin [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    /// @param flagsRenderer [SDL_RendererFlags] (https://wiki.libsdl.org/SDL_RendererFlags)
    /// @return bool success/fail
    ///
    bool CreateWin(const std::string& title,    //if either FULLSCREEN flags are set the window is borderless and there is no title bar.

        const Tau_Posit& posit,                 // to get a window in a particular display pass SDL_WINDOWPOS_CENTERED_DISPLAY(displayIndex) or
                                                // SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex) for BOTH x and y.  Note: the display index begins at 0.

        const Tau_Size& size,                   // the size of the window.  or if SDL_WINDOW_FULLSCREEN is set the new resolution of the display

        Uint32 flagsWin,                        // set SDL_WINDOW_FULLSCREEN_DESKTOP to get an entire (borderless) display window at the current resolution.
                                                // set SDL_WINDOW_FULLSCREEN to get an entire display window at a NEW resolution (see size).

        Uint32 flagsRenderer);

    ///
    /// @brief CreateCenteredWin - Creates a centered Window.
    ///
    /// @param title
    /// @param size size of the window
    /// @param flagsWin [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    /// @param flagsRenderer [SDL_RendererFlags] (https://wiki.libsdl.org/SDL_RendererFlags)
    /// @return bool success/fail
    ///
    bool CreateCenteredWin(int displayIndex, 
        const std::string& title,       // if either FULLSCREEN flags are set the window is borderless and there is no title bar.

        const Tau_Size& size,           // the size of the window.  or if SDL_WINDOW_FULLSCREEN is set the new resolution of the display

        Uint32 flagsWin,                // set SDL_WINDOW_FULLSCREEN_DESKTOP to get an entire (borderless) display window at the current resolution.
                                        // set SDL_WINDOW_FULLSCREEN to get an entire display window at a NEW resolution (see size).
                                        // if you don't set either of those flags you get a centered window of size in the displayIndex display.

        Uint32 flagsRenderer);

    ///
    /// @brief CreateFullscreenWin.  For when you want a borderless window taking the entire display at the current resolution.
    ///
    bool CreateFullscreenWin(int displayIndex, Uint32 flagsWin, Uint32 flagsRenderer);

    ///
    /// @brief CreateFullscreenWinNewResolution.  For when you want a borderless window taking the entire display at a new resolution.
    ///
    bool CreateFullscreenWinNewResolution(int displayIndex, Tau_Size resolution, Uint32 flagsWin, Uint32 flagsRenderer);

    ///
    /// @brief ~Win destructor
    ///
    ~Win();

    ///
    /// @brief DestroyWin - destroys the window
    ///
    void DestroyWin();

};

 } // end namespace Tau