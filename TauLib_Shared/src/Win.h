#pragma once

#include <string>
#include "TauLib.h"
#include "SDL.h"

namespace Tau {

//*******************************
// Win
//*******************************
    
struct TAULIBDLL_API Win
{
    std::string title;
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    int width = 1280;
    int height = 720;
    Uint32 flags = SDL_WINDOW_SHOWN;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool open = false;

    Win(const std::string& _title, int _x, int _y, int _width, int _height, Uint32 _flags);
    ~Win();

    bool Init();
};

}