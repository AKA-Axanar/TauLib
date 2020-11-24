#pragma once

#include <string>
#include "TauLib.h"
#include "SDL.h"
#include "SDL_shared.h"

namespace Tau { // too avoid conflict with other libraries

//*******************************
// Win
//*******************************
    
struct Win
{
    std::string title;
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    int width = 1280;
    int height = 720;
    Uint32 flags = SDL_WINDOW_SHOWN;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool isOpen = false;

    Win() {}
    Win(const std::string& _title, int _x, int _y, int _width, int _height, Uint32 _flags);
    ~Win();

    bool Init();
    void pollEvents();
    void clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 0) const;
    void closeWindow();
};

}