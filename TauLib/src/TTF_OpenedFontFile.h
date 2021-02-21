#pragma once

#include "TTF_Font_Shared.h"
#include <vector>

///
/// @file
/// @brief Header file for TTF_OpenedFontSizes which is a collection of already open TTF_Font's..
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

// Opening and closin a TTF_Font takes an average of 0.14 ms.  
// Opening and closing a FC_Font (which pre-caches the texture of all the characters) takes an average of 5 ms.

//
// TTF_OpenedFontSize
//
struct TTF_OpenedFontSize {
    TTF_Font_Shared ttf_font;
    int pointSize;
    int fontDisplayHeight;  // the height of the font.  it's usually larger than the point size.
    bool ok { false };

    // create a successfully opened font point size
    TTF_OpenedFontSize(TTF_Font_Shared _ttf_font, int _pointSize) 
        : ttf_font(_ttf_font), pointSize(_pointSize), ok(true) { }

    // create a failed to open font (ok = false)
    TTF_OpenedFontSize(int _pointSize) : pointSize(_pointSize) { }

    operator TTF_Font_Shared() { return ttf_font; }
    operator TTF_Font*() { return ttf_font; }
    friend std::ostream& operator << (std::ostream& os, const TTF_OpenedFontSize& openedFontSize);
};

//
// TTF_OpenedFontFile
//
struct TTF_OpenedFontFile {
    std::string fullFilePath;       // fullpath to TTF font file
    std::vector<TTF_OpenedFontSize> openedFontSizes;

    TTF_OpenedFontFile() { }
    TTF_OpenedFontFile(const std::string& _fullFilePath) { OpenFile(_fullFilePath); }
    bool OpenFile(const std::string& _fullFilePath);

    // return if the open font size is in the vector
    bool FoundFontSize(int pointSize);

    // if the size already exists, return the TTF_OpenedFontSize.
    // if it doesn't already exist, create one and return it.
    TTF_OpenedFontSize GetOpenedFontSize(int pointSize);

    void Clear() { fullFilePath = ""; openedFontSizes.clear(); }
    friend std::ostream& operator << (std::ostream& os, const TTF_OpenedFontFile& openedFontFile);
};
