#pragma once

#include "SDL_Rect.h"

///
/// @brief Tau_Point An SDL_Point with additional functions
///
struct Tau_Point : public SDL_Point {
//    /// @brief Tau_Point ctor
//    Tau_Point(int _x=0, int _y=0) : SDL_Point(_x, _y) { }

//    /// @brief Tau_Point copy ctor
//    Tau_Point(const Tau_Point& pnt) { x = pnt.x; y = pnt.y; }

//    /// @brief Tau_Point ctor from a SDL_Rect top left corner position
//    Tau_Point(const SDL_Rect& rect) { x = rect.x; y = rect.y; }

    /// @brief Tau_Point math operators
    Tau_Point operator + (const SDL_Point& pnt) { return { x + pnt.x, y + pnt.y }; }
    Tau_Point operator - (const SDL_Point& pnt) { return { x - pnt.x, y - pnt.y }; }
    void operator += (SDL_Point& pnt) { x += pnt.x; y += pnt.y; }
    void operator -= (SDL_Point& pnt) { x -= pnt.x; y -= pnt.y; }

//    /// @brief Tau_Point conversion operators.  The compiler might do this automatically.
//    operator SDL_Point& () { return *this; }
//    operator const SDL_Point& () const { return *this; }
};

///
/// @brief Tau_Size The width and height portion of an SDL_Rect.
///
struct Tau_Size {
    int w;
    int h;

    Tau_Size(int _w, int _h) { w = _w; h = _h; }
    Tau_Size(const SDL_Rect& rect) : w(rect.w), h(rect.h) { }
 
    Tau_Point GetCenter() { return { w/2, h/2 }; }
};

///
/// @brief Tau_Rect An SDL_Rect with additional functions
///
struct Tau_Rect : public SDL_Rect {
//    /// @brief Tau_Rect ctor
//    Tau_Rect(int _x, int _y, int _w, int _h) : SDL_Rect(_x, _y, _w, _h) { }

    /// @brief Tau_Rect Contrust from the corner point and the size
    /// @param p The top left corner point position of the rectangle
    /// @param size The size of the rectangle
    Tau_Rect(const Tau_Point& pnt, const Tau_Size& size) : SDL_Rect(pnt.x, pnt.y, size.w, size.h) { }

    void MoveBy(const Tau_Point& pnt) { x += pnt.x; y += pnt.y; }

    /// @brief GetPoint
    /// @return The top left corner point position of the rectangle
    Tau_Point GetPoint() { return { x, y }; }

    /// @brief GetSize
    /// @return The size of the rectangle
    Tau_Size GetSize() { return { w, h }; }

    /// @brief SetPoint Sets the value of the top left position
    void SetPoint(const SDL_Point& pnt) { x = pnt.x; y = pnt.y; }

    /// @brief SetSize Sets the size (width and height) of the rectangle
    void SetSize(const Tau_Size& size) { w = size.w; h = size.h; }

//    /// @brief Tau_Rect conversion operators.  The compiler might do this automatically.
//    operator SDL_Rect& () { return *this; }
//    operator const SDL_Rect& () const { return *this; }
};

using Tau_Posit = Tau_Point;    ///< An x,y position.  same as an x,y point.
