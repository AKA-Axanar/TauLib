#include "Win.h"
#include <iostream>

using namespace std;

namespace Tau {

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
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//*******************************
// Win::Init
//*******************************
bool Win::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "SDL_Init failed" << endl;
        return false;
    }
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    open = true;
    return open;
}
}