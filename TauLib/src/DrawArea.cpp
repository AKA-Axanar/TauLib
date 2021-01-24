#include "DrawArea.h"
#include <SDL_image.h>
#include <string>
#include "TauLib.h"
#include "SDL.h"

using namespace std;

namespace Tau { // to avoid conflict with other libraries

//
// DrawArea
//
DrawArea::DrawArea(SDL_Shared<SDL_Renderer> _renderer, const Tau_Rect& _rect) : renderer(_renderer), winRect(_rect) { }

//
// SetDefaultFill
//
void DrawArea::SetDefaultFill(const Tau_Color& color, bool enable) {
    defaultFillColor = color; 
    enableDefaultFill = enable;
}

//
// SetDefaultImage
//
void DrawArea::SetDefaultImage(const std::string& filename, bool enable) {
    defaultImageFile = filename;
    enableDefaultImage = enable;
    if (defaultImageFile != "") 
        defaultImageTexture = GetTextureOfImage(defaultImageFile);  // make texture once for better performance
    else
        defaultImageTexture = nullptr;
}

//
// DrawDefault
//
void DrawArea::DrawDefault() {
    if (enableDraw) {
        if (enableDefaultFill)
            FillRect(winRect, defaultFillColor);
        if (enableDefaultImage)
            DrawTextureToRect(defaultImageTexture, winRect);
    }
}

//
// MoveBy
//
void DrawArea::MoveBy(Tau_Distance distance)
{
    winRect.x += distance.x;
    winRect.y += distance.y;
    for (auto& area : subAreas)
        area.MoveBy(distance);
}

//
// MoveTo
//
void DrawArea::MoveTo(Tau_Point point)
{
    Tau_Distance distance = point - winRect.GetPoint();
    MoveBy(distance);
}

//
// Draw this DrawArea and all the subAreas inside
//
void DrawArea::Draw() {
    if (enableDraw) {
        DrawDefault();
        for (auto& area : subAreas)
            area.Draw();
    }
}

//
// AddSubArea
//
void DrawArea::AddSubArea(const DrawArea& subArea) {
    subAreas.emplace_back(subArea);
    subAreas.back().renderer = renderer;    // just to make sure it has the right renderer to draw to this window.
}

//                  ===========
//                     Fill Win
//                  ===========

//
// FillWin - fill the window with a color
//
void DrawArea::FillWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

//
//  FillWin - fill the window with a color
//
void DrawArea::FillWin(SDL_Color color) {
    FillWin(color.r, color.g, color.b, color.a);
}

//
// ClearWin - clear the window. defaults to black.
//
void DrawArea::ClearWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    FillWin(r, g, b, alpha);
    SDL_RenderPresent(renderer);
}

//
// ClearWin - clear the window. defaults to black.
//
void DrawArea::ClearWin(SDL_Color color = {0,0,0,255}) {
    FillWin(color);
    SDL_RenderPresent(renderer);
}

//                  ===========
//                   Fill Rect
//                  ===========

//
// FillRect - fill an Tau_Rect with a color
//
void DrawArea::FillRect(const Tau_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

//
// FillRect - fill an Tau_Rect with a color
//
void DrawArea::FillRect(const Tau_Rect& rect, SDL_Color color) {
    FillRect(rect, color.r, color.g, color.b, color.a);
}

//                  ===========
//                  Image Texture
//                  ===========

//
// GetTextureOfImage
// 
SDL_Shared<SDL_Texture> DrawArea::GetTextureOfImage(const string& imgFilePath) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFilePath.c_str());
    return texture;
}

//
// GetTextureAndSizeOfImage
// 
tuple<SDL_Shared<SDL_Texture>, Tau_Size> DrawArea::GetTextureAndSizeOfImage(const string& imgFilePath) {
    SDL_Shared<SDL_Texture> texture = GetTextureOfImage(imgFilePath);
    Tau_Size size = GetSizeOfTexture(texture);

    return make_tuple(texture, size);
}

//                  ===========
//                   Draw Image
//                  ===========

//
// DrawImageAt Draws the entire image at a point on the window
//
void DrawArea::DrawImageAt(const string& imgFilePath, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfImage(imgFilePath);
    Tau_Rect rect(point, size);

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

//
// DrawImageCenteredAt Draws the entire image centered at a point on the window
//
void DrawArea::DrawImageCenteredAt(const std::string& imgFilePath, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfImage(imgFilePath);
    // adjust the corner x,y so that the center of the image is at the point
    Tau_Rect rect ({ point.x - (size.w / 2), point.y - (size.h / 2) }, size );

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

//
// DrawImageCenteredInWindow Draws the entire image centered in the window
//
void DrawArea::DrawImageCenteredInWindow(const std::string& imgFilePath) {
    DrawImageCenteredAt(imgFilePath, winRect.Center());
}

//
// DrawImageToRect
//
void DrawArea::DrawImageToRect(const string& imgFilePath, const Tau_Rect& rect) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFilePath.c_str());
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

//                  ===========
//                  Text Texture
//                  ===========

//
// GetTextureOfText
// 
SDL_Shared<SDL_Texture> DrawArea::GetTextureOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color) {
    if (!font)
        return nullptr;

    SDL_Shared<SDL_Surface> surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Shared<SDL_Texture> texture = SDL_CreateTextureFromSurface(renderer, surface);
    return texture;
}

//
// GetTextureAndSizeOfText
// 
std::tuple<SDL_Shared<SDL_Texture>, Tau_Size> DrawArea::GetTextureAndSizeOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color) {
    if (!font)
        return make_tuple(nullptr, Tau_Size());

    SDL_Shared<SDL_Texture> texture = GetTextureOfText(font,text, color);
    return make_tuple(texture, GetSizeOfTexture(texture));
}

//                  ===========
//                   Draw TTF Text
//                  ===========

//
// DrawTextAt Draws the text at a point on the window
// 
int DrawArea::DrawTextAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto texture = GetTextureOfText(font, text, color);
    DrawTextureAt(texture, point);
    return GetHeightOfTexture(texture);
}

//
// DrawTextCenteredAt Draws the text centered on a point on the window
// 
int DrawArea::DrawTextCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto texture = GetTextureOfText(font, text, color);
    DrawTextureCenteredAt(texture, point);
    return GetHeightOfTexture(texture);
}

//
// DrawTextCenteredInWindow Draws the text centered in the window
// 
int DrawArea::DrawTextCenteredInWindow(TTF_Font_Shared font, const std::string& text, SDL_Color color) {
    return DrawTextCenteredAt(font, text, color, winRect.Center());
}

//
// DrawTextHorizCenteredAt Draws the text horizontally centered on a point on the window.  
// 
int DrawArea::DrawTextHorizCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfText(font, text, color);
    Tau_Point newPoint = { point.x - size.w/2, point.y };
    return DrawTextureAt(texture, newPoint);
}

//
// DrawTextUpperRightCornerAt Draws the text such that the upper right corner is at the passed point.  
// 
int DrawArea::DrawTextUpperRightCornerAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    auto [ texture, size ] = GetTextureAndSizeOfText(font, text, color);
    Tau_Point newPoint = { point.x - size.w, point.y };
    return DrawTextureAt(texture, newPoint);
}

//                  ===========
//                    Texture
//                  ===========

//
// GetSizeOfTexture
// 
Tau_Size DrawArea::GetSizeOfTexture(SDL_Shared<SDL_Texture> texture) {
    Tau_Size size;
    SDL_QueryTexture(texture, NULL, NULL, &size.w, &size.h); // get the width and height of the texture
    return size;
}

//
// DrawTextureAt
// 
int DrawArea::DrawTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect rect { posit, size };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    return size.h;
}

//
// DrawTextureCenteredAt
// 
int DrawArea::DrawTextureCenteredAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect rect { posit - size.GetCenter(), size };   // compute upper left corner point
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    return size.h;
}

//
// DrawTextureToRect
// 
int DrawArea::DrawTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& destRect) {
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    return destRect.h;
}

//
// DrawSectionOfTextureAt
// 
int DrawArea::DrawSectionOfTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Posit& posit) {
    Tau_Size size = GetSizeOfTexture(texture);
    Tau_Rect destRect { posit, srcRect.GetSize() };
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    return destRect.h;
}

//
// DrawSectionOfTextureToRect
// 
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
