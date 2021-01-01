#include "DrawArea.h"

namespace Tau { // to avoid conflict with other libraries

DrawArea::DrawArea(SDL_Shared<SDL_Renderer> _renderer, const Tau_Rect& _rect) : renderer(_renderer), winArea(_rect) { }

}
