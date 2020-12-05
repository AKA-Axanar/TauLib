#include "Win.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <assert.h>

using namespace std;

namespace Tau { // to avoid conflict with other libraries

//*******************************
// Win::Win
//*******************************
Win::Win(const string& _title, int _x, int _y, int _width, int _height, Uint32 _flags)
        : title(_title), x(_x), y(_y), width(_width), height(_height), flags(_flags) {
    Init(_title, _x, _y, _width, _height, _flags);
}

//*******************************
// Win::~Win
//*******************************
Win::~Win() {
    Close();
}

//*******************************
// Win::Init
//*******************************
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

//*******************************
// Win::FillWin
//*******************************
void Win::FillWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

//*******************************
// Win::FillRect
//*******************************
void Win::FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

//
// Win::DrawImage
//
void Win::DrawImage(const string& imgFile, const SDL_Rect& rect) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFile.c_str());
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

//
// Win::DrawImage
//
void Win::DrawImage(const string& imgFile, const SDL_Point& point, POSITION posit) {
    SDL_Shared<SDL_Texture> texture = IMG_LoadTexture(renderer, imgFile.c_str());
    SDL_Rect rect;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h); // get the width and height of the texture
    if (posit == UL_CORNER) {
        rect.x = point.x; 
        rect.y = point.y;
    }
    else if (posit == CENTERED_AT) {
        // adjust the corner x,y so that the center of the image is at the point
        rect.x = point.x - (rect.w / 2);
        rect.y = point.y - (rect.h / 2);
    }
    else if (posit == CENTER_OF_WINDOW) {
        // adjust the corner x,y so that the center of the image is at the of the window
        rect.x = (width / 2) - (rect.w / 2);
        rect.y = (height / 2) - (rect.h / 2);
    }
    else
        { assert(false); }
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

//*******************************
// Win::ClearWin
//*******************************
void Win::ClearWin(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    FillWin(r, g, b, alpha);
    SDL_RenderPresent(renderer);
}

//*******************************
// Win::closeWindow
//*******************************
void Win::Close() {
    renderer = nullptr;     // SDL_Shared dtor takes care of calling the proper destroy routine
    window = nullptr;       // SDL_Shared dtor takes care of calling the proper destroy routine
    isOpen = false;
}

} // end namespace Tau