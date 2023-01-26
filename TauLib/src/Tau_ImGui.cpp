#include "Tau_ImGui.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <SDL.h>
#include <ranges>
#include <algorithm>
#include "Lang.h"

using namespace std;

namespace Tau { // to avoid conflict with other libraries

    //
    // Tau_ImGui_Init
    //
    void Tau_ImGui_Init(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer) {
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
        ImGui::CreateContext();

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

        io.Fonts->AddFontDefault();
    }

    //
    // Tau_ImGui_Quit
    //
    void Tau_ImGui_Quit() {
        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    //
    // Tau_DisableImGuiIniFile
    //
    void Tau_DisableImGuiIniFile()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = nullptr;   // disable saving and restoring window sizes and positions in imgui.ini
    }

    //
    // Tau_ImGui_NewFrame - Start the Dear ImGui frame
    // 
    void Tau_ImGui_NewFrame() {
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    //
    // Tau_ImGui_Combo strings
    // 
    int Tau_ImGui_Combo(const string& label, int current_index, const vector<string>& items, ImGuiComboFlags flags) {
        if (ImGui::BeginCombo(label.c_str(), items[current_index].c_str(), flags)) {
            for (int n = 0; n < items.size(); n++)
            {
                const bool is_selected = (current_index == n);
                if (ImGui::Selectable(items[n].c_str(), is_selected))
                    current_index = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        return current_index;
    }

    //
    // Tau_ImGui_Multi_Select strings
    //
    void Tau_ImGui_TreeNodeMulti_Select(const string& label, const vector<string>& items, vector<int> *selected) {
        if (ImGui::TreeNode(label.c_str())) {
            HelpMarker(_("Hold CTRL and click to select multiple items.").c_str());
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
    // Tau_ImGui_TreeNodeCheckboxes strings
    //
    void Tau_ImGui_TreeNodeCheckboxes(const string& label, const vector<string>& items, vector<int> *selected) {
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
    // Tau_ImGui_Combo int's
    // 
    int Tau_ImGui_Combo_Ints(const string& label, int current_index, const vector<int>& int_items, ImGuiComboFlags flags) {
        vector<string> items;
        ranges::for_each(int_items, [&] (int n) { items.push_back(to_string(n)); });
        return Tau_ImGui_Combo(label, current_index, items, flags);
    }

    //
    // Tau_ImGui_Combo int range
    // 
    int Tau_ImGui_Combo_IntRange(const std::string& label, int current_index, int start, int count, ImGuiComboFlags flags) {
        vector<string> items;
        for (int n=start; n < start+count; ++n)
            items.push_back(to_string(n));
        return Tau_ImGui_Combo(label, current_index, items, flags);
    }

    // display a confirmation message with multiple buttons.  the index of the button that was pressed is returned, if any.
    // possible uses: OK/Cancel, Save/Discard, 
    optional<int> Tau_ImGui_Confirm(bool* show, const string& title, const string& message,
                                    const vector<string>& buttons, const vector<ImVec4>& buttonColors,
                                    ImGuiWindowFlags windowFlags)
    {
        ImGui::Begin(title.c_str(), show, windowFlags);
        ImGui::Text("");
        ImGui::Text(message.c_str());
        ImGui::Text("");

        optional<int> buttonPressed;
        int i=0;
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

    // popup a message with a single OK button
    void Tau_ImGui_Popup(bool* show, const string& title, const string& message, ImGuiWindowFlags windowFlags) {
        ImGui::Begin(title.c_str(), show, windowFlags);
    ImGui::Text("");
    ImGui::Text(message.c_str());
    ImGui::Text("");
    if (ImGui::Button(_("Close").c_str()))
        *show = true;
    ImGui::End();
    }

    /// 
    /// @brief Tau_SetPosition - SetNextWindowPos
    /// 
    void Tau_SetPosition()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImVec2 newpos(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
        ImGui::SetNextWindowPos(newpos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    }

    //
    // Tau_ImGui_Render
    // 
    void Tau_ImGui_Render(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer) {
        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    //
    // Tau_ImGui_Render_Clear
    // 
    void Tau_ImGui_Render_Clear(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer, const ImVec4& clearColor) {
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, (Uint8)(clearColor.x * 255), (Uint8)(clearColor.y * 255), (Uint8)(clearColor.z * 255), (Uint8)(clearColor.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    //
    // Tau_ImGui_AddFont
    // 
    ImFont* Tau_ImGui_AddFont(const string& TTF_fontfile, float size_pixels, const ImFontConfig* font_cfg, const ImWchar* glyph_ranges) {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* font = io.Fonts->AddFontFromFileTTF(TTF_fontfile.c_str(), size_pixels, font_cfg, glyph_ranges);
        assert(font);
        return font;
    }

    // Helper to display a little (?) mark which shows a tooltip when hovered.
    // In your own code you may want to display an actual icon if you are using a merged icons font (see docs/FONTS.md)
    void HelpMarker(const char* desc)
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
