#pragma once

#include "SDL_Pixels.h"

struct Tau_RGB {
    Uint8 r;
    Uint8 g;
    Uint8 b;

    Tau_RGB(Uint8 _r=0, Uint8 _g=0, Uint8 _b=0) : r(_r), g(_g), b(_b) { }
    Tau_RGB(Uint8 value) : r(value), g(value), b(value) { }

    /// @brief Tau_RGB math operators
    Tau_RGB operator + (const Tau_RGB& rgb) const { return Tau_RGB(r + rgb.r, g + rgb.g, b + rgb.b); }
    Tau_RGB operator - (const Tau_RGB& rgb) const { return Tau_RGB(r - rgb.r, g - rgb.g, b - rgb.b); }
    void operator += (Tau_RGB& rgb) { r += rgb.r; g += rgb.g; b += rgb.b; }
    void operator -= (Tau_RGB& rgb) { r -= rgb.r; g -= rgb.g; b -= rgb.b; }
};

///
/// @brief Tau_Color An SDL_Color with additional functions
/// @note Do not add additional member variables to this struct!
///
struct Tau_Color : public SDL_Color {
    /// @brief Tau_Color ctor
    Tau_Color(Uint8 _r=0, Uint8 _g=0, Uint8 _b=0, Uint8 _a=0) : SDL_Color(_r, _g, _b, _a) { }
    Tau_Color(const Tau_RGB& rgb, Uint8 _a=0) : SDL_Color(rgb.r, rgb.g, rgb.b, _a) { }

    Tau_RGB GetRGB() const { return Tau_RGB(r, g, b); }
    void SetRGB(const Tau_RGB& rgb) { r = rgb.r; g = rgb.g; b = rgb.b; }
};

const Tau_RGB RGB_black { 0, 0, 0 };
const Tau_Color Tau_black { RGB_black, 0 };

const Tau_RGB RGB_white { 255, 255, 255 };
const Tau_Color Tau_white { RGB_white, 255 };

const Tau_RGB RGB_red { 255, 0, 0 };
const Tau_Color Tau_red { RGB_red, 255 };

const Tau_RGB RGB_green { 0, 255, 0 };
const Tau_Color Tau_green { RGB_green, 255 };

const Tau_RGB RGB_blue { 0, 0, 255 };
const Tau_Color Tau_blue { RGB_blue, 255 };
