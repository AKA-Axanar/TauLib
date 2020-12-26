#pragma once

///
/// @file
/// @brief Header file for a shared FC_Font* (a TTF_Font with a cached texture of the characters for better performance).  
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///
/// @note See SDL_Shared.h for a more advanced example.  In this case we don't need a templated destructor based on the type.
/// See TTF_Font_Shared.h for a regular shared TTF_Font ptr.
/// 
/// A shared font ptr can be passed to an object for later use.  When the last copy of the 
/// shared ptr is destroyed the usage count goes to zero and the font is closed.
/// 
/// A FC_Font_Shared is a FC_Font* which came from third party code that caches the font character textures.
/// This allows you to draw directly on the screen without going create a texture for better perforamance.  SDL_FontCache source is available
/// on [GitHub] (https://github.com/grimfang4/SDL_FontCache).
/// 
/// @code
/// Useful FC_Font (Font Cache) functions
/// 
/// Getting and setting the default color.
/// SDL_Color FC_GetDefaultColor(FC_Font* font);
/// void FC_SetDefaultColor(FC_Font* font, SDL_Color color);
/// 
/// FC_Font Rendering
/// 
/// FC_Rect FC_Draw(FC_Font* font, FC_Target* dest, float x, float y, const char* formatted_text, ...);
/// FC_Rect FC_DrawAlign(FC_Font* font, FC_Target* dest, float x, float y, FC_AlignEnum align, const char* formatted_text, ...);
/// FC_Rect FC_DrawScale(FC_Font* font, FC_Target* dest, float x, float y, FC_Scale scale, const char* formatted_text, ...);
/// FC_Rect FC_DrawColor(FC_Font* font, FC_Target* dest, float x, float y, SDL_Color color, const char* formatted_text, ...);
/// FC_Rect FC_DrawEffect(FC_Font* font, FC_Target* dest, float x, float y, FC_Effect effect, const char* formatted_text, ...);
/// 
/// FC_Rect FC_DrawBox(FC_Font* font, FC_Target* dest, FC_Rect box, const char* formatted_text, ...);
/// FC_Rect FC_DrawBoxAlign(FC_Font* font, FC_Target* dest, FC_Rect box, FC_AlignEnum align, const char* formatted_text, ...);
/// FC_Rect FC_DrawBoxScale(FC_Font* font, FC_Target* dest, FC_Rect box, FC_Scale scale, const char* formatted_text, ...);
/// FC_Rect FC_DrawBoxColor(FC_Font* font, FC_Target* dest, FC_Rect box, SDL_Color color, const char* formatted_text, ...);
/// FC_Rect FC_DrawBoxEffect(FC_Font* font, FC_Target* dest, FC_Rect box, FC_Effect effect, const char* formatted_text, ...);
/// 
/// FC_Rect FC_DrawColumn(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, const char* formatted_text, ...);
/// FC_Rect FC_DrawColumnAlign(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, FC_AlignEnum align, const char* formatted_text, ...);
/// FC_Rect FC_DrawColumnScale(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, FC_Scale scale, const char* formatted_text, ...);
/// FC_Rect FC_DrawColumnColor(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, SDL_Color color, const char* formatted_text, ...);
/// FC_Rect FC_DrawColumnEffect(FC_Font* font, FC_Target* dest, float x, float y, Uint16 width, FC_Effect effect, const char* formatted_text, ...);
/// 
/// @endcode

#include <memory>
#include "SDL.h"
#include "SDL_ttf.h"
#include "ThirdParty\SDL_FontCache.h"
#include "TTF_Font_Shared.h"
#include <string>

///
/// @struct FC_Font_Shared
/// FC_Font is a font cache for fonts.  it allows you to not have to create a texture every time you draw text.
///
struct FC_Font_Shared {
    std::shared_ptr<FC_Font> font_shared_ptr;

    FC_Font_Shared(const std::string& filename, int fontSize, SDL_Renderer* renderer, SDL_Color color) {
        FC_Font* font = FC_CreateFont();
        Uint8 ret = FC_LoadFont(font, renderer, filename.c_str(), fontSize, color, 0);
        if (ret != 0)
            font_shared_ptr.reset(font, [](FC_Font *font) { if (font) FC_FreeFont(font); });
        else
            cerr << "error opening font: " << filename << endl;
}

    operator FC_Font* () { return font_shared_ptr.get(); };
    FC_Font & operator * () { return *font_shared_ptr.get(); };
    FC_Font * operator -> () { return font_shared_ptr.get(); };
};
