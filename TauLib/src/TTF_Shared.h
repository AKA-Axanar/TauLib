#pragma once

///
/// @file
/// @brief Header file for TTF_Shared (Shared TTF_Font and FC_Font).  
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///
/// @note See SDL_Shared.h.  But in this case we don't need a custom destructor.  An ordinary dtor will do.


#include <memory>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_FontCache.h"

///
/// @struct TTF_Font_Shared
///
struct TTF_Font_Shared {
    std::shared_ptr<TTF_Font> font_shared_ptr;

    TTF_Font_Shared(TTF_Font* font = nullptr) : font_shared_ptr(font, [](TTF_Font *font)
        { TTF_CloseFont(font); } ) {};    // automatically destroy/free when the last shared_ptr goes away.

    operator TTF_Font* () { return font_shared_ptr.get(); };
    TTF_Font & operator * () { return *font_shared_ptr.get(); };
    TTF_Font * operator -> () { return font_shared_ptr.get(); };
};

///
/// @struct FC_Font_Shared
/// FC_Font is a font cache for fonts.  it allows you to not have to create a texture every time you draw text.
///
struct FC_Font_Shared {
    std::shared_ptr<FC_Font> font_shared_ptr;

    FC_Font_Shared(FC_Font* font = nullptr) : font_shared_ptr(font, [](FC_Font *font)
    { FC_FreeFont(font); } ) {};    // free allocated structures when the last shared_ptr goes away.
                                    // note that "owns_ttf_source" is false so it will not close the TTF_Font* that was passed to it.
                                    // the passed TTF_Font* is owned by the caller.

    operator FC_Font* () { return font_shared_ptr.get(); };
    FC_Font & operator * () { return *font_shared_ptr.get(); };
    FC_Font * operator -> () { return font_shared_ptr.get(); };
};
