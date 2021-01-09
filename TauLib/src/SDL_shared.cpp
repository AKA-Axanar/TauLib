///
/// @file
/// @brief CPP file for SDL_Shared which is a shared_ptr with a custom destructor based on the type.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
///

#include "SDL_Shared.h"

/// @note Original code technique came from [here](https://blog.galowicz.de/2016/02/21/automatic_resource_release_with_sdl).
/// and modified by steve@iterator.com into a class containing conversion operators.  The conversion operators let you treate
/// the object as an ordinary pointer to the SDL object.
/// Uses a shared_ptr optional custom destructor to call the correct SDL_Destroy/SDL_Free for the SDL type.
/// Take care to not manually call the destroy function elsewhere causing it to be destroyed twice.
/// Destroy all instances so the destrutor will be called before calling SDL_Quit(). 

// see the template in the header for the implementation
void SDL_DelResource(SDL_Window   *r) { SDL_DestroyWindow(r);   }
void SDL_DelResource(SDL_Renderer *r) { SDL_DestroyRenderer(r); }
void SDL_DelResource(SDL_Texture  *r) { SDL_DestroyTexture(r);  }
void SDL_DelResource(SDL_Surface  *r) { SDL_FreeSurface(r);     }

void SDL_DelResource(Mix_Music  *r) { Mix_FreeMusic(r);     }
void SDL_DelResource(Mix_Chunk  *r) { Mix_FreeChunk(r);     }
