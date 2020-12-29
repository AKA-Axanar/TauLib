#pragma once

#include "SDL_Rect.h"

///
/// @brief Tau_Point An SDL_Point with additional functions
/// @note Do not add additional member variables to this struct!
///
struct Tau_Point : public SDL_Point {
    /// @brief Tau_Point ctor
    Tau_Point(int _x=0, int _y=0) : SDL_Point(_x, _y) { }

//    /// @brief Tau_Point copy ctor
//    Tau_Point(const Tau_Point& pnt) { x = pnt.x; y = pnt.y; }
//
//    /// @brief Tau_Point ctor from a SDL_Rect top left corner position
//    Tau_Point(const SDL_Rect& rect) { x = rect.x; y = rect.y; }

    /// @brief Tau_Point math operators
    Tau_Point operator + (const Tau_Point& pnt) const { return { x + pnt.x, y + pnt.y }; }
    Tau_Point operator - (const Tau_Point& pnt) const { return { x - pnt.x, y - pnt.y }; }
    void operator += (Tau_Point& pnt) { x += pnt.x; y += pnt.y; }
    void operator -= (Tau_Point& pnt) { x -= pnt.x; y -= pnt.y; }

//    /// @brief Tau_Point conversion operators.  The compiler might do this automatically.
//    operator SDL_Point& () { return *this; }
//    operator const SDL_Point& () const { return *this; }
};

///
/// @brief Tau_Size The width and height portion of an SDL_Rect.
/// @note Do not add additional member variables to this struct!
///
struct Tau_Size {
    int w;
    int h;

    Tau_Size(int _w=0, int _h=0) { w = _w; h = _h; }
    Tau_Size(const SDL_Rect& rect) : w(rect.w), h(rect.h) { }
 
    Tau_Point GetCenter() { return { w/2, h/2 }; }
};

///
/// @brief Tau_Rect An SDL_Rect with additional functions
/// @note Do not add additional member variables to this struct!
///
struct Tau_Rect : public SDL_Rect {
    /// @brief Tau_Rect ctor
    Tau_Rect(int _x=0, int _y=0, int _w=0, int _h=0) : SDL_Rect(_x, _y, _w, _h) { }

    /// @brief Tau_Rect Construct from upper left corner point and the size
    /// @param p The top left corner point position of the rectangle
    /// @param size The size of the rectangle
    Tau_Rect(const Tau_Point& pnt, const Tau_Size& size) : SDL_Rect(pnt.x, pnt.y, size.w, size.h) { }

    void MoveBy(const Tau_Point& pnt) { x += pnt.x; y += pnt.y; }

    /// @brief GetPoint
    /// @return The top left corner point position of the rectangle
    Tau_Point GetPoint() const { return { x, y }; }

    /// @brief GetSize
    /// @return The size of the rectangle
    Tau_Size GetSize() const { return { w, h }; }

    /// @brief SetPoint Sets the value of the top left position
    void SetPoint(const SDL_Point& pnt) { x = pnt.x; y = pnt.y; }

    /// @brief SetSize Sets the size (width and height) of the rectangle
    void SetSize(const Tau_Size& size) { w = size.w; h = size.h; }

    /// @brief Return the center point of the rectangle.
    /// @return The center point of the rectangle
    Tau_Point Center() const { return { x + w/2, y + h/2 }; }

    void CenterMeInsideRectangle(const Tau_Rect& outerRect) 
        { SetPoint(outerRect.Center() - Tau_Point(w/2, h/2)); }

//    /// @brief Tau_Rect conversion operators.  The compiler might do this automatically.
//    operator SDL_Rect& () { return *this; }
//    operator const SDL_Rect& () const { return *this; }
};

using Tau_Posit = Tau_Point;    ///< An x,y position.  same as an x,y point.
