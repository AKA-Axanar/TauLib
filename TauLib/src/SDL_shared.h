#pragma once

///
/// @file
/// @brief Header file for SDL_Shared.  A shared_ptr<T> with a custom destructor based on the type which calls 
/// the correct SDL_Destroy/SDL_Free function for that type.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///
/// @note Original code technique came from [here](https://blog.galowicz.de/2016/02/21/automatic_resource_release_with_sdl).
/// and modified by steve@iterator.com into a class containing conversion operators.  The conversion operators let you treate
/// the object as an ordinary pointer to the SDL object.
/// Uses a shared_ptr optional custom destructor to call the correct SDL_Destroy/SDL_Free for the SDL type.
/// Take care to not manually call the destroy function elsewhere causing it to be destroyed twice.
/// Destroy all instances before calling SDL_Quit() so the destrutor will be called. 


#include <memory>
#include "SDL.h"
#include "SDL_mixer.h"

extern void SDL_DelResource(SDL_Window   *r);   ///< @brief a custom shared_ptr dtor for SDL_Window
extern void SDL_DelResource(SDL_Renderer *r);   ///< @fn a custom shared_ptr dtor for SDL_Renderer
extern void SDL_DelResource(SDL_Texture  *r);   ///< @fn a custom shared_ptr dtor for SDL_Texture
extern void SDL_DelResource(SDL_Surface  *r);   ///< @fn a custom shared_ptr dtor for SDL_Surface

extern void SDL_DelResource(Mix_Music  *r);     ///< @fn a custom shared_ptr dtor for Mix_Music
extern void SDL_DelResource(Mix_Chunk  *r);     ///< @fn a custom shared_ptr dtor for Mix_Chunk

///
/// @struct SDL_Shared - a templated shared_ptr with a custom dtor per type
/// @note Don't call SDL_Quit(), Mix_Quit(), etc while there are outstanding shared_ptr's.
/// Destroy all instances of the shared+ptr so the destrutor will be called prior to calling SDL_Quit(). 
/// If needed the last remaining copy of a shared_ptr can be destroyed by setting it equal to nullptr.  
///
template <typename T>
struct SDL_Shared {
    std::shared_ptr<T> sdl_shared_ptr;                      //!< the shared_ptr of the template type

    /// @brief SDL_Shared() constructor
    /// @param t a pointer to the templated type
    SDL_Shared(T* t = nullptr) : sdl_shared_ptr(t, [](T *t)
        { SDL_DelResource(t); } ) {};    // automatically destroy/free when the last shared_ptr goes away

    operator T* () { return sdl_shared_ptr.get(); };        ///< @brief operator T* ()
    T & operator * () { return *sdl_shared_ptr.get(); };    ///< @brief T & operator * ()
    T * operator -> () { return sdl_shared_ptr.get(); };    ///< @brief T * operator -> ()
};

