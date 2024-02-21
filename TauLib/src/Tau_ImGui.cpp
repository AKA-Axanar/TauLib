#include "Tau_ImGui.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"
#include "imgui_impl_sdlrenderer.h"
#include <SDL.h>
#include <ranges>
#include <algorithm>
#include "Lang.h"
#include <iostream>
#include "DirFile.h"

using namespace std;

ImGuiContext* TauImGuiContext {nullptr};

namespace Tau { // to avoid conflict with other libraries

    //
    // ImGui_Init
    //
    void ImGui_Init(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer) {
        // from the example code in imgui/examples/example_sdl_sdlrenderer/main.cpp

        assert(window);
        assert(renderer);

#if 0
        // Setup window
        //SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        //SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
        if (window == nullptr) {
            SDL_Log("Error creating SDL_Window!");
            return;
        }
        // Setup SDL_Renderer instance
        //SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
        {
            SDL_Log("Error creating SDL_Renderer!");
            return;
        }
#endif

        //SDL_RendererInfo info;
        //SDL_GetRendererInfo(renderer, &info);
	
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        TauImGuiContext = ImGui::CreateContext();

        // enable keyboard and controller control over menu
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer_Init(renderer);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);
    }

    //
    // ImGui_Quit
    //
    void ImGui_Quit() {
        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    //
    // ImGui_DisableIniFile
    //
    void ImGui_DisableIniFile()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = nullptr;   // disable saving and restoring window sizes and positions in imgui.ini
    }

    //
    // ImGui_NewFrame - Start the Dear ImGui frame
    // 
    void ImGui_NewFrame() {
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    //
    // ImGui_Combo strings
    // 
    pair<optional<int>, optional<int>> ImGui_Combo(const string& label, int current_index, const vector<string>& items, ImGuiComboFlags flags) {
        optional<int> new_index;
        optional<int> hovering_over;

        if (ImGui::BeginCombo(label.c_str(), items[current_index].c_str(), flags)) {
            for (int n = 0; n < items.size(); n++)
            {
                const bool is_selected = (current_index == n);
                if (ImGui::Selectable(items[n].c_str(), is_selected)) {
                    current_index = n;
                    new_index = n;
                }
                else if (ImGui::IsItemHovered(0)) {
                    hovering_over = n;
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
            return { new_index, hovering_over };
        }
        else
            return { new_index, hovering_over };
    }

    ///
    /// @brief ImGui_ComboImageAndText
    /// @param label - the label string on the right of the combo
    /// @param current_int - the index of the item that is the current selection
    /// @param imgData - array of SDL_Shared<SDL_Texture>
    /// @param textData - array of strings, if any, toe display after the image
    /// @param flags - any combo flags
    /// @return the selected index
    ///
    std::pair<std::optional<int>, std::optional<int>>
    ImGui_ComboImageAndText(const std::string& label, int current_index,
                            const std::vector<SDL_Shared<SDL_Texture>>& imgData, const std::vector<std::string>& textData,
                            Tau_Size imageDisplaySize, float heightPerItem, ImGuiComboFlags flags) {

        optional<int> new_index;
        optional<int> hovering_over;

        const char* combo_preview_value = textData[current_index].c_str();
        if (ImGui::BeginCombo(label.c_str(), combo_preview_value, flags)) {
            // display the list of items
            for (int n = 0; n < imgData.size(); n++)
            {
                SDL_Shared<SDL_Texture> img = imgData[n];
                const char* text = textData[n].c_str();

                ImGui::PushID(n);
                const bool is_selected = (current_index == n);
                if (ImGui::Selectable("", is_selected, 0, ImVec2(0.0, float(imageDisplaySize.h)))) {
                    current_index = n;
                    new_index = n;
                }
                else if (ImGui::IsItemHovered(0)) {
                    hovering_over = n;
                }

                ImGui::SameLine();
                ImGui_Image(img, imageDisplaySize);
                ImGui::SameLine();
                ImGui::Text(text);
                ImGui::SameLine();
                ImGui::Dummy(ImVec2(0.0f, heightPerItem));

                ImGui::PopID();

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
            return { new_index, hovering_over };
        }
        else
            return { new_index, hovering_over };
    }

    //
    // Tau_ImGui_Multi_Select strings
    //
    void ImGui_TreeNodeMulti_Select(const string& label, const vector<string>& items, vector<int> *selected) {
        if (ImGui::TreeNode(label.c_str())) {
            ImGui_HelpMarker(_("Hold CTRL and click to select multiple items.").c_str());
            for (int n = 0; n < items.size(); n++)
            {
                bool is_selected = (*selected)[n];
                if (ImGui::Selectable(items[n].c_str(), is_selected)) {
                    (*selected)[n] = is_selected;

                    if (!ImGui::GetIO().KeyCtrl)    // Clear selection when CTRL is not held
                        ranges::fill(*selected, 0);
                    (*selected)[n] ^= 1;
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::TreePop();
        }
    }

    //
    // ImGui_TreeNodeCheckboxes strings
    //
    void ImGui_TreeNodeCheckboxes(const string& label, const vector<string>& items, vector<int> *selected) {
        assert(items.size() == (*selected).size());
        if (ImGui::TreeNode(label.c_str())) {
            //HelpMarker(_("Hold CTRL and click to select multiple items.").c_str());
            for (int n = 0; n < items.size(); n++)
            {
                ImGui::Checkbox(items[n].c_str(), (bool*) &(*selected)[n]);
            }
            ImGui::TreePop();
        }
    }

    //
    // ImGui_Combo int's
    // 
    std::pair<std::optional<int>, std::optional<int>> ImGui_Combo_Ints(const string& label, int current_index, const vector<int>& int_items, ImGuiComboFlags flags) {
        vector<string> items;
        ranges::for_each(int_items, [&] (int n) { items.push_back(to_string(n)); });
        return ImGui_Combo(label, current_index, items, flags);
    }

    //
    // ImGui_Combo int range
    // 
    std::pair<std::optional<int>, std::optional<int>> ImGui_Combo_IntRange(const std::string& label, int current_index, int start, int count, ImGuiComboFlags flags) {
        vector<string> items;
        for (int n=start; n < start+count; ++n)
            items.push_back(to_string(n));
        return ImGui_Combo(label, current_index, items, flags);
    }

    //
    // ListBox2Columns
    // copied from ImGui::ListBox and modified to display in two columns
    // 
    pair<optional<int>, optional<int>>
    ImGui_ListBox2Columns(const std::string& label, int* current_item, const char* const leftData[], const char* const rightData[],
                          float data2xPosit, float xWindowWidth, size_t items_count, int height_in_items)
    {
        ImGuiContext& g = *TauImGuiContext;
        optional<int> new_index;
        optional<int> hovering_over;

        // Calculate size from "height_in_items"
        if (height_in_items < 0)
            height_in_items = ImMin((int)items_count, 7);
        float height_in_items_f = height_in_items + 0.25f;
        ImVec2 size(xWindowWidth, ImFloor(ImGui::GetTextLineHeightWithSpacing() * height_in_items_f + g.Style.FramePadding.y * 2.0f));

        if (!ImGui::BeginListBox(label.c_str(), size))
            return {new_index, hovering_over};

        // Assume all items have even height (= 1 line of text). If you need items of different height,
        // you can create a custom version of ListBox() in your code without using the clipper.
        bool value_changed = false;
        ImGuiListClipper clipper;
        clipper.Begin((int)items_count, ImGui::GetTextLineHeightWithSpacing()); // We know exactly our line height here so we pass it as a minor optimization, but generally you don't need to.
        while (clipper.Step())
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            {
                const char* leftText = leftData[i];
                const char* rightText = rightData[i];

                ImGui::PushID(i);
                bool selected {false};
                bool hovered {false};
                if (ImGui::Selectable(leftText, (i == *current_item)))
                    selected = true;
                if (ImGui::IsItemHovered())
                    hovered = true;

//                if (selected)
//                    ImGui::SetItemDefaultFocus();

                ImGui::SameLine(data2xPosit);
                if (ImGui::Selectable(rightText, (i == *current_item)))
                    selected = true;
                if (ImGui::IsItemHovered())
                    hovered = true;

                if (selected)
                {
                    *current_item = i;
                    new_index = i;
                    //cout << "new index " << i << endl;
                    value_changed = true;
                }
                if (hovered) {
                    hovering_over = i;
                }
                if (ImGui::IsItemHovered()) {
                    hovering_over = i;
                    //cout << "hovering over " << i << endl;
                }

//                if (hovering_over && hovering_over.value() == i)
//                    ImGui::SetItemDefaultFocus();

//                if (selected)
//                    ImGui::SetItemDefaultFocus();

                ImGui::PopID();
            }
        ImGui::EndListBox();

        if (value_changed) {
            ImGui::MarkItemEdited(g.LastItemData.ID);
            //cout << "MarkItemEdited " << new_index.value() << endl;
        }

        return {new_index, hovering_over};
    }

    //
    // ListBoxImageAndText
    // copied from ImGui_ListBox2Columns and modified to display an image followed by text
    //
    pair<optional<int>, optional<int>>
    ImGui_ListBoxImageAndText(const std::string& label, int* current_item, const std::vector<SDL_Shared<SDL_Texture>>& imgData, const std::vector<std::string>& textData,
                        float xWindowWidth, size_t items_count, int height_in_items, Tau_Size imageDisplaySize, float heightPerItem)
    {
        ImGuiContext& g = *TauImGuiContext;
        optional<int> new_index;
        optional<int> hovering_over;

        // Calculate size from "height_in_items"
        if (height_in_items < 0)
            height_in_items = ImMin((int)items_count, 7);
        float height_in_items_f = height_in_items + 0.25f;
        ImVec2 size(xWindowWidth, ImFloor(heightPerItem * height_in_items_f + g.Style.FramePadding.y * 2.0f));

        if (!ImGui::BeginListBox(label.c_str(), size))
            return {new_index, hovering_over};

        // Assume all items have even height (= 1 line of text). If you need items of different height,
        // you can create a custom version of ListBox() in your code without using the clipper.
        bool value_changed = false;
        ImGuiListClipper clipper;
        clipper.Begin((int)items_count, heightPerItem); // We know exactly our line height here so we pass it as a minor optimization, but generally you don't need to.
        while (clipper.Step())
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            {
                SDL_Shared<SDL_Texture> img = imgData[i];
                const char* text = textData[i].c_str();

                ImGui::PushID(i);
                bool selected {false};
                bool hovered {false};
                if (ImGui::Selectable("", (i == *current_item), 0, ImVec2(0.0, float(imageDisplaySize.h))))
                    selected = true;
                if (ImGui::IsItemHovered())
                    hovered = true;

                ImGui::SameLine();
                ImGui_Image(img, imageDisplaySize);
                ImGui::SameLine();
                ImGui::Text(text);
                ImGui::SameLine();
                ImGui::Dummy(ImVec2(0.0f, heightPerItem));

                if (selected)
                {
                    *current_item = i;
                    new_index = i;
                    cout << "new index " << i << endl;
                    value_changed = true;
                }
                if (hovered) {
                    hovering_over = i;
                }
                if (ImGui::IsItemHovered()) {
                    hovering_over = i;
                    //cout << "hovering over " << i << endl;
                }

                ImGui::PopID();
            }
        ImGui::EndListBox();

        if (value_changed) {
            ImGui::MarkItemEdited(g.LastItemData.ID);
            //cout << "MarkItemEdited " << new_index.value() << endl;
        }

        return {new_index, hovering_over};
    }

    // display a confirmation message with multiple buttons.  the index of the button that was pressed is returned, if any.
    // possible uses: OK/Cancel, Save/Discard, 
    optional<int> ImGui_Confirm(bool* show, const string& title, const string& message,
                                    const vector<string>& buttons, const vector<ImVec4>& buttonColors,
                                    ImGuiWindowFlags windowFlags)
    {
        ImGui::Begin(title.c_str(), show, windowFlags);
        ImGui::Text("");
        ImGui::Text(message.c_str());
        ImGui::Text("");

        optional<int> buttonPressed;
        int i=0;
        ImGui_SetButtonsCenteredPosX(buttons);
        for (const string& button : buttons) {
            ImGui::PushStyleColor(ImGuiCol_Button, buttonColors[i]);
            if (ImGui::Button(buttons[i].c_str()))
                buttonPressed = i;  // return the index of the pressed button
            ImGui::SameLine();
            ImGui::PopStyleColor(1);
            ++i;
        }
        ImGui::End();
    
        return buttonPressed;
    }

    // popup a single string message with a single OK button
    void ImGui_Popup(bool* done, const string& title, const string& message, ImGuiWindowFlags windowFlags) {
        ImGui::Begin(title.c_str(), nullptr, windowFlags);
        ImGui::Text("");
        ImGui::Text(message.c_str());
        ImGui::Text("");
        ImGui_SetButtonsCenteredPosX({ _("Close") });
        if (ImGui::Button(_("Close").c_str()))
            *done = true;
        ImGui::End();
    }

    // popup a vector of strings message with a single OK button
    void ImGui_Popup(bool* done, const std::string& title, const std::vector<std::string>& message, ImGuiWindowFlags windowFlags)
    {
        ImGui::Begin(title.c_str(), nullptr, windowFlags);
        ImGui::Text("");
        ImGui::BeginChild("child", ImVec2(1200, 500), false, windowFlags);
        for (const string& str : message)
            ImGui::Text(str.c_str());
        ImGui::EndChild();
        ImGui::Text("");
        ImGui_SetButtonsCenteredPosX({ _("Close") });
        if (ImGui::Button(_("Close").c_str()))
            *done = true;
        ImGui::End();
    }

    // popup the contents of a text file with a single OK button
    void ImGui_PopupFile(bool* done, const std::string& title, const std::string& filePath, ImGuiWindowFlags windowFlags)
    {
        Strings contents = ReadTextFileAsAStringArray(filePath, true);
        ImGui_Popup(done, title, contents, windowFlags);    
    }

    //
    // ImGui_Render
    // 
    void ImGui_Render(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer) {
        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    //
    // ImGui_Render_Clear
    // 
    void ImGui_Render_Clear(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer, const ImVec4& clearColor) {
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, (Uint8)(clearColor.x * 255), (Uint8)(clearColor.y * 255), (Uint8)(clearColor.z * 255), (Uint8)(clearColor.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    //
    // ImGui_Image(texture, size)
    // display the image on the current ImGui line in progress.
    // 
    void ImGui_Image(SDL_Shared<SDL_Texture> texture, Tau_Size size) {
        ImGui::Image((SDL_Texture*)texture, ImVec2((float)size.w, (float)size.h));
    }

    //
    // ImGui_Image(texture, rect)
    // display the image at the specified rect in the ImGui window.
    // 
    void ImGui_Image(SDL_Shared<SDL_Texture> texture, Tau_Rect rect) {
        ImGui::SetCursorPos(ImVec2((float)rect.x, (float)rect.y));
        ImGui::Image((SDL_Texture*)texture, ImVec2((float)rect.w, (float)rect.h));
    }

    //
    // ImGui_ImageButton(str_id, texture, size)
    // display the image button on the current ImGui line in progress.
    // 
    bool ImGui_ImageButton(const std::string& str_id, SDL_Shared<SDL_Texture> texture, Tau_Size size) {
        return ImGui::ImageButton(str_id.c_str(), (SDL_Texture*)texture, ImVec2((float)size.w, (float)size.h));
    }

    //
    // ImGui_ImageButton(str_id, texture, rect)
    // display the image button at the specified rect in the ImGui window.
    // 
    bool ImGui_ImageButton(const std::string& str_id, SDL_Shared<SDL_Texture> texture, Tau_Rect rect) {
        ImGui::SetCursorPos(ImVec2((float)rect.x, (float)rect.y));
        return ImGui::ImageButton(str_id.c_str(), (SDL_Texture*)texture, ImVec2((float)rect.w, (float)rect.h));
    }

    //
    // ImGui_BeginDisableOpaque
    // Disable buttons etc without changing the color of the disabled items.
    // This is useful in Help menus where you want to display the button without it being clickable or look like it's clickable.
    // 
    void ImGui_BeginDisableOpaque()
    {
        ImGuiContext& g = *GImGui;
        bool was_disabled = (g.CurrentItemFlags & ImGuiItemFlags_Disabled) != 0;
        g.CurrentItemFlags |= ImGuiItemFlags_Disabled;
        g.ItemFlagsStack.push_back(g.CurrentItemFlags);
        g.DisabledStackSize++;
    }

    //
    // ImGui_EndDisableOpaque
    //
    void ImGui_EndDisableOpaque()
    {
        ImGuiContext& g = *GImGui;
        IM_ASSERT(g.DisabledStackSize > 0);
        g.DisabledStackSize--;
        bool was_disabled = (g.CurrentItemFlags & ImGuiItemFlags_Disabled) != 0;
        g.ItemFlagsStack.pop_back();
        g.CurrentItemFlags = g.ItemFlagsStack.back();
    }

    //
    // ImGui_Text
    //
    void ImGui_Text(const string& str) {
        ImGui::Text(str.c_str());
    }

    //
    // ImGui_TextCentered
    // from: https://stackoverflow.com/questions/64653747/how-to-center-align-text-horizontally
    //
    void ImGui_TextCentered(const string& str) {
        ImGui::SetCursorPosX( (ImGui::GetWindowWidth() - ImGui::CalcTextSize(str.c_str()).x) / 2.f);
        ImGui::Text(str.c_str());
    }

    //
    // ImGui_ComputeButtonsCenteredPosX
    // from: https://stackoverflow.com/questions/64653747/how-to-center-align-text-horizontally
    //
    float ImGui_ComputeButtonsCenteredPosX(const vector<string>& buttonStrings) {
        string all;
        ranges::for_each(buttonStrings, [&] (const string& str) { all += str; });
        float textSize = ImGui::CalcTextSize(all.c_str()).x;
        float buttonSidesSize = ((float) buttonStrings.size()) * 10;
        return (ImGui::GetWindowWidth() - textSize - buttonSidesSize) / 2.f;
    }

    ///
    /// @brief ImGui_SetButtonsCenteredPosX
    /// 
    void ImGui_SetButtonsCenteredPosX(const std::vector<std::string>& buttonStrings) {
        ImGui::SetCursorPosX(ImGui_ComputeButtonsCenteredPosX(buttonStrings));
    }

    //
    // ImGui_TextIndentedMultiline
    //
    void ImGui_TextIndentedMultiline(std::string str, float leftIndent, float rightIndent) {
        float win_width = ImGui::GetWindowSize().x;
        ImGui::SameLine(leftIndent);
        ImGui::PushTextWrapPos(win_width - rightIndent); 
        ImGui::TextWrapped(str.c_str());
        ImGui::PopTextWrapPos();
    }

    //
    // ImGui_AddFont
    // 
    ImFont* ImGui_AddFont(const string& TTF_fontfile, float size_pixels, const ImFontConfig* font_cfg, const ImWchar* glyph_ranges) {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* font = io.Fonts->AddFontFromFileTTF(TTF_fontfile.c_str(), size_pixels, font_cfg, glyph_ranges);
        assert(font);
        return font;
    }

    // Helper to display a little (?) mark which shows a tooltip when hovered.
    // In your own code you may want to display an actual icon if you are using a merged icons font (see docs/FONTS.md)
    void ImGui_HelpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
}
