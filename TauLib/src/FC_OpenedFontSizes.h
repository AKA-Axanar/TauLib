#pragma once

#include "FC_Font_Shared.h"
#include "Tau_Color.h"
#include "SDL_Shared.h"
#include <vector>

///
/// @file
/// @brief Header file for FC_OpenedFontSizes which is a collection of already open FC_Font's..
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

//
// The FC_Font (Font Cache Font) pre-creates textures for all the characters (in the requested color).  When constantly
// redrawing a page this improves performance as the textures for each character do not need to be created each time the screen is refreshed.
// I would not use this class to create a font size in every possible color as that would use a lot of memory unneccessarily and
// also waste time creating a cache for each color.  
// To take an existing FC_Font and use a different color you can either call FC_GetDefaultColor() and FC_SetDefaultColor() to save and 
// restore the color.  There are also calls like FC_DrawColor() that will draw text in a different color.
// See FC_Font_Shared.h for examples of useful FC_Font calls.
//

// Opening and closin a TTF_Font takes an average of 0.14 ms.  
// Opening and closing a FC_Font (which pre-caches the texture of all the characters) takes an average of 5 ms.

//
// FC_OpenedFontSize
//
struct FC_OpenedFontSize {
    FC_Font_Shared fc_font;
    int pointSize;
    Tau_Color color;
    bool ok { false };

    // create a successfully opened font point size
    FC_OpenedFontSize(FC_Font_Shared _fc_font, int _pointSize, Tau_Color _color) 
        : fc_font(_fc_font), pointSize(_pointSize), color(_color), ok(true) { }

    // create a failed to open font (ok = false)
    FC_OpenedFontSize(int _pointSize, Tau_Color _color) 
        : pointSize(_pointSize), color(_color) { }

    // return the height of the font.  it's usually larger than the point size.
    int FontHeight() { return FC_GetLineHeight(fc_font); }

    operator FC_Font_Shared() { return fc_font; }
    operator FC_Font*() { return fc_font; }
};

//
// FC_OpenedFontSizes
//
struct FC_OpenedFontSizes {
    std::string fullFilePath;       // fullpath to FC font file
    SDL_Shared<SDL_Renderer> renderer;
    std::vector<FC_OpenedFontSize> openedFontSizes;

    FC_OpenedFontSizes(const std::string& _fullFilePath, SDL_Shared<SDL_Renderer> _renderer);
    ~FC_OpenedFontSizes() 
        { Clear(); }

    FC_OpenedFontSize GetOpenedFontSize(int pointSize, const Tau_Color& color);

    // Clear() should be called before exiting the app so fonts can be closed and deleted before TTF_Quit().
    // Otherwise the dtor might not be called until after the memory had already been freed by TTF_Quit().
    void Clear() 
        { fullFilePath = ""; openedFontSizes.clear(); }
};
