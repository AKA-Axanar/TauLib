#include "TTF_OpenedFontSizes.h"
#include "DirFile.h"
#include <algorithm>

using namespace std;
using namespace Tau;

///
/// @file
/// @brief CPP file for TTF_OpenedFontSizes which is a collection of already open TTF_Font's..
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

//
// TTF_OpenedFontSizes
//
TTF_OpenedFontSizes::TTF_OpenedFontSizes(const std::string& _fullFilePath) : fullFilePath(_fullFilePath) {
    // create an empty TTF_OpenedFontSizes.  call GetOpenedFontSize() to add a font at a point size.
}

//
// FoundFontSize
// return if the open font size is in the vector
//
bool TTF_OpenedFontSizes::FoundFontSize(int pointSize) {
    // see if the requested point size is already in the vector.
    auto it = find_if(begin(openedFontSizes), end(openedFontSizes), [&] (const TTF_OpenedFontSize& ofont) { return ofont.pointSize == pointSize; });
    return it != end(openedFontSizes);
}


//
// GetOpenedFontSize
// if the size already exists, return the TTF_OpenedFontSize.
// if it doesn't already exist, create one and return it.
//
TTF_OpenedFontSize TTF_OpenedFontSizes::GetOpenedFontSize(int pointSize) {
    // first see if the requested point size is already in the vector.  if so, return it.
    auto it = find_if(begin(openedFontSizes), end(openedFontSizes), [&] (const TTF_OpenedFontSize& ofont) { return ofont.pointSize == pointSize; });
    if (it != end(openedFontSizes))
        return *it;         // the font size is already in openedFontSizes

    if (!FileExists(fullFilePath))
        return TTF_OpenedFontSize(pointSize);     // failure

    // the file exists and the requested point size is not saved in the vector
    // make a new shared font with the requested point size.
    TTF_Font_Shared ttf_font(fullFilePath, pointSize);
    if (ttf_font) {
        TTF_OpenedFontSize ret(ttf_font, pointSize);
        openedFontSizes.emplace_back(ret);
        // return the point size
        return ret;
    }
    else {
        // font failed to open, return a "ok = false" TTF_OpenedFontSize
        return TTF_OpenedFontSize(pointSize);
    }

}
