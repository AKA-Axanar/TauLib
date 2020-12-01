#include "Win.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"

using namespace std;

namespace Tau { // too avoid conflict with other libraries

//*******************************
// Win::Win
//*******************************
Win::Win(const string& _title, int _x, int _y, int _width, int _height, Uint32 _flags)
        : title(_title), x(_x), y(_y), width(_width), height(_height), flags(_flags) {
}

//*******************************
// Win::~Win
//*******************************
Win::~Win() {
}

//*******************************
// Win::Init
//*******************************
bool Win::Init() {
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
    if (flags & SDL_WINDOW_FULLSCREEN)
        SDL_GetRendererOutputSize(renderer, &width, &height);

    isOpen = true;
    return isOpen;
}

//*******************************
// Win::pollEvents
//*******************************
void Win::PollEvents() {
    SDL_Event event;
    while (isOpen && SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Close();
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Close();
                        break;
                }

            case SDL_MOUSEMOTION:
                //cout << event.motion.x << ", " << event.motion.y << endl;
                break;

            case SDL_MOUSEBUTTONDOWN:
                //cout << "button down " << event.motion.x << ", " << event.motion.y << endl;
                break;

            default:
                break;
        }
    }
}

//*******************************
// Win::Fill
//*******************************
void Win::Fill(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

//*******************************
// Win::Clear
//*******************************
void Win::Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    Fill(r, g, b, alpha);
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

}