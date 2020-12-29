#include "Win.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <assert.h>

using namespace std;

///
/// @file
/// @brief cpp file for Win class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

namespace Tau { // to avoid conflict with other libraries

//
// Win ctor
//
Win::Win(unsigned int _displayIndex, const string& _title, const Tau_Rect& bounds, Uint32 _flags)
        : title(_title), winBounds(bounds), flags(_flags)
{
    Init(_displayIndex, _title, bounds, _flags);
}

//
// Init the object
//
bool Win::Init(unsigned int _displayIndex, const string& _title, const Tau_Rect& bounds, Uint32 _flags) {
    assert(_displayIndex < (unsigned int)GetNumberOfDisplays());

    displayIndex = _displayIndex;
    title = _title;
    winBounds = bounds;
    flags = _flags;         // https://wiki.libsdl.org/SDL_WindowFlags

    window = SDL_CreateWindow(title.c_str(), bounds.x, bounds.y, bounds.w, bounds.h, flags);
    if (window == nullptr) {
        cerr << "SDL_CreateWindow failed" << endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        cerr << "SDL_CreateRenderer failed" << endl;
        return false;
    }

    isOpen = true;
    return isOpen;
}

//
// ~Win destructor
//
Win::~Win() {
    Close();
}

///
/// @brief Win::FillWin - fill the window with a color
/// @param r red
/// @param g green
/// @param b blue
/// @param alpha
///
void Win::FillWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

///
/// @brief FillWin - fill the window with a color
/// @param color The color to fill the window with
///
void Win::FillWin(SDL_Color color) {
    FillWin(color.r, color.g, color.b, color.a);
}

///
/// @brief Win::FillRect - fill an SDL_Rect with a color
/// @param rect SDL_Rect rectangle to fill
/// @param r red
/// @param g green
/// @param b blue
/// @param alpha
///
void Win::FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

///
/// @brief Win::FillRect - fill an SDL_Rect with a color
/// @param rect rectangle to fill
/// @param color Color to fill
///
void Win::FillRect(const SDL_Rect& rect, SDL_Color color) {
    FillRect(rect, color.r, color.g, color.b, color.a);
}

///
/// @brief DrawImageAt Draws the entire image at a point on the window
/// @param imgFilePath The image file path
/// @param point The point to draw the image
///
void Win::DrawImageAt(const string& imgFilePath, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfImage(imgFilePath);
    Tau_Rect rect(point, size);

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief DrawImageCenteredAt Draws the entire image centered at a point on the window
/// @param imgFilePath The image file path
/// @param point The center point to draw the image
///
void Win::DrawImageCenteredAt(const std::string& imgFilePath, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfImage(imgFilePath);
    // adjust the corner x,y so that the center of the image is at the point
    Tau_Rect rect ({ point.x - (size.w / 2), point.y - (size.h / 2) }, size );

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief DrawImageCenteredInWindow Draws the entire image centered in the window
/// @param imgFilePath The image file path
///
void Win::DrawImageCenteredInWindow(const std::string& imgFilePath) {
    DrawImageCenteredAt(imgFilePath, winBounds.Center());
}

///
/// @brief DrawImageToRect
/// @param imgFilePath The image file path
/// @param rect The rectangle area in the window to draw the image
/// @note the image will be scaled to fit in the rect
///
void Win::DrawImageToRect(const string& imgFilePath, const Tau_Rect& rect) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFilePath.c_str());
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief GetTextureOfImage
/// @param imgFilePath The image file path
/// @return SDL_Shared<SDL_Texture> texture
/// 
SDL_Shared<SDL_Texture> Win::GetTextureOfImage(const string& imgFilePath) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFilePath.c_str());
    return texture;
}

    ///
    /// @brief GetSizeOfTexture
    /// @param texture The texture to get the size of
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
Tau_Size Win:: GetSizeOfTexture(SDL_Shared<SDL_Texture> texture) {
    Tau_Size size;
    SDL_QueryTexture(texture, NULL, NULL, &size.w, &size.h); // get the width and height of the texture
    return size;
}

///
/// @brief GetTextureAndSizeOfImage
/// @param imgFilePath The image file path
/// @param &rect return width and height of image
/// @return SDL_Shared<SDL_Texture> texture
/// 
tuple<SDL_Shared<SDL_Texture>, Tau_Size> Win::GetTextureAndSizeOfImage(const string& imgFilePath) {
    SDL_Shared<SDL_Texture> texture = GetTextureOfImage(imgFilePath);
    Tau_Size size = GetSizeOfTexture(texture);

    return make_tuple(texture, size);
}

///
/// @brief DrawSectionOfTexture
/// @param texture probably from calling GetTextureAndSizeOfImage
/// @param srcRect The rectangle area in the texture to draw
/// @param destRect The rectangle area in the window to draw the srcRect
/// @remark the srcRect will be scaled to fit in the destRect
/// 
void Win::DrawSectionOfTexture(SDL_Shared<SDL_Texture> texture, const SDL_Rect& srcRect, const SDL_Rect& destRect) {
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

///
/// @brief Win::ClearWin - clear the window. defaults to black.
///
/// @param Uint8 r
/// @param Uint8 g
/// @param Uint8 b
/// @param Uint8 alpha
///
void Win::ClearWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    FillWin(r, g, b, alpha);
    SDL_RenderPresent(renderer);
}

///
/// @brief ClearWin - clear the window. defaults to black.
/// @param color
///
void Win::ClearWin(SDL_Color color = {0,0,0,255}) {
    FillWin(color);
    SDL_RenderPresent(renderer);
}

///
/// @brief Win::Close - close the window
///
void Win::Close() {
    renderer = nullptr;     // SDL_Shared dtor takes care of calling the proper destroy routine
    window = nullptr;       // SDL_Shared dtor takes care of calling the proper destroy routine
    isOpen = false;
}

} // end namespace Tau