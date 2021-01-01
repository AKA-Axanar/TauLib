#pragma once

///
/// @file
/// @brief Header file for Win class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include <string>
#include "TauLib.h"
#include "SDL.h"
#include "SDL_shared.h"
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
    Uint32 flags = SDL_WINDOW_SHOWN;    

    SDL_Shared<SDL_Window> window = nullptr;
    bool windowIsEntireDisplay = false;
    bool isOpen = false;

    Win() {}

    ///
    /// @brief Win constructor
    /// @param title
    /// @param posit position of the window
    /// @param width width of the window
    /// @param height height of the window
    /// @param flags [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    ///
    Win(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 _flags);

    ///
    /// @brief Init - Initialize the Window object
    ///
    /// @param title
    /// @param posit position of the window
    /// @param width width of the window
    /// @param height height of the window
    /// @param flags [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    ///
    bool Init(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 _flags);

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