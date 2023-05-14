#pragma once

#include "SDL_Shared.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <optional>
#include "Tau_Rect.h"
#include "Tau_Color.h"

extern ImGuiContext* TauImGuiContext;

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
/// @brief ListBox2Columns
/// @param label - the label string on the right of the ListBox
/// @param current_item - the index of the item that is the current selection
/// @param leftData - array of char* strings for the left side column
/// @param rightData - array of char* strings for the right side column
/// @param data2xPosit - x position of right column
/// @param items_count - the count of char* in both the left and right arrays
/// @return the selected index if a line was clicked on.  and the index of a hovered over line.
/// 
std::pair<std::optional<int>, std::optional<int>>
ImGui_ListBox2Columns(const char* label, int* current_item, const char* const leftData[], const char* const rightData[],
                      float data2xPosit, float xWindowWidth, size_t items_count, int height_in_items);

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
/// Pass a size to display the image on the current ImGui line in progress.
/// Pass a rect to display the image at the specified rect in the ImGui window.
void ImGui_Image(SDL_Shared<SDL_Texture> texture, Tau_Size size);
void ImGui_Image(SDL_Shared<SDL_Texture> texture, Tau_Rect rect);

///
// @brief ImGui_ImageButton
/// Pass a size to display the image button on the current ImGui line in progress.
/// Pass a rect to display the image button at the specified rect in the ImGui window.
/// 
void ImGui_ImageButton(SDL_Shared<SDL_Texture> texture, Tau_Size size);
void ImGui_ImageButton(SDL_Shared<SDL_Texture> texture, Tau_Rect rect);

///
/// @brief ImGui_AddFont
/// 
ImFont* ImGui_AddFont(const std::string& TTF_fontfile, float size_pixels, const ImFontConfig* font_cfg = NULL, const ImWchar* glyph_ranges = NULL);

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
/// @brief ImGui_TextIndentedMultiline
/// 
void ImGui_TextIndentedMultiline(std::string str, float leftIndent, float rightIndent);
inline void ImGui_TextIndentedMultiline(std::string str, float indent) { ImGui_TextIndentedMultiline(str, indent, indent); }

///
/// @brief ImGui_HelpMarker
/// Helper to display a little (?) mark which shows a tooltip when hovered.
/// 
void ImGui_HelpMarker(const char* desc);

//
// Conversion Helpers
//
inline Tau_Point to_Tau_Point(const ImVec2& vec2) { return { (int) round(vec2.x), (int) round(vec2.y) }; }
inline Tau_Posit to_Tau_Posit(const ImVec2& vec2) { return { (int) round(vec2.x), (int) round(vec2.y) }; }
inline Tau_Distance to_Tau_Distance(const ImVec2& vec2) { return { (int) round(vec2.x), (int) round(vec2.y) }; }
inline Tau_Size to_Tau_Size(const ImVec2& vec2) { return { (int) round(vec2.x), (int) round(vec2.y) }; }
inline Tau_Rect to_Tau_Rect(const ImVec4& vec4) { return { (int) round(vec4.x), (int) round(vec4.y), (int) round(vec4.z), (int) round(vec4.w) }; }

inline ImVec2 to_ImVec2(const Tau_Point point) { return { (float)point.x, (float)point.y }; }
//inline ImVec2 to_ImVec2(const Tau_Posit posit) { return { (float)posit.x, (float)posit.y }; }     // uncommenting causes an already has a body error
//inline ImVec2 to_ImVec2(const Tau_Distance dist) { return { (float)dist.x, (float)dist.y }; }     // uncommenting causes an already has a body error
inline ImVec2 to_ImVec2(const Tau_Size size) { return { (float)size.w, (float)size.h }; }
inline ImVec4 to_ImVec4(const Tau_Rect rect) { return { (float)rect.x, (float)rect.y, (float)rect.w, (float)rect.h }; }

inline Tau_Color to_Tau_Color(const ImVec4& vec4) { return { (Uint8) round(vec4.x * 255.f), (Uint8) round(vec4.y * 255.f), (Uint8) round(vec4.z * 255.f), (Uint8) round(vec4.w * 255.f) }; }
inline Tau_RGB to_Tau_RGB(const ImVec4& vec4) { return { (Uint8) round(vec4.x * 255.f), (Uint8) round(vec4.y * 255.f), (Uint8) round(vec4.z * 255.f) }; }

inline ImVec4 to_ImVec4(const Tau_Color color) { return { (float)color.r/255.f, (float)color.g/255.f, (float)color.b/255.f, (float)color.a/255.f }; }
inline ImVec4 to_ImVec4(const Tau_RGB color) { return { (float)color.r/255.f, (float)color.g/255.f, (float)color.b/255.f, 1.0f }; }

//    // Update and Render additional Platform Windows
//    void UpdateViewports();
}
