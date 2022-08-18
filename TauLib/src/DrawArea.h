#pragma once
///
/// @file
/// @brief Header file for DrawArea class.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "SDL_Shared.h"
#include "Tau_Rect.h"
#include "TTF_Font_Shared.h"
#include "FC_Font_Shared.h"
#include "Tau_Color.h"
#include <vector>

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief DrawArea class with routines to draw text, images, lines, rectangles, fill, move within window
///
struct DrawArea {
    SDL_Shared<SDL_Renderer> renderer;
    Tau_Rect drawAreaRect;  ///< The rect area of the window to draw in the window.

    DrawArea() {}
    DrawArea(SDL_Shared<SDL_Renderer> _renderer, const Tau_Rect& rect);

    // Default Background Draw Action
    Tau_Color defaultFillColor = Tau_black;
    bool enableDefaultFill = false;
    std::string defaultImageFile;
    SDL_Shared<SDL_Texture> defaultImageTexture;    // save this for better performance later
    bool enableDefaultImage = false;

    void SetDefaultFill(const Tau_Color& color, bool enable);

    void SetDefaultImage(const std::string& filename, bool enable);

    void DrawDefault();

    /// @brief Move the DrawArea rectangle within the window
    /// @param distance 
    void MoveBy(Tau_Distance distance);

    /// @brief Move the DrawArea rectangle within the window
    /// @param point 
    void MoveTo(Tau_Point point);

    bool enableDraw = true;

    /// @brief Draw this DrawArea and all the subAreas inside
    virtual void Draw();

    // I don't know if the technique of having sub-area rectangles and sub-areas within them will work out or not.
    // But they are easy to implement and try out.  They might be useful for implementing menus.  Will give it a try.
    std::vector<DrawArea> subAreas;     ///< Children rect draw areas that fall within this drawAreaRect.  A button icon for example.

    /// @brief Add a sub rectangle DrawArea to the vector of items to draw within the DrawArea
    /// @param subArea 
    void AddSubArea(const DrawArea& subArea);

//                  ===========
//                     Fill Win
//                  ===========

    /// @brief FillWin - fill the window with a color
    /// @param color The color to fill the window with
    /// @note does not call SDL_RenderPresent
    void FillWin(Tau_Color color = Tau_black);

    /// @brief ClearWin - clear the window. defaults to black.
    /// @param color
    /// @note calls SDL_RenderPresent
    void ClearWin(Tau_Color color = Tau_black);

//                  ===========
//                   Fill Rect
//                  ===========

    ///
    /// @brief FillRect - fill an Tau_Rect with the current color or blend
    /// @param rect rectangle to fill
    ///
    void FillRect(const Tau_Rect& rect);

    ///
    /// @brief FillRect - fill an Tau_Rect with a color
    /// @param rect rectangle to fill
    /// @param color Color to fill
    ///
    void FillRect(const Tau_Rect& rect, Tau_Color color);

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

    ///
    /// @brief SetTextureAlpha
    /// @param texture - texture to have it's alpha factor set
    /// @param alpha - alpha factor.  0-255.  255 is full overwrite what's underneath.  128 is 50% draw and 50% transparent.
    /// 
    void SetTextureAlpha(SDL_Shared<SDL_Texture> texture, Uint8 alpha);

    ///
    /// @brief GetTextureAlpha
    /// @param texture - texture to get the alpha value
    /// @return the alpha factor in the texture.  0-255.  255 is full overwrite what's underneath.  128 is 50% draw and 50% transparent.
    /// 
    Uint8 GetTextureAlpha(SDL_Shared<SDL_Texture> texture);

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
    /// @param font
    /// @param text
    /// @param color
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    SDL_Shared<SDL_Texture> GetTextureOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color);

    ///
    /// @brief GetTextureAndSizeOfText
    /// @param font
    /// @param text
    /// @param color
    /// @return SDL_Shared<SDL_Texture> texture and Tau_Size size
    /// 
    std::tuple<SDL_Shared<SDL_Texture>, Tau_Size> GetTextureAndSizeOfText(TTF_Font_Shared font, const std::string& text, SDL_Color color);

//                  ===========
//                   Draw TTF Text
//                  ===========

    ///
    /// @brief DrawTextAt Draws the text at a point on the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the image
    /// @return The height of the text
    /// 
    int DrawTextAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextCenteredAt Draws the text centered on a point on the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the image
    /// @return none
    /// 
    int DrawTextCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextCenteredInWindow Draws the text centered in the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @return The height of the text
    /// 
    int DrawTextCenteredInWindow(TTF_Font_Shared font, const std::string& text, SDL_Color color);

    ///
    /// @brief DrawTextHorizCenteredAt Draws the text horizontally centered on a point on the window.  
    /// The center top of the text will be at that point.
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the text
    /// @return The height of the text
    /// 
    int DrawTextHorizCenteredAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextHorizCenteredInWindow Draws the text centered in the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param y the y position to draw (x will be the window center x).
    /// @return The height of the text
    /// 
    int DrawTextHorizCenteredInWindow(TTF_Font_Shared font, const std::string& text, SDL_Color color, int y);

    ///
    /// @brief DrawTextUpperRightCornerAt Draws the text such that the upper right corner is at the passed point.  
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The upper right corner point to draw the text
    /// @return The height of the text
    /// 
    int DrawTextUpperRightCornerAt(TTF_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

//                  ===========
//                   Draw FC Text
//                   Overrides the FC_Font color
//                  ===========

    ///
    /// @brief DrawTextAt Draws the text at a point on the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the image
    /// @return The height of the text
    /// 
    int DrawTextAt(FC_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextCenteredAt Draws the text centered on a point on the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the image
    /// @return none
    /// 
    int DrawTextCenteredAt(FC_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextCenteredInWindow Draws the text centered in the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @return The height of the text
    /// 
    int DrawTextCenteredInWindow(FC_Font_Shared font, const std::string& text, SDL_Color color);

    ///
    /// @brief DrawTextHorizCenteredAt Draws the text horizontally centered on a point on the window.  
    /// The center top of the text will be at that point.
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The point to draw the text
    /// @return The height of the text
    /// 
    int DrawTextHorizCenteredAt(FC_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

    ///
    /// @brief DrawTextHorizCenteredInWindow Draws the text centered in the window
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param y the y position to draw (x will be the window center x).
    /// @return The height of the text
    /// 
    int DrawTextHorizCenteredInWindow(FC_Font_Shared font, const std::string& text, SDL_Color color, int y);

    ///
    /// @brief DrawTextUpperRightCornerAt Draws the text such that the upper right corner is at the passed point.  
    /// @param font A shared font ptr
    /// @param text The text to draw
    /// @param color The color to draw the text
    /// @param point The upper right corner point to draw the text
    /// @return The height of the text
    /// 
    int DrawTextUpperRightCornerAt(FC_Font_Shared font, const std::string& text, SDL_Color color, const Tau_Point& point);

//                  ===========
//                   Draw FC Text
//                   Same as the above routines but uses the color the FC_Font was created with
//                  ===========

    int DrawTextAt(FC_Font_Shared font, const std::string& text, const Tau_Point& point);
    int DrawTextCenteredAt(FC_Font_Shared font, const std::string& text, const Tau_Point& point);
    int DrawTextCenteredInWindow(FC_Font_Shared font, const std::string& text);
    int DrawTextHorizCenteredAt(FC_Font_Shared font, const std::string& text, const Tau_Point& point);
    int DrawTextHorizCenteredInWindow(FC_Font_Shared font, const std::string& text, int y);
    int DrawTextUpperRightCornerAt(FC_Font_Shared font, const std::string& text, const Tau_Point& point);

//                  ===========
//                  Get Texture Size
//                  ===========

    ///
    /// @brief GetSizeOfTexture
    /// @param texture The texture to get the size of
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    Tau_Size GetSizeOfTexture(SDL_Shared<SDL_Texture> texture);

    ///
    /// @brief GetHeightOfTexture
    /// @param texture The texture to get the height of.  This is useful for text to find how many pixels to move down to the next line.
    /// @return SDL_Shared<SDL_Texture> texture
    /// 
    int GetHeightOfTexture(SDL_Shared<SDL_Texture> texture) { return GetSizeOfTexture(texture).h; }

//                  ===========
//                  Draw Texture
//                  ===========

    ///
    /// @brief DrawTextureAt
    /// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
    /// @param posit The posit in the window to draw the texture
    /// @return The height of the texture

    int DrawTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit);

    ///
    /// @brief DrawTextureCenteredAt
    /// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
    /// @param posit The posit in the window to draw the centere of the texture
    /// @return The height of the texture
    /// 
    int DrawTextureCenteredAt(SDL_Shared<SDL_Texture> texture, const Tau_Posit& posit);

    ///
    /// @brief DrawTextureCenteredInWindow
    /// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
    /// 
    void DrawTextureCenteredInWindow(SDL_Shared<SDL_Texture> texture);

    ///
    /// @brief DrawTextureToRect
    /// @param texture perhaps from calling GetTextureAndSizeOfImage or GetTextureOfText
    /// @param destRect The rectangle area in the window to draw the srcRect
    /// @remark the srcRect will be scaled to fit in the destRect
    /// @return The height of the texture
    /// 
    int DrawTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& destRect);

    ///
    /// @brief DrawSectionOfTextureAt
    /// @param texture probably from calling GetTextureAndSizeOfImage
    /// @param srcRect The rectangle area in the texture to draw
    /// @param posit The posit in the window to draw the texture
    /// @return The height of the drawn dest area
    /// 
    int DrawSectionOfTextureAt(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Posit& posit);

    ///
    /// @brief DrawSectionOfTextureToRect
    /// @param texture probably from calling GetTextureAndSizeOfImage
    /// @param srcRect The rectangle area in the texture to draw
    /// @param destRect The rectangle area in the window to draw the srcRect
    /// @remark the srcRect will be scaled to fit in the destRect
    /// @return The height of the drawn dest area
    /// 
    int DrawSectionOfTextureToRect(SDL_Shared<SDL_Texture> texture, const Tau_Rect& srcRect, const Tau_Rect& destRect);

//                  ===========
//                     Color
//                  ===========

    /// @brief SetColor Set the rendering color
    /// @param color 
    void SetColor(const Tau_Color& color);

    /// @brief GetColor Get the rendering color
    /// @return Tau_Color
    Tau_Color GetColor();

    /// @brief SetColor Set the rendering color
    /// @param mode 
    void SetDrawBlendMode(SDL_BlendMode mode) { SDL_SetRenderDrawBlendMode(renderer, mode); }

//                  ===========
//                   Draw Line
//                  ===========

    void DrawLine(const Tau_Point& p1, const Tau_Point& p2);

    void DrawLine(const std::vector<Tau_Point>& points);

    void DrawRect(const Tau_Rect& rect);

};

}
