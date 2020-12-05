///
/// @file
/// CPP file for SDL_Shared which is a shared_ptr with a custom destructor based on the type.
///

#include "SDL_shared.h"

// Code came from https://blog.galowicz.de/2016/02/21/automatic_resource_release_with_sdl/
//
// Modified by steve@iterator.com to use a class with conversion operators so a class
// onject can be treated as a ordinary pointer to the SDL object.
// Uses a shared_ptr optional custom destructor to call the correct SDL_Destroy/SDL_Free for the SDL type.
// Take care to not call the destroy function elsewhere causing it to be destroyed twice.

// see the template in the header for the implementation
void SDL_DelResource(SDL_Window   *r) { SDL_DestroyWindow(r);   }
void SDL_DelResource(SDL_Renderer *r) { SDL_DestroyRenderer(r); }
void SDL_DelResource(SDL_Texture  *r) { SDL_DestroyTexture(r);  }
void SDL_DelResource(SDL_Surface  *r) { SDL_FreeSurface(r);     }

