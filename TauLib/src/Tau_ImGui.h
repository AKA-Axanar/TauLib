#pragma once

#include "SDL_Shared.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <optional>
#include "Tau_Rect.h"

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
/// @brief ImGui_DisableIniFile
///
void ImGui_DisableIniFile();

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
/// @return the selected index
/// 
std::pair<std::optional<int>, std::optional<int>> ImGui_Combo(const std::string& label, int current_index, const std::vector<std::string>& items, ImGuiComboFlags flags = 0);

///
/// @brief ImGui_TreeNodeMulti_Select
/// @param label - the label string on the right of the combo
/// @param items - the item strings in the combo list
/// @param selected - true for each item that is selected
/// @return void
/// selected is a vector<int> to bypass issues with vector<bool> being bits.
/// selected must be the same length as items.
/// selected int's will be true if that string is selected
/// 
void ImGui_TreeNodeMulti_Select(const std::string& label, const std::vector<std::string>& items, std::vector<int> *selected);

///
/// @brief ImGui_TreeNodeCheckboxes
/// @param label - the label string on the right of the combo
/// @param items - the item strings in the combo list
/// @param selected - true for each item that is selected
/// @return void
/// selected is a vector<int> to bypass issues with vector<bool> being bits.
/// selected must be the same length as items.
/// selected int's will be true if that string is selected
/// 
void ImGui_TreeNodeCheckboxes(const std::string& label, const std::vector<std::string>& items, std::vector<int> *selected);

///
/// @brief ImGui_Combo_Ints
/// @param label - the label string on the right of the combo
/// @param current_int - the index of the item that is the current selection
/// @param items - the item integers in the combo list
/// @param flags - any combo flags
/// @return the selected index
/// 
std::pair<std::optional<int>, std::optional<int>> ImGui_Combo_Ints(const std::string& label, int current_index, const std::vector<int>& int_items, ImGuiComboFlags flags = 0);

///
/// @brief ImGui_Combo_IntRange
/// @param label - the label string on the right of the combo
/// @param current_int - the index of the item that is the current selection
/// @param start - the first integer in the combo list
/// @param count - the count of integers in the combo list
/// @param flags - any combo flags
/// @return the selected index
/// 
std::pair<std::optional<int>, std::optional<int>> ImGui_Combo_IntRange(const std::string& label, int current_index, int start, int count, ImGuiComboFlags flags = 0);

///
/// @brief ImGui_Confirm
/// display a confirmation message with multiple buttons.  the index of the button that was pressed is returned, if any.
/// possible uses: OK/Cancel, Save/Discard,
/// @param show - same as ImGui::Begin's bool* p_open
/// @return the index of the button pressed, if any
/// 
std::optional<int> ImGui_Confirm(bool* show, const std::string& title, const std::string& message,
                  const std::vector<std::string>& buttons,
                  const std::vector<ImVec4>& buttonColors,
                  ImGuiWindowFlags windowFlags);

///
/// @brief ImGui_Popup
/// popup a message with a single OK button
/// 
void ImGui_Popup(bool* show, const std::string& title, const std::string& message, ImGuiWindowFlags windowFlags);

///
/// @brief ImGui_Render
/// 
void ImGui_Render(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer);
void ImGui_Render_Clear(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer, const ImVec4& clearColor);

///
/// @brief ImGui_Image
/// 
void ImGui_Image(SDL_Shared<SDL_Texture> texture, Tau_Rect rect);

///
/// @brief ImGui_AddFont
/// 
ImFont*  ImGui_AddFont(const std::string& TTF_fontfile, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);

///
/// @brief ImGui_TextCentered
/// 
void ImGui_TextCentered(const std::string& str);

///
/// @brief ImGui_ComputeButtonsCenteredPosX
/// 
float ImGui_ComputeButtonsCenteredPosX(const std::vector<std::string>& buttonStrings);

///
/// @brief ImGui_SetButtonsCenteredPosX
/// 
void ImGui_SetButtonsCenteredPosX(const std::vector<std::string>& buttonStrings);

///
/// @brief ImGui_TextCenteredMultiline
/// 
void ImGui_TextCenteredMultiline(std::string str);

///
/// @brief ImGui_HelpMarker
/// Helper to display a little (?) mark which shows a tooltip when hovered.
/// 
void ImGui_HelpMarker(const char* desc);

//    // Update and Render additional Platform Windows
//    void UpdateViewports();
}
