///
/// @file
/// @brief CPP file for DrawArea class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "DrawArea.h"
#include <SDL_image.h>
#include <string>
#include "TauLib.h"
#include "SDL.h"
#include "DirFile.h"

using namespace std;
using namespace Tau;

namespace Tau { // to avoid conflict with other libraries

//
// DrawArea
//
DrawArea::DrawArea(SDL_Shared<SDL_Renderer> _renderer, const Tau_Rect& _rect) : renderer(_renderer), drawAreaRect(_rect) { }

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
            FillRect(drawAreaRect, defaultFillColor);
        if (enableDefaultImage)
            DrawTextureToRect(defaultImageTexture, drawAreaRect);
    }
}

//
// MoveBy
//
void DrawArea::MoveBy(Tau_Distance distance)
{
    drawAreaRect.x += distance.x;
    drawAreaRect.y += distance.y;
    for (auto& area : subAreas)
        area.MoveBy(distance);
}

//
// MoveTo
//
void DrawArea::MoveTo(Tau_Point point)
{
    Tau_Distance distance = point - drawAreaRect.GetPoint();
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
//  FillWin - fill the window with a color
//
void DrawArea::FillWin(Tau_Color color) {
    SetColor(color);
    SDL_RenderClear(renderer);
}

//
// ClearWin - clear the window. defaults to black.  calls SDL_RenderPresent
//
void DrawArea::ClearWin(Tau_Color color) {
    FillWin(color);
    SDL_RenderPresent(renderer);
}

//                  ===========
//                   Fill Rect
//                  ===========

//
// FillRect - fill an Tau_Rect with current color or blend
//
void DrawArea::FillRect(const Tau_Rect& rect) {
    SDL_RenderFillRect(renderer, &rect);
}

//
// FillRect - fill an Tau_Rect with a color
//
void DrawArea::FillRect(const Tau_Rect& rect, Tau_Color color) {
    SetColor(color);
    FillRect(rect);
}

//                  ===========
//                  Image Texture
//                  ===========

//
// GetTextureOfImage
// 
SDL_Shared<SDL_Texture> DrawArea::GetTextureOfImage(const string& imgFilePath) {
    if (!FileExists(imgFilePath))
        cerr << "image file does not exist: " << imgFilePath << endl;
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
    DrawImageCenteredAt(imgFilePath, drawAreaRect.Center());
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
    return DrawTextCenteredAt(font, text, color, drawAreaRect.Center());
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
// DrawTextHorizCenteredInWindow
// 
int DrawArea::DrawTextHorizCenteredInWindow(TTF_Font_Shared font, const std::string& text, SDL_Color color, int y) {
    return DrawTextCenteredAt(font, text, color, { drawAreaRect.Center().x, y });
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
//                   Draw FC Text
//                   Overrides the FC_Font color
//                  ===========

//
// DrawTextAt Draws the text at a point on the window
// 
int DrawArea::DrawTextAt(FC_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    FC_Rect rect = FC_DrawColor(font, renderer, (float)point.x, (float)point.y, color, text.c_str());
    return rect.h;
}

//
// DrawTextCenteredAt Draws the text centered on a point on the window
// 
int DrawArea::DrawTextCenteredAt(FC_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    int h = FC_GetHeight(font, text.c_str());
    int w = FC_GetWidth(font, text.c_str());
    Tau_Size size { w, h };
    DrawTextAt(font, text, color, point - size.GetCenter());    // adjust the corner so that point is the center of the text
    return h;
}

//
// DrawTextCenteredInWindow Draws the text centered in the window
// 
int DrawArea::DrawTextCenteredInWindow(FC_Font_Shared font, const std::string& text, SDL_Color color) {
    return DrawTextCenteredAt(font, text, color, drawAreaRect.Center());
}

//
// DrawTextHorizCenteredAt Draws the text horizontally centered on a point on the window.  
// 
int DrawArea::DrawTextHorizCenteredAt(FC_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    int h = FC_GetHeight(font, text.c_str());
    int w = FC_GetWidth(font, text.c_str());
    Tau_Size size { w, h };
    Tau_Point newPoint = { point.x - size.w/2, point.y };
    return DrawTextAt(font, text, color, newPoint);
}

//
// DrawTextHorizCenteredInWindow
// 
int DrawArea::DrawTextHorizCenteredInWindow(FC_Font_Shared font, const std::string& text, SDL_Color color, int y) {
    return DrawTextCenteredAt(font, text, color, { drawAreaRect.Center().x, y });
}

//
// DrawTextUpperRightCornerAt Draws the text such that the upper right corner is at the passed point.  
// 
int DrawArea::DrawTextUpperRightCornerAt(FC_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point) {
    int w = FC_GetWidth(font, text.c_str());
    Tau_Point newPoint = { point.x - w, point.y };
    return DrawTextAt(font, text, color, newPoint);
}

//                  ===========
//                   Draw FC Text
//                   Same as the above routines but uses the color the FC_Font was created with
//                  ===========

//
// DrawTextAt Draws the text at a point on the window
// 
int DrawArea::DrawTextAt(FC_Font_Shared font, const std::string& text, const Tau_Point& point) {
    FC_Rect rect = FC_Draw(font, renderer, (float)point.x, (float)point.y, text.c_str());
    return rect.h;
}

//
// DrawTextCenteredAt Draws the text centered on a point on the window
// 
int DrawArea::DrawTextCenteredAt(FC_Font_Shared font, const std::string& text, const Tau_Point& point) {
    int h = FC_GetHeight(font, text.c_str());
    int w = FC_GetWidth(font, text.c_str());
    Tau_Size size { w, h };
    DrawTextAt(font, text, point - size.GetCenter());    // adjust the corner so that point is the center of the text
    return h;
}

//
// DrawTextCenteredInWindow Draws the text centered in the window
// 
int DrawArea::DrawTextCenteredInWindow(FC_Font_Shared font, const std::string& text) {
    return DrawTextCenteredAt(font, text, drawAreaRect.Center());
}

//
// DrawTextHorizCenteredAt Draws the text horizontally centered on a point on the window.  
// 
int DrawArea::DrawTextHorizCenteredAt(FC_Font_Shared font, const std::string& text, const Tau_Point& point) {
    int h = FC_GetHeight(font, text.c_str());
    int w = FC_GetWidth(font, text.c_str());
    Tau_Size size { w, h };
    Tau_Point newPoint = { point.x - size.w/2, point.y };
    return DrawTextAt(font, text, newPoint);
}

//
// DrawTextHorizCenteredInWindow
// 
int DrawArea::DrawTextHorizCenteredInWindow(FC_Font_Shared font, const std::string& text, int y) {
    return DrawTextCenteredAt(font, text, { drawAreaRect.Center().x, y });
}

//
// DrawTextUpperRightCornerAt Draws the text such that the upper right corner is at the passed point.  
// 
int DrawArea::DrawTextUpperRightCornerAt(FC_Font_Shared font, const std::string& text, const Tau_Point& point) {
    int w = FC_GetWidth(font, text.c_str());
    Tau_Point newPoint = { point.x - w, point.y };
    return DrawTextAt(font, text, newPoint);
}

//                  ===========
//                  Get Texture Size
//                  ===========

//
// GetSizeOfTexture
// 
Tau_Size DrawArea::GetSizeOfTexture(SDL_Shared<SDL_Texture> texture) {
    Tau_Size size;
    if (texture)
        SDL_QueryTexture(texture, NULL, NULL, &size.w, &size.h); // get the width and height of the texture
    else
        cerr << "nullptr texture passed to GetSizeOfTexture" << endl;
    return size;
}

//                  ===========
//                  Draw Texture
//                  ===========

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
// DrawTextureCenteredInWindow Draws the entire image centered in the window
//

void DrawArea::DrawTextureCenteredInWindow(SDL_Shared<SDL_Texture> texture) {
    DrawTextureCenteredAt(texture, drawAreaRect.Center());
}

//
// DrawTextureToRect
// 
int DrawArea::DrawTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& destRect) {
    if (texture)
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    else
        cerr << "nullptr texture passed to DrawTextureToRect" << endl;
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
    if (texture)
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    else
        cerr << "nullptr texture passed to DrawSectionOfTextureToRect" << endl;
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
