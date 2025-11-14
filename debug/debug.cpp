#include "debug.hpp"

#include <platf/glfw/main.h>

#include <nouser/state.hpp>
#include <wraps/input.hpp>

#include <node/node.hpp>

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

    void gui_hier(Node* node, s32* id) {
        ImGui::PushID(*id);

        if (node->children.size() != 0) {
            if (ImGui::Button(node->DEBUG_expanded? "-" : "+"))
                node->DEBUG_expanded = !node->DEBUG_expanded;
            ImGui::SameLine();
        }

        if (ImGui::Selectable(node->name.c_str()))
            node->DEBUG_expanded = !node->DEBUG_expanded;

        ImGui::Indent(24);

        if (node->DEBUG_expanded)
            for (Node* child : node->children)
                gui_hier(child, &++*id); // silly

        ImGui::Unindent(24);    
        ImGui::PopID();    
    }

    void debug_endFrame(Node* scene) {
        if (get_key_down(Key::F1))
            state::is_debug = !state::is_debug;

        if (state::is_debug) {
            ImGui::Begin("debug - hierarchy");

            s32 temp = 0;
            gui_hier(scene, &temp);

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void debug_end() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
