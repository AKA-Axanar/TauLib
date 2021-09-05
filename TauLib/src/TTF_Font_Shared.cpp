///
/// @file
/// @brief CPP file for TTF_Font_Shared.  
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///
/// @note See SDL_Shared.h for a more advanced example.  In this case we don't need a templated destructor based on the type.
/// See TTF_Font_Cache_Shared.h for a FC_Font shared TTF_Font ptr.
/// 
/// A shared font ptr can be passed to an object for later use.  When the last copy of the 
/// shared ptr is destroyed the usage count goes to zero and the font is closed.
/// 

#include "TTF_Font_Shared.h"

// 
// TTF_Font_Shared The last shared_ptr destroyed closes the font.
//
TTF_Font_Shared::TTF_Font_Shared(TTF_Font* font) : font_shared_ptr(font, [](TTF_Font *font)
    { TTF_CloseFont(font); } ) {};    // automatically destroy/free when the last shared_ptr goes away

// 
// TTF_Font_Shared The last shared_ptr destroyed closes the font.
// 
TTF_Font_Shared::TTF_Font_Shared(const std::string& filename, int fontSize) {
    TTF_Font* font = TTF_OpenFont(filename.c_str(), fontSize);
    if (font)
        font_shared_ptr.reset(font, [](TTF_Font *font) { TTF_CloseFont(font); } );  // automatically destroy/free when the last shared_ptr goes away.
    else
        std::cerr << "error opening font: " << filename << std::endl;
}
