#include "Tau_ImGui.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
//#include "imgui_impl_sdlrenderer.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#include <ranges>
#include <algorithm>
#include "Lang.h"

using namespace std;

namespace Tau { // to avoid conflict with other libraries

    //
    // Tau_ImGui_Init
    //
    void Tau_ImGui_Init(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer) {
        // from the example code in imgui/examples/example_sdl_opengl3/main.cpp

        assert(window);
        assert(renderer);

#if 0
        // Setup window
        //SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
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

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
        // GL 3.2 Core + GLSL 150
        const char* glsl_version = "#version 150";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
//        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
//        SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
        SDL_GLContext gl_context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
        ImGui_ImplOpenGL3_Init(glsl_version);

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
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    //
    // Tau_ImGui_NewFrame - Start the Dear ImGui frame
    // 
    void Tau_ImGui_NewFrame() {
        ImGui_ImplOpenGL3_NewFrame();
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

    //
    // Tau_ImGui_Render
    // 
    void Tau_ImGui_Render(SDL_Shared<SDL_Window> window) {
        ImGui::Render();
        ImGuiIO& io = ImGui::GetIO();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
//        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);
    }

    //
    // Tau_ImGui_Render
    // 
    void Tau_ImGui_Render(SDL_Shared<SDL_Window> window, const ImVec4& clearColor) {
        ImGui::Render();
        ImGuiIO& io = ImGui::GetIO();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);
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
