#pragma once

#include "SDL_Shared.h"
#include "imgui.h"

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief ImGui_Init
///
void ImGui_Init(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer);

///
/// @brief ImGui_Cleanup
///
void ImGui_Cleanup();

///
/// @brief ImGui_NewFrame - Start the Dear ImGui frame
/// 
void ImGui_NewFrame();

///
/// @brief ImGui_Render
/// 
void ImGui_Render(SDL_Shared<SDL_Renderer> renderer, const ImVec4& clearColor);

///
/// @brief ImGui_ShowDemoWindow - calls ImGui::ShowDemoWindow() from Tau
///
void ImGui_ShowDemoWindow(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer);
}
