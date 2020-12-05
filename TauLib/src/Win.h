#pragma once

/**
 *  @file
 *
 *  Header file for Window class.
 *
 */

#include <string>
#include "TauLib.h"
#include "SDL.h"
#include "SDL_shared.h"

/**
 *  \brief avoid conflict with other libraries
 */
namespace Tau { // to avoid conflict with other libraries

enum POSITION { UL_CORNER, CENTERED_AT, CENTER_OF_WINDOW };

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

    SDL_Shared<SDL_Window> window = nullptr;
    SDL_Shared<SDL_Renderer> renderer = nullptr;
    bool isOpen = false;

    Win() {}
    Win(const std::string& _title, int _x, int _y, int _width, int _height, Uint32 _flags);
    ~Win();

    bool Init(const std::string& _title, int _x, int _y, int _width, int _height, Uint32 _flags);

    void FillWin(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);
    void FillRect(const SDL_Rect& rect, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);

    void DrawImage(const std::string& imgFile, const SDL_Rect& rect);
    void DrawImage(const std::string& imgFile, const SDL_Point& point, POSITION posit = UL_CORNER);

    void ClearWin(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);
    void Close();
};

} // end namespace Tau