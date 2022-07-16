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
    /// @brief CreateWinOnDesktop - Creates a window on the desktop.  
    ///
    /// @param title
    /// @param posit position of the window on the desktop (across multiple displays)
    /// @param size size of the window
    /// @param flagsWin [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    /// @param flagsRenderer [SDL_RendererFlags] (https://wiki.libsdl.org/SDL_RendererFlags)
    /// @return bool success/fail
    ///
    // the position is the position across an entire desktop of multiple displays.  you can then create
    // a window offset from that position to create a window any where in that display.
    // Displays::GetInstance().DisplayInfos gives you info about the displays on your system.
    //
    // an example multi display desktop
    //
    //                  x on desktop                x on desktop                        x on desktop
    //                  x = -2560                   x = 0                               x = 3480
    //                  +-----------------------+   +-------------------------------+   +-----------------------+
    //                  |                       |   |                               |   |                       |
    //                  |      display 1        |   |          display 0            |   |      display 2        |
    //                  |                       |   |                               |   |                       |
    //                  |     2560 x 1440       |   |         3840 x 2160           |   |     2560 x 1440       |
    //                  |                       |   |                               |   |                       |
    //                  |                       |   |                               |   |                       |
    //                  +-----------------------+   |                               |   +-----------------------+
    //                                              |                               |                                    
    //                                              |                               |                                    
    //                                              +-------------------------------+
    //
    bool CreateWinOnDesktop(const std::string& title, const Tau_Posit& posit, const Tau_Size& size, Uint32 flagsWin, Uint32 flagsRenderer) {
        return CreateWin(title, posit, size, flagsWin, flagsRenderer);
    }

    ///  @brief CreateWinOnDisplay - creates a window on a particular display.  the position is relative to the upper left corner of the display.
    bool CreateWinOnDisplay(int displayIndex, const std::string& title, const Tau_Posit& posit, const Tau_Size& size, Uint32 flagsWin, Uint32 flagsRenderer);

    ///  @brief CreateWinCenteredOnDisplay - creates a window centered in a particular display.
    bool CreateWinCenteredOnDisplay(int displayIndex, const std::string& title, const Tau_Size& size, Uint32 flagsWin, Uint32 flagsRenderer);

    /// @brief ChangeWinPosit
    void ChangeWinPosit(const Tau_Posit& posit);

    /// @brief ChangeWinSize
    void ChangeWinSize(const Tau_Size& size);

    /// @brief FindDisplayIndexOfX - finds the display that an x position on the desktop is in.
    /// @return display index.  -1 on error.
    int FindDisplayIndexOfX(int x);

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