#pragma once
///
/// @file
/// @brief Header file for Tau_Color and Tau_RGB classes.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "SDL_Pixels.h"
#include "Str.h"

struct Tau_RGB {
    Uint8 r;
    Uint8 g;
    Uint8 b;

    Tau_RGB(Uint8 _r=0, Uint8 _g=0, Uint8 _b=0) : r(_r), g(_g), b(_b) { }
    Tau_RGB(Uint8 value) : r(value), g(value), b(value) { }

    /// @brief these ctors are useful when getting the RGB values from an IniFile
    Tau_RGB(const std::vector<int>& values) : Tau_RGB() 
        { if (values.size() == 3) { r = values[0]; g = values[1]; b = values[2]; } }
    Tau_RGB(const std::string& str) : Tau_RGB(Tau::CommaSepStringToInts(str)) { }

    /// @brief Tau_RGB math operators
    Tau_RGB operator + (const Tau_RGB& rgb) const { return Tau_RGB(r + rgb.r, g + rgb.g, b + rgb.b); }
    Tau_RGB operator - (const Tau_RGB& rgb) const { return Tau_RGB(r - rgb.r, g - rgb.g, b - rgb.b); }
    void operator += (Tau_RGB& rgb) { r += rgb.r; g += rgb.g; b += rgb.b; }
    void operator -= (Tau_RGB& rgb) { r -= rgb.r; g -= rgb.g; b -= rgb.b; }

    bool operator == (const Tau_RGB& rgb) const { return r == rgb.r && g == rgb.g && b == rgb.b; }
};

///
/// @brief Tau_Color An SDL_Color with additional functions
/// @note Do not add additional member variables to this struct!
///
struct Tau_Color : public SDL_Color {
    /// @brief Tau_Color ctor
    Tau_Color(Uint8 _r=0, Uint8 _g=0, Uint8 _b=0, Uint8 _a=0) : SDL_Color(_r, _g, _b, _a) { }
    Tau_Color(const Tau_RGB& rgb, Uint8 _a=0) : SDL_Color(rgb.r, rgb.g, rgb.b, _a) { }
    Tau_Color(const SDL_Color& color) : SDL_Color(color) {}

    /// @brief these ctors are useful when getting the color values from an IniFile
    Tau_Color(const std::vector<int>& values) : Tau_Color()
    {
        if (values.size() == 4) { r = values[0]; g = values[1]; b = values[2]; a = values[3]; }
        if (values.size() == 3) { r = values[0]; g = values[1]; b = values[2]; a = SDL_ALPHA_OPAQUE; }
    }
    Tau_Color(const std::string& str) : Tau_Color(Tau::CommaSepStringToInts(str)) { }

    Tau_RGB GetRGB() const { return Tau_RGB(r, g, b); }
    void SetRGB(const Tau_RGB& rgb) { r = rgb.r; g = rgb.g; b = rgb.b; }

    bool operator == (const Tau_Color& color) const { return GetRGB() == color.GetRGB() && a == color.a; }
};

inline const Tau_RGB RGB_black { 0, 0, 0 };
inline const Tau_Color Tau_black { RGB_black, 0 };

inline const Tau_RGB RGB_white { 255, 255, 255 };
inline const Tau_Color Tau_white { RGB_white, SDL_ALPHA_OPAQUE };

inline const Tau_RGB RGB_red { 255, 0, 0 };
inline const Tau_Color Tau_red { RGB_red, SDL_ALPHA_OPAQUE };

inline const Tau_RGB RGB_green { 0, 255, 0 };
inline const Tau_Color Tau_green { RGB_green, SDL_ALPHA_OPAQUE };

inline const Tau_RGB RGB_blue { 0, 0, 255 };
inline const Tau_Color Tau_blue { RGB_blue, SDL_ALPHA_OPAQUE };

inline Tau_RGB RGB_grey { 128, 128, 128 };
inline const Tau_Color Tau_grey { RGB_grey, SDL_ALPHA_OPAQUE };

inline const Tau_RGB RGB_gray = RGB_grey;
inline const Tau_Color Tau_gray = Tau_grey;

inline const Tau_Color Tau_cornflowerBlue { 100, 147, 237, SDL_ALPHA_OPAQUE };  // "Can I get the icon in Cornflower Blue?"  "Absolutely."
