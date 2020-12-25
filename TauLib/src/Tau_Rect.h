#pragma once

#include "SDL_Rect.h"

/// @brief Tau_Point An SDL_Point with additional functions
struct Tau_Point : public SDL_Point {
    Tau_Point(int _x, int _y) : SDL_Point(_x, _y) { }
    Tau_Point(const SDL_Rect& r) { x = r.x; y = r.y; }

    Tau_Point operator + (const SDL_Point& p) { return { x + p.x, y + p.y }; }
    Tau_Point operator - (const SDL_Point& p) { return { x - p.x, y - p.y }; }
    void operator += (SDL_Point& p) { x += p.x; y += p.y; }
    void operator -= (SDL_Point& p) { x -= p.x; y -= p.y; }

    operator SDL_Point& () { return *this; }
    operator const SDL_Point& () const { return *this; }
};

/// @brief Tau_Size The width and height portion of an SDL_Rect.
struct Tau_Size {
    int w;
    int h;

    Tau_Size(int _w, int _h) { w = _w; h = _h; }
    Tau_Size(const SDL_Rect& r) : w(r.w), h(r.h) { }
 
    Tau_Point GetCenter() { return { w/2, h/2 }; }
};

/// @brief Tau_Rect An SDL_Rect with additional functions
struct Tau_Rect : public SDL_Rect {
    Tau_Rect(int _x, int _y, int _w, int _h) : SDL_Rect(_x, _y, _w, _h) { }
    Tau_Rect(const Tau_Point& p, const Tau_Size size) : Tau_Rect(p.x, p.y, size.w, size.h) { }

    void MoveBy(const Tau_Point& p) { x += p.x; y += p.y; }

    Tau_Point GetPoint() { return { x, y }; }
    Tau_Size GetSize() { return { w, h }; }

    void SetPoint(const SDL_Point& p) { x = p.x; y = p.y; }
    void SetSize(const Tau_Size& size) { w = size.w; h = size.h; }

    operator SDL_Rect& () { return *this; }
    operator const SDL_Rect& () const { return *this; }
};
