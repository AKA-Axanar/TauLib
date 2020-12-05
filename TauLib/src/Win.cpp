#include "Win.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <assert.h>

using namespace std;

namespace Tau { // to avoid conflict with other libraries


//
// Win ctor
//
Win::Win(const string& _title, int _x, int _y, int _width, int _height, Uint32 _flags)
        : title(_title), x(_x), y(_y), width(_width), height(_height), flags(_flags) {
    Init(_title, _x, _y, _width, _height, _flags);
}


//
// ~Win destructor
//
Win::~Win() {
    Close();
}

//
// Init the object
//
bool Win::Init(const string& _title, int _x, int _y, int _width, int _height, Uint32 _flags) {
    title = _title;
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    flags = _flags;

    window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    if (window == nullptr) {
        cerr << "SDL_CreateWindow failed" << endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        cerr << "SDL_CreateRenderer failed" << endl;
        return false;
    }

    // if the window is full screen get the width and height
    if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP)
        SDL_GetRendererOutputSize(renderer, &width, &height);

    isOpen = true;
    return isOpen;
}


///
/// @brief Win::FillWin - fill the window with a color
///
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
///
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
/// @brief Win::DrawImageToRect
///
/// @param imgFilePath The image file path
/// @param rect The rectangle area in the window to draw the image
///
void Win::DrawImageToRect(const string& imgFilePath, const SDL_Rect& rect) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFilePath.c_str());
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

///
/// @brief Win::DrawImageFullSize Draws the entire image on the window
///
/// @param imgFilePath The image file path
/// @param point The point to draw the image
/// @param point_posit Whether point is the upper left corner of the image or the s=center of the image
///
void Win::DrawImageFullSize(const string& imgFile, const SDL_Point& point, POINT_POSITION point_posit) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFile.c_str());
    SDL_Rect rect;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h); // get the width and height of the texture
    if (point_posit == UL_CORNER) {
        rect.x = point.x; 
        rect.y = point.y;
    }
    else if (point_posit == CENTERED_AT) {
        // adjust the corner x,y so that the center of the image is at the point
        rect.x = point.x - (rect.w / 2);
        rect.y = point.y - (rect.h / 2);
    }
    else if (point_posit == CENTER_OF_WINDOW) {
        // adjust the corner x,y so that the center of the image is at the of the window
        rect.x = (width / 2) - (rect.w / 2);
        rect.y = (height / 2) - (rect.h / 2);
    }
    else
        { assert(false); }
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
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
/// @brief Win::Close - close the window
///
void Win::Close() {
    renderer = nullptr;     // SDL_Shared dtor takes care of calling the proper destroy routine
    window = nullptr;       // SDL_Shared dtor takes care of calling the proper destroy routine
    isOpen = false;
}

} // end namespace Tau