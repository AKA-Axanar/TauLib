#pragma once

///
/// @file
/// Header file for Win class.

#include <string>
#include "TauLib.h"
#include "SDL.h"
#include "SDL_shared.h"

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief POINT_POSITION - The position of a passed point
///
enum POINT_POSITION { UL_CORNER, CENTERED_AT, CENTER_OF_WINDOW };

///
/// @class Win
/// @brief SDL WIndow class
///
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

    ///
    /// @brief Win constructor
    /// @param title
    /// @param x
    /// @param y
    /// @param width
    /// @param height
    /// @param flags - options
    ///
    Win(const std::string& _title, int _x, int _y, int _width, int _height, Uint32 _flags);

    ///
    /// @brief ~Win destructor
    ///
    ~Win();

    ///
    /// @brief Init - Initialize the Window object
    ///
    /// @param title
    /// @param x
    /// @param y
    /// @param width
    /// @param height
    /// @param flags - options
    ///
    bool Init(const std::string& _title, int _x, int _y, int _width, int _height, Uint32 _flags);

    ///
    /// @brief FillWin - fill the window with a color
    ///
    /// @param r red
    /// @param g green
    /// @param b blue
    /// @param alpha
    ///
    void FillWin(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);

    ///
    /// @brief FillWin - fill the window with a color
    /// @param color The color to fill the window with
    ///
    void FillWin(SDL_Color color);

    ///
    /// @brief FillRect - fill an SDL_Rect with a color
    /// @param rect SDL_Rect rectangle to fill
    /// @param r red
    /// @param g green
    /// @param b blue
    /// @param alpha
    ///
    void FillRect(const SDL_Rect& rect, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);

    ///
    /// @brief FillRect - fill an SDL_Rect with a color
    /// @param rect rectangle to fill
    /// @param color Color to fill
    ///
    void FillRect(const SDL_Rect& rect, SDL_Color color);

    ///
    /// @brief DrawEntireImage Draws the entire image on the window at a point on the window
    /// @param imgFilePath The image file path
    /// @param point The point to draw the image
    /// @param point_posit Whether point is the upper left corner of the image or the s=center of the image
    ///
    void DrawEntireImage(const std::string& imgFilePath, const SDL_Point& point, POINT_POSITION point_posit = UL_CORNER);

    ///
    /// @brief DrawImageToRect
    /// @param imgFilePath The image file path
    /// @param rect The rectangle area in the window to draw the image
    /// @remark the image will be scaled to fit in the rect
    /// 
    void DrawImageToRect(const std::string& imgFilePath, const SDL_Rect& rect);

    ///
    /// @brief GetTextureAndSizeOfImage
    /// @param imgFilePath The image file path
    /// @param &rect return width and height of image
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    SDL_Shared<SDL_Texture> GetTextureAndSizeOfImage(const std::string& imgFilePath, SDL_Rect *rect = nullptr);

    ///
    /// @brief DrawSectionOfTexture
    /// @param texture probably from calling GetTextureAndSizeOfImage
    /// @param srcRect The rectangle area in the texture to draw
    /// @param destRect The rectangle area in the window to draw the srcRect
    /// @remark the srcRect will be scaled to fit in the destRect
    /// 
    void DrawSectionOfTexture(SDL_Shared<SDL_Texture> texture, const SDL_Rect& srcRect, const SDL_Rect& destRect);

    ///
    /// @brief ClearWin - clear the window. defaults to black.
    /// @param Uint8 r
    /// @param Uint8 g
    /// @param Uint8 b
    /// @param Uint8 alpha
    ///
    void ClearWin(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);

    ///
    /// @brief Close - close the window
    ///
    void Close();
};

} // end namespace Tau