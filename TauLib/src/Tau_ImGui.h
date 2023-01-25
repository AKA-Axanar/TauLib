#pragma once

#include "SDL_Shared.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <optional>

extern ImFont* font1;

///
/// @brief namespace Tau - avoid conflict with other libraries
///
namespace Tau { // to avoid conflict with other libraries

///
/// @brief Tau_ImGui_Init
/// @note call ImGui_Quit to clean up the init
///
void Tau_ImGui_Init(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer);

///
/// @brief Tau_ImGui_Quit
///
void Tau_ImGui_Quit();

///
/// @brief Tau_DisableImGuiIniFile
///
void Tau_DisableImGuiIniFile();

///
/// @brief Tau_ImGui_NewFrame - Start the Dear ImGui frame
/// @note call ImGui::EndFrame at the end of the frame
/// 
void Tau_ImGui_NewFrame();

///
/// @brief Tau_ImGui_Combo
/// @param label - the label string on the right of the combo
/// @param current_int - the index of the item that is the current selection
/// @param items - the item strings in the combo list
/// @param flags - any combo flags
/// @return the selected index
/// 
int Tau_ImGui_Combo(const std::string& label, int current_index, const std::vector<std::string>& items, ImGuiComboFlags flags = 0);

///
/// @brief Tau_ImGui_TreeNodeMulti_Select
/// @param label - the label string on the right of the combo
/// @param items - the item strings in the combo list
/// @param selected - true for each item that is selected
/// @return void
/// selected is a vector<int> to bypass issues with vector<bool> being bits.
/// selected must be the same length as items.
/// selected int's will be true if that string is selected
/// 
void Tau_ImGui_TreeNodeMulti_Select(const std::string& label, const std::vector<std::string>& items, std::vector<int> *selected);

///
/// @brief Tau_ImGui_TreeNodeCheckboxes
/// @param label - the label string on the right of the combo
/// @param items - the item strings in the combo list
/// @param selected - true for each item that is selected
/// @return void
/// selected is a vector<int> to bypass issues with vector<bool> being bits.
/// selected must be the same length as items.
/// selected int's will be true if that string is selected
/// 
void Tau_ImGui_TreeNodeCheckboxes(const std::string& label, const std::vector<std::string>& items, std::vector<int> *selected);

///
/// @brief Tau_ImGui_Combo_Ints
/// @param label - the label string on the right of the combo
/// @param current_int - the index of the item that is the current selection
/// @param items - the item integers in the combo list
/// @param flags - any combo flags
/// @return the selected index
/// 
int Tau_ImGui_Combo_Ints(const std::string& label, int current_index, const std::vector<int>& int_items, ImGuiComboFlags flags = 0);

///
/// @brief Tau_ImGui_Combo_IntRange
/// @param label - the label string on the right of the combo
/// @param current_int - the index of the item that is the current selection
/// @param start - the first integer in the combo list
/// @param count - the count of integers in the combo list
/// @param flags - any combo flags
/// @return the selected index
/// 
int Tau_ImGui_Combo_IntRange(const std::string& label, int current_index, int start, int count, ImGuiComboFlags flags = 0);

///
/// @brief Tau_ImGui_Confirm
/// display a confirmation message with multiple buttons.  the index of the button that was pressed is returned, if any.
/// possible uses: OK/Cancel, Save/Discard,
/// @param show - same as ImGui::Begin's bool* p_open
/// @return the index of the button pressed, if any
/// 
std::optional<int> Tau_ImGui_Confirm(bool* show, const std::string& title, const std::string& message,
                  const std::vector<std::string>& buttons,
                  const std::vector<ImVec4>& buttonColors,
                  ImGuiWindowFlags windowFlags);

///
/// @brief Tau_ImGui_Popup
/// popup a message with a single OK button
/// 
void Tau_ImGui_Popup(bool* show, const std::string& title, const std::string& message, ImGuiWindowFlags windowFlags);

void Tau_SetPosition();

///
/// @brief Tau_ImGui_Render
/// 
void Tau_ImGui_Render(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer);
void Tau_ImGui_Render_Clear(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer, const ImVec4& clearColor);

///
/// @brief Tau_ImGui_AddFont
/// 
ImFont*  Tau_ImGui_AddFont(const std::string& TTF_fontfile, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);

///
/// @brief HelpMarker
/// Helper to display a little (?) mark which shows a tooltip when hovered.
/// 
void HelpMarker(const char* desc);

//    // Update and Render additional Platform Windows
//    void UpdateViewports();
}
