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
/// @struct Win SDL_Window class
///
struct Win : public DrawArea
{
    unsigned int displayIndex = 0;                  ///< physical display index starting at 0

    std::string title;                              ///< title of window if not full screen
    Uint32 flagsWin = SDL_WINDOW_SHOWN;
    Uint32 flagsRenderer = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    SDL_Shared<SDL_Window> window = nullptr;
    bool windowIsEntireDisplay = false;

    Tau_Posit windowPosit;      // the window position and size on the display or multi-display desktop
    Tau_Size windowSize;
    Tau_Rect windowRect;

    bool isOpen = false;

    Win() {}

    ///
    /// @brief InitWin - Initialize the Window
    ///
    /// @param _displayIndex display index starts at 0.  the displayIndex is saved for info only.  the bounds is what determines
    /// the position and size of the window and if you are specifying a full screen on a specific display.
    /// @param title
    /// @param posit position of the window
    /// @param width width of the window
    /// @param height height of the window
    /// @param flagsWin [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    /// @param flagsRenderer [SDL_RendererFlags] (https://wiki.libsdl.org/SDL_RendererFlags)
    ///
    bool InitWin(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 flagsWin, Uint32 flagsRenderer);

    ///
    /// @brief ~Win destructor
    ///
    ~Win();

    ///
    /// @brief Close - close the window
    ///
    void Close();
};

 } // end namespace Tau