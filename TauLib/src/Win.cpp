#include "Win.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <assert.h>
#include "Display.h"

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
    assert(_displayIndex < (unsigned int)Display::GetNumberOfDisplays());

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

    if (flags & (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN))
        windowIsEntireDisplay = true;

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
/// @brief Win::Close - close the window
///
void Win::Close() {
    renderer = nullptr;     // SDL_Shared dtor takes care of calling the proper destroy routine
    window = nullptr;       // SDL_Shared dtor takes care of calling the proper destroy routine
    isOpen = false;
}

//                  ===========
//                     Fill Win
//                  ===========

/// @brief Win::FillWin - fill the window with a color
/// @param r red
/// @param g green
/// @param b blue
/// @param alpha
/// @note does not call SDL_RenderPresent
void Win::FillWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

/// @brief FillWin - fill the window with a color
/// @param color The color to fill the window with
/// @note does not call SDL_RenderPresent
void Win::FillWin(SDL_Color color) {
    FillWin(color.r, color.g, color.b, color.a);
}

/// @brief Win::ClearWin - clear the window. defaults to black.
///
/// @param Uint8 r
/// @param Uint8 g
/// @param Uint8 b
/// @param Uint8 alpha
void Win::ClearWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    FillWin(r, g, b, alpha);
    SDL_RenderPresent(renderer);
}

/// @brief ClearWin - clear the window. defaults to black.
/// @param color
void Win::ClearWin(SDL_Color color = {0,0,0,255}) {
    FillWin(color);
    SDL_RenderPresent(renderer);
}

//                  ===========
//                   Fill Rect
//                  ===========

///
/// @brief Win::FillRect - fill an Tau_Rect with a color
/// @param rect Tau_Rect rectangle to fill
/// @param r red
/// @param g green
/// @param b blue
/// @param alpha
///
void Win::FillRect(const Tau_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

///
/// @brief Win::FillRect - fill an Tau_Rect with a color
/// @param rect rectangle to fill
/// @param color Color to fill
///
void Win::FillRect(const Tau_Rect& rect, SDL_Color color) {
    FillRect(rect, color.r, color.g, color.b, color.a);
}

//                  ===========
//                  Image Texture
//                  ===========

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

//                  ===========
//                   Draw Image
//                  ===========

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

//                  ===========
//                  Text Texture
//                  ===========

///
/// @brief GetTextureOfText
/// @param 
/// @return SDL_Shared<SDL_Texture> texture
/// 
SDL_Shared<SDL_Texture> Win::GetTextureOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color) {
    if (!font)
        return nullptr;

    SDL_Shared<SDL_Surface> surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Shared<SDL_Texture> texture = SDL_CreateTextureFromSurface(renderer, surface);
    return texture;
}

///
/// @brief GetTextureAndSizeOfText
/// @param 
/// @return SDL_Shared<SDL_Texture> texture and Tau_Size size
/// 
std::tuple<SDL_Shared<SDL_Texture>, Tau_Size> Win::GetTextureAndSizeOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color) {
    if (!font)
        return make_tuple(nullptr, Tau_Size());

    SDL_Shared<SDL_Texture> texture = GetTextureOfText(font,text, color);
    return make_tuple(texture, GetSizeOfTexture(texture));
}

//                  ===========
//                   Draw Text
//                  ===========

///
/// @brief DrawTextAt Draws the text at a point on the window
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @param point The point to draw the image
/// @return none
/// 
void Win::DrawTextAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto texture = GetTextureOfText(font, text, color);
    DrawTextureAt(texture, point);
}

///
/// @brief DrawTextCenteredAt Draws the text centered on a point on the window
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @param point The point to draw the image
/// @return none
/// 
void Win::DrawTextCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto texture = GetTextureOfText(font, text, color);
    DrawTextureCenteredAt(texture, point);
}

///
/// @brief DrawTextCenteredInWindow Draws the text centered in the window
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @return none
/// 
void Win::DrawTextCenteredInWindow(TTF_Font_Shared font, const std::string& text, SDL_Color color) {

}

///
/// @brief DrawTextHorizCenteredAt Draws the text horizontally centered on a point on the window.  
/// The center top of the text will be at that point.
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @param point The point to draw the text
/// @return none
/// 
void Win::DrawTextHorizCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfText(font, text, color);
    Tau_Point newPoint = { point.x - size.w/2, point.y };
    DrawTextureAt(texture, newPoint);
}

///
/// @brief DrawTextUpperRightCornerAt Draws the text such that the upper right corner is at the passed point.  
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @param point The upper right corner point to draw the text
/// @return none
/// 
void Win::DrawTextUpperRightCornerAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfText(font, text, color);
    Tau_Point newPoint = { point.x - size.w, point.y };
    DrawTextureAt(texture, newPoint);
}

//                  ===========
//                    Texture
//                  ===========

    ///
    /// @brief GetSizeOfTexture
    /// @param texture The texture to get the size of
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
Tau_Size Win::GetSizeOfTexture(SDL_Shared<SDL_Texture> texture) {
    Tau_Size size;
    SDL_QueryTexture(texture, NULL, NULL, &size.w, &size.h); // get the width and height of the texture
    return size;
}

///
/// @brief DrawTextureAt
/// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
/// @param posit The posit in the window to draw the texture
/// 
void Win::DrawTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect rect { posit, size };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief DrawTextureCenteredAt
/// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
/// @param posit The posit in the window to draw the centere of the texture
/// 
void Win::DrawTextureCenteredAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect rect { posit - size.GetCenter(), size };   // compute upper left corner point
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief DrawTextureToRect
/// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
/// @param destRect The rectangle area in the window to draw the srcRect
/// @remark the texture will be scaled to fit in the destRect
/// 
void Win::DrawTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& destRect) {
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

///
/// @brief DrawSectionOfTextureAt
/// @param texture probably from calling GetTextureAndSizeOfImage
/// @param srcRect The rectangle area in the texture to draw
/// @param posit The posit in the window to draw the texture
/// 
void Win::DrawSectionOfTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect rect { posit, size };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief DrawSectionOfTextureToRect
/// @param texture probably from calling GetTextureAndSizeOfImage
/// @param srcRect The rectangle area in the texture to draw
/// @param destRect The rectangle area in the window to draw the srcRect
/// @remark the srcRect will be scaled to fit in the destRect
/// 
void Win::DrawSectionOfTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Rect& destRect) {
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

//                  ===========
//                     Color
//                  ===========

void Win::SetColor(const Tau_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

Tau_Color Win::GetColor() {
    Tau_Color color;
    SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
    return color;
}

//                  ===========
//                   Draw Line
//                  ===========

void Win::DrawLine(const Tau_Point& p1, const Tau_Point& p2) {
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

void Win::DrawLine(const vector<Tau_Point>& points) {
    if (points.size() >= 2) {
        Tau_Point p1 = points[0];
        for (int i=1; i < points.size(); ++i) {
            Tau_Point p2 = points[i];
            DrawLine(p1, p2);
            p1 = p2;
        }
    }
}

void Win::DrawRect(const Tau_Rect& rect) {
    auto temp = rect;
    SDL_RenderDrawRect(renderer, &temp);
}

} // end namespace Tau