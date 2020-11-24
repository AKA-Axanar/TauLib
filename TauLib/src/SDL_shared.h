#pragma once

// Code came from https://blog.galowicz.de/2016/02/21/automatic_resource_release_with_sdl/
//
// Modified by steve@iterator.com to use a class with conversion operators so a class
// onject can be treated as a ordinary pointer to the SDL object.
// Uses a shared_ptr optional custom destructor to call the correct SDL_Destroy/SDL_Free for the SDL type.
// Take care to not call the destroy function elsewhere causing it to be destroyed twice.

#include <memory>
#include "SDL.h"

extern void SDL_DelResource(SDL_Window   *r);
extern void SDL_DelResource(SDL_Renderer *r);
extern void SDL_DelResource(SDL_Texture  *r);
extern void SDL_DelResource(SDL_Surface  *r);

template <typename T>
struct SDL_Shared {
    std::shared_ptr<T> sdl_shared_ptr;

    SDL_Shared(T* t = nullptr) : sdl_shared_ptr(t, [](T *t)
        { SDL_DelResource(t); } ) {};    // automatically destroy/free when the last shared_ptr goes away

    operator T* () { return sdl_shared_ptr.get(); };
    T & operator * () { return *sdl_shared_ptr.get(); };
    T * operator -> () { return sdl_shared_ptr.get(); };
};

