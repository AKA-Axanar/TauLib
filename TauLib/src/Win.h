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
#include "TTF_Font_Shared.h"
#include "Tau_Color.h"
#include <vector>
#include "DrawArea.h"

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @struct Win SDL_Window class
///
struct Win : public DrawArea
{
    unsigned int displayIndex = 0;                  ///< physical display index starting at 0

    std::string title;                              ///< title of window if not full screen
//    Tau_Rect winBounds {{0, 0}, {1280, 720}};       ///< window bounds on the display.
    Uint32 flags = SDL_WINDOW_SHOWN;    

    SDL_Shared<SDL_Window> window = nullptr;
    bool windowIsEntireDisplay = false;
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
    /// @brief ~Win destructor
    ///
    ~Win();

    ///
    /// @brief Close - close the window
    ///
    void Close();

//                  ===========
//                     Fill Win
//                  ===========

    /// @brief FillWin - fill the window with a color
    /// @param r red
    /// @param g green
    /// @param b blue
    /// @param alpha
    /// @note does not call SDL_RenderPresent
    void FillWin(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);

    /// @brief FillWin - fill the window with a color
    /// @param color The color to fill the window with
    /// @note does not call SDL_RenderPresent
    void FillWin(SDL_Color color);

    /// @brief ClearWin - clear the window. defaults to black.
    /// @param Uint8 r
    /// @param Uint8 g
    /// @param Uint8 b
    /// @param Uint8 alpha
    void ClearWin(SDL_Color color);

    /// @brief ClearWin - clear the window. defaults to black.
    /// @param color
    void ClearWin(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);

//                  ===========
//                   Fill Rect
//                  ===========

    ///
    /// @brief FillRect - fill an Tau_Rect with a color
    /// @param rect Tau_Rect rectangle to fill
    /// @param r red
    /// @param g green
    /// @param b blue
    /// @param alpha
    ///
    void FillRect(const Tau_Rect& rect, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 alpha = 255);

    ///
    /// @brief FillRect - fill an Tau_Rect with a color
    /// @param rect rectangle to fill
    /// @param color Color to fill
    ///
    void FillRect(const Tau_Rect& rect, SDL_Color color);

//                  ===========
//                  Image Texture
//                  ===========

    ///
    /// @brief GetTextureOfImage
    /// @param imgFilePath The image file path
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    SDL_Shared<SDL_Texture> GetTextureOfImage(const std::string& imgFilePath);

    ///
    /// @brief GetTextureAndSizeOfImage
    /// @param imgFilePath The image file path
    /// @return SDL_Shared<SDL_Texture> texture and Tau_Size size
    /// 
    std::tuple<SDL_Shared<SDL_Texture>, Tau_Size> GetTextureAndSizeOfImage(const std::string& imgFilePath);

//                  ===========
//                   Draw Image
//                  ===========

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

//                  ===========
//                  Text Texture
//                  ===========

    ///
    /// @brief GetTextureOfText
    /// @param 
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    SDL_Shared<SDL_Texture> GetTextureOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color);

    ///
    /// @brief GetTextureAndSizeOfText
    /// @param 
    /// @return SDL_Shared<SDL_Texture> texture and Tau_Size size
    /// 
    std::tuple<SDL_Shared<SDL_Texture>, Tau_Size> GetTextureAndSizeOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color);

//                  ===========
//                   Draw Text
//                  ===========

    ///
    /// @brief DrawTextAt Draws the text at a point on the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the image
    /// @return none
    /// 
    void DrawTextAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextCenteredAt Draws the text centered on a point on the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the image
    /// @return none
    /// 
    void DrawTextCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextCenteredInWindow Draws the text centered in the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @return none
    /// 
    void DrawTextCenteredInWindow(TTF_Font_Shared font, const std::string& text, SDL_Color color);

    ///
    /// @brief DrawTextHorizCenteredAt Draws the text horizontally centered on a point on the window.  
    /// The center top of the text will be at that point.
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the text
    /// @return none
    /// 
    void DrawTextHorizCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextUpperRightCornerAt Draws the text such that the upper right corner is at the passed point.  
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The upper right corner point to draw the text
    /// @return none
    /// 
    void DrawTextUpperRightCornerAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

//                  ===========
//                    Texture
//                  ===========

    ///
    /// @brief GetSizeOfTexture
    /// @param texture The texture to get the size of
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    Tau_Size GetSizeOfTexture(SDL_Shared<SDL_Texture> texture);

    ///
    /// @brief DrawTextureAt
    /// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
    /// @param posit The posit in the window to draw the texture
    /// 
    void DrawTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit);

    ///
    /// @brief DrawTextureCenteredAt
    /// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
    /// @param posit The posit in the window to draw the centere of the texture
    /// 
    void DrawTextureCenteredAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit);

    ///
    /// @brief DrawTextureToRect
    /// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
    /// @param destRect The rectangle area in the window to draw the srcRect
    /// @remark the srcRect will be scaled to fit in the destRect
    /// 
    void DrawTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& destRect);

    ///
    /// @brief DrawSectionOfTextureAt
    /// @param texture probably from calling GetTextureAndSizeOfImage
    /// @param srcRect The rectangle area in the texture to draw
    /// @param posit The posit in the window to draw the texture
    /// 
    void DrawSectionOfTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Posit& posit);

    ///
    /// @brief DrawSectionOfTextureToRect
    /// @param texture probably from calling GetTextureAndSizeOfImage
    /// @param srcRect The rectangle area in the texture to draw
    /// @param destRect The rectangle area in the window to draw the srcRect
    /// @remark the srcRect will be scaled to fit in the destRect
    /// 
    void DrawSectionOfTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Rect& destRect);

//                  ===========
//                     Color
//                  ===========

    /// @brief SetColor Set the rendering color
    /// @param color 
    void SetColor(const Tau_Color& color);

    /// @brief GetColor Get the rendering color
    /// @return Tau_Color
    Tau_Color GetColor();

//                  ===========
//                   Draw Line
//                  ===========

    void DrawLine(const Tau_Point& p1, const Tau_Point& p2);

    void DrawLine(const std::vector<Tau_Point>& points);

    void DrawRect(const Tau_Rect& rect);
};

 } // end namespace Tau