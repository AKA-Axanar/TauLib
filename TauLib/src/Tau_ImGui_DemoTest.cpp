#include "TauLib.h"
#include "Tau_ImGui_DemoTest.h"
#include "Tau_ImGui.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "Display.h"
#include "Win.h"

using namespace std;
using namespace Tau;

namespace Tau {
//
// ImGui_DemoTest - calls ImGui::ShowDemoWindow() from scratch using Tau routines
// creates the SDL_Window and SDL_Renderer and calls other setup routines for you.
//
    void ImGui_DemoTest() {
    Init_SDL();
    //Init_TTF();
    //Init_Mixer();

    Win win;

    int displayIndex = 0;
    win.CreateWin("TauBleem", Display::GetCenteredDisplayPosit(displayIndex), { 1280, 720 },
        SDL_WINDOW_OPENGL | 
        SDL_WINDOW_ALLOW_HIGHDPI,                                   // https://wiki.libsdl.org/SDL_WindowFlags
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);      // https://wiki.libsdl.org/SDL_RendererFlags

    int numDisplays = SDL_GetNumVideoDisplays();
    Tau_Rect displayBounds;
    SDL_GetDisplayBounds(displayIndex, &displayBounds);

    win.ClearWin(Tau_black);
    SDL_RenderPresent(win.renderer);

    Tau::ImGui_DemoTest(win.window, win.renderer);

    //Quit_Mixer();
    //Quit_TTF();
    SDL_DestroyRenderer(win.renderer);
    SDL_DestroyWindow(win.window);
    Quit_SDL();
    }

    //
    // ImGui_DemoTest - pass it an existing SDL_Window and SDL_Renderer.  calls ImGui::ShowDemoWindow() using Tau routines.
    //
    void ImGui_DemoTest(SDL_Shared<SDL_Window> window, SDL_Shared<SDL_Renderer> renderer) {
        // from the example code in imgui/examples/example_sdl_sdlrenderer/main.cpp

        Tau_ImGui_Init(window, renderer);

        // enable keyboard and controller control over menu
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // Main loop
        bool done = false;
        while (!done)
        {
            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    done = true;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                    done = true;
            }

            // Start the Dear ImGui frame
            Tau_ImGui_NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            // Rendering
            Tau_ImGui_Render(window);
        }

        Tau_ImGui_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
