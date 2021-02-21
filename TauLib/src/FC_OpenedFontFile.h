#pragma once

#include "FC_Font_Shared.h"
#include "Tau_Color.h"
#include "SDL_Shared.h"
#include <vector>

///
/// @file
/// @brief Header file for FC_OpenedFontFile which is a collection of already open FC_Font's..
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
    int fontDisplayHeight;  // the height of the font.  it's usually larger than the point size.
    Tau_Color color;
    bool ok { false };

    // create a successfully opened font point size
    FC_OpenedFontSize(FC_Font_Shared _fc_font, int _pointSize, Tau_Color _color) 
        : fc_font(_fc_font), pointSize(_pointSize), color(_color), ok(true) { }

    // create a failed to open font (ok = false)
    FC_OpenedFontSize(int _pointSize, Tau_Color _color) 
        : pointSize(_pointSize), color(_color) { }

    operator FC_Font_Shared() { return fc_font; }
    operator FC_Font*() { return fc_font; }
    friend std::ostream& operator << (std::ostream& os, const FC_OpenedFontSize& openedFontSize);
};

//
// FC_OpenedFontFile
//
struct FC_OpenedFontFile {
    std::string fullFilePath;       // fullpath to FC font file
    SDL_Shared<SDL_Renderer> renderer;
    std::vector<FC_OpenedFontSize> openedFontSizes;
    // default color is for when you search for an FC font of a certain size and you don't care about the
    // color as you are going to pass an override color to the draw routine.  if no font of the requested
    // size exists, the defaultColor is the color it will create the new font size with.
    Tau_Color defaultColor {Tau_white};

    FC_OpenedFontFile() { }
    FC_OpenedFontFile(const std::string& _fullFilePath, SDL_Shared<SDL_Renderer> _renderer) { OpenFile(_fullFilePath, _renderer); }
    bool OpenFile(const std::string& _fullFilePath, SDL_Shared<SDL_Renderer> _renderer);

    // return if the open font size & color is in the vector
    bool FoundFontSize(int pointSize, const Tau_Color& color);
    bool FoundFontSize(int pointSize) { return FoundFontSize(pointSize, defaultColor); }

    // if the size & color already exists, return the FC_OpenedFontSize.
    // if it doesn't already exist, create one and return it.
    FC_OpenedFontSize GetOpenedFontSize(int pointSize, const Tau_Color& color);
    FC_OpenedFontSize GetOpenedFontSize(int pointSize);

    void Clear() { fullFilePath = ""; renderer.sdl_shared_ptr.reset(); openedFontSizes.clear(); }
    friend std::ostream& operator << (std::ostream& os, const FC_OpenedFontFile& openedFontFile);
};
