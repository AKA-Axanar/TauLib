#include "FC_OpenedFontSizes.h"
#include "DirFile.h"
#include <algorithm>

using namespace std;
using namespace Tau;

///
/// @file
/// @brief CPP file for FC_OpenedFontSizes which is a collection of already open FC_Font's..
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

//
// FC_OpenedFontSizes
//
FC_OpenedFontSizes::FC_OpenedFontSizes(const std::string& _fullFilePath, SDL_Shared<SDL_Renderer> _renderer) : fullFilePath(_fullFilePath), renderer(_renderer) {
    // create an empty FC_OpenedFontSizes.  call GetOpenedFontSize() to add a font at a point size.
}

//
// FC_OpenedFontSizes
//
FC_OpenedFontSize FC_OpenedFontSizes::GetOpenedFontSize(int pointSize, const Tau_Color& color) {
    // first see if the requested point size and color is already in the vector.  if so, return it.
    auto it = find_if(begin(openedFontSizes), end(openedFontSizes), [&] (const FC_OpenedFontSize& ofont) 
                                                                    { return ofont.pointSize == pointSize && ofont.color == color; });
    if (it != end(openedFontSizes))
        return *it;         // the font size is already in openedFontSizes

    if (!FileExists(fullFilePath))
        return FC_OpenedFontSize(pointSize, color);     // failure

    // the file exists and the requested point size and color combo  is not saved in the vector
    // make a new shared font with the requested point size.
    FC_Font_Shared fc_font(fullFilePath, pointSize, renderer, color);
    if (fc_font) {
        FC_OpenedFontSize ret(fc_font, pointSize, color);
        openedFontSizes.emplace_back(ret);
        // return the point size
        return ret;
    }
    else {
        // font failed to open, return a "ok = false" FC_OpenedFontSize
        return FC_OpenedFontSize(pointSize, color);
    }
}
