#include "DrawArea.h"
#include <SDL_image.h>
#include <string>
#include "TauLib.h"
#include "SDL.h"

using namespace std;

namespace Tau { // to avoid conflict with other libraries

DrawArea::DrawArea(SDL_Shared<SDL_Renderer> _renderer, const Tau_Rect& _rect) : renderer(_renderer), winArea(_rect) { }

void DrawArea::SetDefaultFill(const Tau_Color& color, bool enable) {
    defaultFillColor = color; 
    enableDefaultFill = enable;
}

void DrawArea::SetDefaultImage(const std::string& filename, bool enable) {
    defaultImageFile = filename;
    enableDefaultImage = enable;
    if (defaultImageFile != "") 
        defaultImageTexture = GetTextureOfImage(defaultImageFile);  // make texture once for better performance
    else
        defaultImageTexture = nullptr;
}

void DrawArea::DrawDefault() {
    if (enableDraw) {
        if (enableDefaultFill)
            FillRect(winArea, defaultFillColor);
        if (enableDefaultImage)
            DrawTextureToRect(defaultImageTexture, winArea);
    }
}

void DrawArea::MoveBy(Tau_Distance distance)
{
    winArea.x += distance.x;
    winArea.y += distance.y;
    for (auto& area : subAreas)
        area.MoveBy(distance);
}

void DrawArea::MoveTo(Tau_Point point)
{
    Tau_Distance distance = point - winArea.GetPoint();
    MoveBy(distance);
}

// Overload this function unless the default action of fill, background image, and sub areas draw is all you need.  For example:
// ::Draw();    // do any base class drawing such as a background image
// do something special here
void DrawArea::Draw()
{
    if (enableDraw)
        DrawDefault();
}

/// @brief Draw this DrawArea and all the subAreas inside
void DrawArea::DrawAll() {
    if (enableDraw) {
        Draw();
        for (auto& area : subAreas)
            area.DrawAll();
    }
}

void DrawArea::AddSubArea(const DrawArea& subArea) {
    subAreas.emplace_back(subArea);
    subAreas.back().renderer = renderer;    // just to make sure it has the right renderer to draw to this window.
}

//                  ===========
//                     Fill Win
//                  ===========

/// @brief DrawArea::FillWin - fill the window with a color
/// @param r red
/// @param g green
/// @param b blue
/// @param alpha
/// @note does not call SDL_RenderPresent
void DrawArea::FillWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

/// @brief FillWin - fill the window with a color
/// @param color The color to fill the window with
/// @note does not call SDL_RenderPresent
void DrawArea::FillWin(SDL_Color color) {
    FillWin(color.r, color.g, color.b, color.a);
}

/// @brief DrawArea::ClearWin - clear the window. defaults to black.
///
/// @param Uint8 r
/// @param Uint8 g
/// @param Uint8 b
/// @param Uint8 alpha
void DrawArea::ClearWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    FillWin(r, g, b, alpha);
    SDL_RenderPresent(renderer);
}

/// @brief ClearWin - clear the window. defaults to black.
/// @param color
void DrawArea::ClearWin(SDL_Color color = {0,0,0,255}) {
    FillWin(color);
    SDL_RenderPresent(renderer);
}

//                  ===========
//                   Fill Rect
//                  ===========

///
/// @brief DrawArea::FillRect - fill an Tau_Rect with a color
/// @param rect Tau_Rect rectangle to fill
/// @param r red
/// @param g green
/// @param b blue
/// @param alpha
///
void DrawArea::FillRect(const Tau_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

///
/// @brief DrawArea::FillRect - fill an Tau_Rect with a color
/// @param rect rectangle to fill
/// @param color Color to fill
///
void DrawArea::FillRect(const Tau_Rect& rect, SDL_Color color) {
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
SDL_Shared<SDL_Texture> DrawArea::GetTextureOfImage(const string& imgFilePath) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFilePath.c_str());
    return texture;
}

///
/// @brief GetTextureAndSizeOfImage
/// @param imgFilePath The image file path
/// @param &rect return width and height of image
/// @return SDL_Shared<SDL_Texture> texture
/// 
tuple<SDL_Shared<SDL_Texture>, Tau_Size> DrawArea::GetTextureAndSizeOfImage(const string& imgFilePath) {
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
void DrawArea::DrawImageAt(const string& imgFilePath, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfImage(imgFilePath);
    Tau_Rect rect(point, size);

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief DrawImageCenteredAt Draws the entire image centered at a point on the window
/// @param imgFilePath The image file path
/// @param point The center point to draw the image
///
void DrawArea::DrawImageCenteredAt(const std::string& imgFilePath, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfImage(imgFilePath);
    // adjust the corner x,y so that the center of the image is at the point
    Tau_Rect rect ({ point.x - (size.w / 2), point.y - (size.h / 2) }, size );

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief DrawImageCenteredInWindow Draws the entire image centered in the window
/// @param imgFilePath The image file path
///
void DrawArea::DrawImageCenteredInWindow(const std::string& imgFilePath) {
    DrawImageCenteredAt(imgFilePath, winArea.Center());
}

///
/// @brief DrawImageToRect
/// @param imgFilePath The image file path
/// @param rect The rectangle area in the window to draw the image
/// @note the image will be scaled to fit in the rect
///
void DrawArea::DrawImageToRect(const string& imgFilePath, const Tau_Rect& rect) {
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
SDL_Shared<SDL_Texture> DrawArea::GetTextureOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color) {
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
std::tuple<SDL_Shared<SDL_Texture>, Tau_Size> DrawArea::GetTextureAndSizeOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color) {
    if (!font)
        return make_tuple(nullptr, Tau_Size());

    SDL_Shared<SDL_Texture> texture = GetTextureOfText(font,text, color);
    return make_tuple(texture, GetSizeOfTexture(texture));
}

//                  ===========
//                   Draw TTF Text
//                  ===========

///
/// @brief DrawTextAt Draws the text at a point on the window
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @param point The point to draw the image
/// @return The height of the text
/// 
int DrawArea::DrawTextAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto texture = GetTextureOfText(font, text, color);
    DrawTextureAt(texture, point);
    return GetHeightOfTexture(texture);
}

///
/// @brief DrawTextCenteredAt Draws the text centered on a point on the window
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @param point The point to draw the image
/// @return The height of the text
/// 
int DrawArea::DrawTextCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto texture = GetTextureOfText(font, text, color);
    DrawTextureCenteredAt(texture, point);
    return GetHeightOfTexture(texture);
}

///
/// @brief DrawTextCenteredInWindow Draws the text centered in the window
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @return The height of the text
/// 
int DrawArea::DrawTextCenteredInWindow(TTF_Font_Shared font, const std::string& text, SDL_Color color) {
    return DrawTextCenteredAt(font, text, color, winArea.Center());
}

///
/// @brief DrawTextHorizCenteredAt Draws the text horizontally centered on a point on the window.  
/// The center top of the text will be at that point.
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @param point The point to draw the text
/// @return The height of the text
/// 
int DrawArea::DrawTextHorizCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfText(font, text, color);
    Tau_Point newPoint = { point.x - size.w/2, point.y };
    return DrawTextureAt(texture, newPoint);
}

///
/// @brief DrawTextUpperRightCornerAt Draws the text such that the upper right corner is at the passed point.  
/// @param font A shared font ptr
/// @param text The text to draw
/// @param color The color to draw the text
/// @param point The upper right corner point to draw the text
/// @return The height of the text
/// 
int DrawArea::DrawTextUpperRightCornerAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfText(font, text, color);
    Tau_Point newPoint = { point.x - size.w, point.y };
    return DrawTextureAt(texture, newPoint);
}

//                  ===========
//                    Texture
//                  ===========

    ///
    /// @brief GetSizeOfTexture
    /// @param texture The texture to get the size of
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
Tau_Size DrawArea::GetSizeOfTexture(SDL_Shared<SDL_Texture> texture) {
    Tau_Size size;
    SDL_QueryTexture(texture, NULL, NULL, &size.w, &size.h); // get the width and height of the texture
    return size;
}

///
/// @brief DrawTextureAt
/// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
/// @param posit The posit in the window to draw the texture
/// @return The height of the texture
/// 
int DrawArea::DrawTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect rect { posit, size };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    return size.h;
}

///
/// @brief DrawTextureCenteredAt
/// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
/// @param posit The posit in the window to draw the centere of the texture
/// @return The height of the texture
/// 
int DrawArea::DrawTextureCenteredAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect rect { posit - size.GetCenter(), size };   // compute upper left corner point
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    return size.h;
}

///
/// @brief DrawTextureToRect
/// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
/// @param destRect The rectangle area in the window to draw the srcRect
/// @remark the texture will be scaled to fit in the destRect
/// @return The height of the texture
/// 
int DrawArea::DrawTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& destRect) {
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    return destRect.h;
}

///
/// @brief DrawSectionOfTextureAt
/// @param texture probably from calling GetTextureAndSizeOfImage
/// @param srcRect The rectangle area in the texture to draw
/// @param posit The posit in the window to draw the texture
/// @return The height of the drawn dest area
/// 
int DrawArea::DrawSectionOfTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect destRect { posit, srcRect.GetSize() };
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    return destRect.h;
}

///
/// @brief DrawSectionOfTextureToRect
/// @param texture probably from calling GetTextureAndSizeOfImage
/// @param srcRect The rectangle area in the texture to draw
/// @param destRect The rectangle area in the window to draw the srcRect
/// @remark the srcRect will be scaled to fit in the destRect
/// @return The height of the drawn dest area
/// 
int DrawArea::DrawSectionOfTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Rect& destRect) {
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    return destRect.h;
}

//                  ===========
//                     Color
//                  ===========

void DrawArea::SetColor(const Tau_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

Tau_Color DrawArea::GetColor() {
    Tau_Color color;
    SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
    return color;
}

//                  ===========
//                   Draw Line
//                  ===========

void DrawArea::DrawLine(const Tau_Point& p1, const Tau_Point& p2) {
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

void DrawArea::DrawLine(const vector<Tau_Point>& points) {
    if (points.size() >= 2) {
        Tau_Point p1 = points[0];
        for (int i=1; i < points.size(); ++i) {
            Tau_Point p2 = points[i];
            DrawLine(p1, p2);
            p1 = p2;
        }
    }
}

//                  ===========
//                   Draw Line
//                  ===========

void DrawArea::DrawRect(const Tau_Rect& rect) {
    auto temp = rect;
    SDL_RenderDrawRect(renderer, &temp);
}

}
