///
/// @file
/// @brief CPP file for a shared FC_Font* (a TTF_Font with a cached texture of the characters for better performance).  
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///
/// @note See SDL_Shared.h for a more advanced example.  In this case we don't need a templated destructor based on the type.
/// See TTF_Font_Shared.h for a regular shared TTF_Font ptr.
/// 
/// A shared font ptr can be passed to an object for later use.  When the last copy of the 
/// shared ptr is destroyed the usage count goes to zero and the font is closed.
/// 
/// A FC_Font_Shared is a FC_Font* which came from third party code that caches the font character textures.
/// This allows you to draw directly on the screen without recreating the textures for better performance.  SDL_FontCache source is available
/// on [GitHub] (https://github.com/grimfang4/SDL_FontCache).
/// 

#include "FC_Font_Shared.h"
#include <iostream>

using namespace std;

///
/// @brief FC_Font_Shared The last shared_ptr destroyed closes the font.
/// @param filename full path
/// @param fontSize in points (72 per inch)
/// @param renderer The screen renderer.  Needed by the font cache to create the font textures
/// @param color The default color of the font.  It can be changed with FC_SetDefaultColor() and revrieved with FC_GetDefaultColor.
/// 
FC_Font_Shared::FC_Font_Shared(FC_Font* font) : font_shared_ptr(font, [](FC_Font *font)
    { FC_FreeFont(font); } ) {};    // automatically destroy/free when the last shared_ptr goes away

FC_Font_Shared::FC_Font_Shared(const std::string& filename, int fontSize, SDL_Renderer* renderer, SDL_Color color, int style) {
    FC_Font* font = FC_CreateFont();
    Uint8 ret = FC_LoadFont(font, renderer, filename.c_str(), fontSize, color, style);
    if (ret != 0)
        font_shared_ptr.reset(font, [](FC_Font *font) { if (font) FC_FreeFont(font); });
    else
        cerr << "error opening font: " << filename << endl;
}
