#pragma once

#include "TTF_Font_Shared.h"
#include <vector>

///
/// @file
/// @brief Header file for TTF_OpenedFontSizes which is a collection of already open TTF_Font's..
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

//
// TTF_OpenedFontSize
//
struct TTF_OpenedFontSize {
    TTF_Font_Shared ttf_font;
    int pointSize;
    bool ok { false };

    // create a successfully opened font point size
    TTF_OpenedFontSize(TTF_Font_Shared _ttf_font, int _pointSize) 
        : ttf_font(_ttf_font), pointSize(_pointSize), ok(true) { }

    // create a failed to open font (ok = false)
    TTF_OpenedFontSize(int _pointSize) 
        : pointSize(_pointSize) { }

    operator TTF_Font_Shared() { return ttf_font; }
    operator TTF_Font*() { return ttf_font; }
};

//
// TTF_OpenedFontSizes
//
struct TTF_OpenedFontSizes {
    std::string fullFilePath;       // fullpath to TTF font file
    std::vector<TTF_OpenedFontSize> openedFontSizes;

    TTF_OpenedFontSizes(const std::string& _fullFilePath);
    ~TTF_OpenedFontSizes() 
        { Clear(); }

    TTF_OpenedFontSize GetOpenedFontSize(int pointSize);

    // Clear() should be called before exiting the app so fonts can be closed and deleted before TTF_Quit().
    // Otherwise the dtor might not be called until after the memory had already been freed by TTF_Quit().
    void Clear() 
        { fullFilePath = ""; openedFontSizes.clear(); }
};
