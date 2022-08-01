#pragma once

#include "SDL_Shared.h"
#include "imgui.h"
#include <vector>
#include <string>

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief ImGui_Init
/// @note call ImGui_Quit to clean up the init
///
void ImGui_Init(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer);

///
/// @brief ImGui_Quit
///
void ImGui_Quit();

///
/// @brief ImGui_NewFrame - Start the Dear ImGui frame
/// @note call ImGui::EndFrame at the end of the frame
/// 
void ImGui_NewFrame();

///
/// @brief ImGui_Combo
/// @param label - the label string on the right of the combo
/// @param current_int - the index of the item that is the current selection
/// @param items - the item strings in the combo list
/// @param flags - any combo flags
/// 
int ImGui_Combo(const std::string& label, int current_index, const std::vector<std::string>& items, ImGuiComboFlags flags = 0);

///
/// @brief ImGui_Combo_Ints
/// @param label - the label string on the right of the combo
/// @param current_int - the index of the item that is the current selection
/// @param items - the item integers in the combo list
/// @param flags - any combo flags
/// 
int ImGui_Combo_Ints(const std::string& label, int current_index, const std::vector<int>& int_items, ImGuiComboFlags flags = 0);

///
/// @brief ImGui_Combo_IntRange
/// @param label - the label string on the right of the combo
/// @param current_int - the index of the item that is the current selection
/// @param start - the first integer in the combo list
/// @param count - the count of integers in the combo list
/// @param flags - any combo flags
/// 
int ImGui_Combo_IntRange(const std::string& label, int current_index, int start, int count, ImGuiComboFlags flags = 0);

///
/// @brief ImGui_Render
/// 
void ImGui_Render(SDL_Shared<SDL_Renderer> renderer, const ImVec4& clearColor);

}
