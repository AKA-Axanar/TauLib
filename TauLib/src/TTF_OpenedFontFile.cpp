#include "TTF_OpenedFontFile.h"
#include "DirFile.h"
#include <algorithm>
#include <ranges>

using namespace std;
using namespace Tau;

///
/// @file
/// @brief CPP file for TTF_OpenedFontSizes which is a collection of already open TTF_Font's..
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

    //TTF_Font_Shared ttf_font;
    //int pointSize;
    //int fontDisplayHeight;  // the height of the font.  it's usually larger than the point size.
    //bool ok { false };

//
// TTF_OpenedFontSize operator <<
//
ostream& operator << (ostream& os, const TTF_OpenedFontSize& rhs) {
    os << "pointSize: " << rhs.pointSize;
    if (rhs.ok) {
        os  << ", height: " << rhs.fontDisplayHeight;
        os << ", pointSize: " << rhs.pointSize << ", height: " << rhs.fontDisplayHeight;
    }
    else {
        os << "OK == FALSE";
    }
    os << endl;
    return os;
}

//
// OpenFile
//
bool TTF_OpenedFontFile::OpenFile(const std::string& _fullFilePath) {
    // create an empty TTF_OpenedFontSizes.  call GetOpenedFontSize() to add a font at a point size.
    Clear();
    if (FileExists(_fullFilePath)) {
        fullFilePath = _fullFilePath;
        return true;
    } else {
        return false;
    }
}

//
// FoundFontSize
// return if the open font size is in the vector
//
bool TTF_OpenedFontFile::FoundFontSize(int pointSize) {
    // see if the requested point size is already in the vector.
    auto it = ranges::find_if(openedFontSizes, [&] (const TTF_OpenedFontSize& ofont) { return ofont.pointSize == pointSize; });
    return it != end(openedFontSizes);
}


//
// GetOpenedFontSize
// if the size already exists, return the TTF_OpenedFontSize.
// if it doesn't already exist, create one and return it.
//
TTF_OpenedFontSize TTF_OpenedFontFile::GetOpenedFontSize(int pointSize) {
    // first see if the requested point size is already in the vector.  if so, return it.
    auto it = ranges::find_if(openedFontSizes, [&] (const TTF_OpenedFontSize& ofont) { return ofont.pointSize == pointSize; });
    if (it != end(openedFontSizes))
        return *it;         // the font size is already in openedFontSizes

    if (!FileExists(fullFilePath))
        return TTF_OpenedFontSize(pointSize);     // failure

    // the file exists and the requested point size is not saved in the vector
    // make a new shared font with the requested point size.
    TTF_Font_Shared ttf_font(fullFilePath, pointSize);
    if (ttf_font) {
        TTF_OpenedFontSize ret(ttf_font, pointSize);
        ret.fontDisplayHeight = TTF_FontHeight(ttf_font);
        openedFontSizes.emplace_back(ret);
        // return the point size
        return ret;
    }
    else {
        // font failed to open, return a "ok = false" TTF_OpenedFontSize
        return TTF_OpenedFontSize(pointSize);
    }
}

//
// TTF_OpenedFontFile operator <<
//
ostream& operator << (ostream& os, const TTF_OpenedFontFile& rhs) {
    os << "font file: " << rhs.fullFilePath << endl;
    for_each(begin(rhs.openedFontSizes), end(rhs.openedFontSizes), [&] (const TTF_OpenedFontSize& openFontSize) { os << openFontSize; });
    return os;
}

