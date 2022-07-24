#pragma once

#include "SDL_Shared.h"
#include "imgui.h"
#include <vector>
#include <string>

namespace Tau {
///
/// @brief ImGui_DemoTest - calls ImGui::ShowDemoWindow() from scratch using Tau routines
/// creates the SDL_Window and SDL_Renderer and calls other setup routines for you.
///
void ImGui_DemoTest();

///
/// @brief ImGui_DemoTest - pass it an existing SDL_Window and SDL_Renderer.  calls ImGui::ShowDemoWindow() using Tau routines.
///
void ImGui_DemoTest(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer);
}
