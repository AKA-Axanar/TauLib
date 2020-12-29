#pragma once

///
/// @file
/// @brief Header file for Win class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include <string>
#include "TauLib.h"
#include "SDL.h"
#include "SDL_shared.h"
#include "Tau_Rect.h"

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @struct Win SDL_Window class
///
struct Win
{
    unsigned int displayIndex = 0;                  ///< physical display index starting at 0

    std::string title;                              ///< title of window if not full screen
    Tau_Rect winBounds {{0, 0}, {1280, 720}};
    Uint32 flags = SDL_WINDOW_SHOWN;    

    SDL_Shared<SDL_Window> window = nullptr;
    SDL_Shared<SDL_Renderer> renderer = nullptr;
    bool isOpen = false;

    Win() {}

    ///
    /// @brief Win constructor
    /// @param title
    /// @param posit position of the window
    /// @param width width of the window
    /// @param height height of the window
    /// @param flags [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    ///
    Win(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 _flags);

    ///
    /// @brief ~Win destructor
    ///
    ~Win();

    ///
    /// @brief Init - Initialize the Window object
    ///
    /// @param title
    /// @param posit position of the window
    /// @param width width of the window
    /// @param height height of the window
    /// @param flags [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags)
    ///
    bool Init(unsigned int _displayIndex, const std::string& _title, const Tau_Rect& bounds, Uint32 _flags);

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
    /// @brief DrawImageAt Draws the entire image at a point on the window
    /// @param imgFilePath The image file path
    /// @param point The point to draw the image
    ///
    void DrawImageAt(const std::string& imgFilePath, const Tau_Point& point);

    ///
    /// @brief DrawImageCenteredAt Draws the entire image centered at a point on the window
    /// @param imgFilePath The image file path
    /// @param point The center point to draw the image
    ///
    void DrawImageCenteredAt(const std::string& imgFilePath, const Tau_Point& point);

    ///
    /// @brief DrawImageCenteredInWindow Draws the entire image centered in the window
    /// @param imgFilePath The image file path
    ///
    void DrawImageCenteredInWindow(const std::string& imgFilePath);

    ///
    /// @brief DrawImageToRect
    /// @param imgFilePath The image file path
    /// @param rect The rectangle area in the window to draw the scaled image
    /// @note the image will be scaled to fit in the rect
    /// 
    void DrawImageToRect(const std::string& imgFilePath, const Tau_Rect& rect);

    ///
    /// @brief GetTextureOfImage
    /// @param imgFilePath The image file path
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    SDL_Shared<SDL_Texture> GetTextureOfImage(const std::string& imgFilePath);

    ///
    /// @brief GetSizeOfTexture
    /// @param texture The texture to get the size of
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    Tau_Size GetSizeOfTexture(SDL_Shared<SDL_Texture> texture);

    ///
    /// @brief GetTextureAndSizeOfImage
    /// @param imgFilePath The image file path
    /// @return SDL_Shared<SDL_Texture> texture and Tau_Size size
    /// 
    std::tuple<SDL_Shared<SDL_Texture>, Tau_Size> GetTextureAndSizeOfImage(const std::string& imgFilePath);

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
    void ClearWin(SDL_Color color);

    ///
    /// @brief ClearWin - clear the window. defaults to black.
    /// @param color
    ///
    void ClearWin(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);

    ///
    /// @brief Close - close the window
    ///
    void Close();

static int GetNumberOfDisplays() { return SDL_GetNumVideoDisplays(); }
};

} // end namespace Tau