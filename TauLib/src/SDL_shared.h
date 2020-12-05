#pragma once

///
/// @file
/// Header file for SDL_Shared which is a shared_ptr with a custom destructor based on the type.
///

// Code came from https://blog.galowicz.de/2016/02/21/automatic_resource_release_with_sdl/
//
// Modified by steve@iterator.com to use a class with conversion operators so a class
// onject can be treated as a ordinary pointer to the SDL object.
// Uses a shared_ptr optional custom destructor to call the correct SDL_Destroy/SDL_Free for the SDL type.
// Take care to not call the destroy function elsewhere causing it to be destroyed twice.

#include <memory>
#include "SDL.h"

extern void SDL_DelResource(SDL_Window   *r);   ///< @brief a custom shared_ptr dtor for this type
extern void SDL_DelResource(SDL_Renderer *r);   ///< @fn a custom shared_ptr dtor for this type
extern void SDL_DelResource(SDL_Texture  *r);   ///< @fn a custom shared_ptr dtor for this type
extern void SDL_DelResource(SDL_Surface  *r);   ///< @fn a custom shared_ptr dtor for this type

///
///  @brief SDL_Shared - a templated shared_ptr with a custom dtor per type
///
template <typename T>
struct SDL_Shared {
    std::shared_ptr<T> sdl_shared_ptr;                      //!< the shared_ptr of the template type

    /// @brief  @brief SDL_Shared() constructor
    /// @param t a pointer to the templated type
    SDL_Shared(T* t = nullptr) : sdl_shared_ptr(t, [](T *t)
        { SDL_DelResource(t); } ) {};    // automatically destroy/free when the last shared_ptr goes away

    operator T* () { return sdl_shared_ptr.get(); };        ///< @brief operator T* ()
    T & operator * () { return *sdl_shared_ptr.get(); };    ///< @brief T & operator * ()
    T * operator -> () { return sdl_shared_ptr.get(); };    ///< @brief T * operator -> ()
};

