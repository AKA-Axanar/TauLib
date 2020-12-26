#pragma once

///
/// @file
/// @brief Header file for a shared TTF_Font*.  
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///
/// @note See SDL_Shared.h for a more advanced example.  In this case we don't need a templated destructor based on the type.
/// See TTF_Font_Cache_Shared.h for a FC_Font shared TTF_Font ptr.
/// 
/// A shared font ptr can be passed to an object for later use.  When the last copy of the 
/// shared ptr is destroyed the usage count goes to zero and the font is closed.
/// 

#include <memory>
#include "SDL.h"
#include "SDL_ttf.h"

///
/// @struct TTF_Font_Shared
///
struct TTF_Font_Shared {
    std::shared_ptr<TTF_Font> font_shared_ptr;

    TTF_Font_Shared(TTF_Font* font = nullptr) : font_shared_ptr(font, [](TTF_Font *font)
        { if (font) TTF_CloseFont(font); } ) {};    // automatically destroy/free when the last shared_ptr goes away.

    TTF_Font_Shared(const std::string& filename, int fontSize) : TTF_Font_Shared(TTF_OpenFont(filename.c_str(), fontSize)) { }

    operator TTF_Font* () { return font_shared_ptr.get(); };
    TTF_Font & operator * () { return *font_shared_ptr.get(); };
    TTF_Font * operator -> () { return font_shared_ptr.get(); };
};

