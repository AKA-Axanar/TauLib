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
    Tau_Rect displayRelativeRect;   // the position and size of the window on the display.
                                    // if this is a full screen window then this is the same as Display::displayBounds
    bool isOpen = false;

    Win() {}

    ///
    /// @brief InitWin - Initialize the Window
    ///
    /// @param title
    /// @param posit position of the window
    /// @param width width of the window
    /// @param height height of the window
    /// @param flags [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    ///
    bool InitWin(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 _flagsWin, Uint32 _flagsRenderer);

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