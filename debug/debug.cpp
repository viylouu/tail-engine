#include "debug.hpp"

#include <platf/glfw/main.h>

#include <nouser/state.hpp>

#include <deps/imgui/imgui.h>
#include <deps/imgui/backends/imgui_impl_glfw.h>
#include <deps/imgui/backends/imgui_impl_opengl3.h>

namespace tail {
    void debug_init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); UNUSED(io);
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(CAST(FUR_glfw_platfState*, state::platf->spec)->window, true);
        ImGui_ImplOpenGL3_Init("#version 150");
    }

    void debug_startFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void debug_endFrame() {
        ImGui::Begin("debug");

        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void debug_end() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
