#pragma once

///
/// @file
/// @brief Header file for DrawArea class.
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

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @struct Win SDL_Window class
///
struct DrawArea {
    SDL_Shared<SDL_Renderer> renderer = nullptr;
    Tau_Rect winArea;       ///< The rect area of the window to draw in

    DrawArea() {}
    DrawArea(SDL_Shared<SDL_Renderer> _renderer, const Tau_Rect& rect);
};

}
