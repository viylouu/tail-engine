#include "debug.hpp"

#include <platf/glfw/main.h>

#include <nouser/state.hpp>
#include <wraps/input.hpp>

#include <node/node.hpp>

#include <deps/imgui/imgui.h>
#include <deps/imgui/misc/cpp/imgui_stdlib.h>
#include <deps/imgui/backends/imgui_impl_glfw.h>
#include <deps/imgui/backends/imgui_impl_opengl3.h>

namespace tail {
    Node* DEBUG_sel;

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
            DEBUG_sel = node;

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

            if (DEBUG_sel) {
                ImGui::Begin("debug - properties"); 

                ImGui::InputText("name", &DEBUG_sel->name);
                
                f32 vals1[3] = {DEBUG_sel->pos.x, DEBUG_sel->pos.y, DEBUG_sel->pos.z};
                ImGui::InputFloat3("Position", vals1);
                DEBUG_sel->pos.x = vals1[0];
                DEBUG_sel->pos.y = vals1[1];
                DEBUG_sel->pos.z = vals1[2];

                f32 vals2[3] = {DEBUG_sel->rot.x, DEBUG_sel->rot.y, DEBUG_sel->rot.z};
                ImGui::InputFloat3("Rotation", vals2);
                DEBUG_sel->rot.x = vals2[0];
                DEBUG_sel->rot.y = vals2[1];
                DEBUG_sel->rot.z = vals2[2];

                f32 vals3[3] = {DEBUG_sel->scale.x, DEBUG_sel->scale.y, DEBUG_sel->scale.z};
                ImGui::InputFloat3("Scale", vals3);
                DEBUG_sel->scale.x = vals3[0];
                DEBUG_sel->scale.y = vals3[1];
                DEBUG_sel->scale.z = vals3[2];

                for (Component* comp : DEBUG_sel->components) {
                    if (ImGui::Button(comp->DEBUG_expanded? "-" : "+"))
                        comp->DEBUG_expanded = !comp->DEBUG_expanded;
                    ImGui::SameLine();
                    ImGui::Text("%s", comp->name.c_str());

                    if (comp->DEBUG_expanded)
                        for (Variable var : comp->vars)
                            switch(var.type) {
                                case VarType::INTEGER: {
                                    ImGuiDataType type = -1;
                                    switch (var.size) {
                                        case sizeof(s8): type = ImGuiDataType_S8; break;
                                        case sizeof(s16): type = ImGuiDataType_S16; break;
                                        case sizeof(s32): type = ImGuiDataType_S32; break;
                                        case sizeof(s64): type = ImGuiDataType_S64; break;
                                        default:
                                            printf("unsupported integer size %d!\n", (s32)var.size); break;
                                    }
                                    
                                    if (type < 0) break;

                                    ImGui::InputScalar(var.name.c_str(), type, var.var);
                                    break;
                                } case VarType::UNSIGNED_INTEGER: {
                                    ImGuiDataType type = -1;
                                    switch(var.size) {
                                        case sizeof(u8): type = ImGuiDataType_U8; break;
                                        case sizeof(u16): type = ImGuiDataType_U16; break;
                                        case sizeof(u32): type = ImGuiDataType_U32; break;
                                        case sizeof(u64): type = ImGuiDataType_U64; break;
                                        default:
                                            printf("unsupported unsigned integer size %d!\n", (s32)var.size); break;
                                    }

                                    if (type < 0) break;

                                    ImGui::InputScalar(var.name.c_str(), type, var.var);
                                    break;
                                } case VarType::FLOAT: {
                                    ImGuiDataType type = -1;
                                    switch(var.size) {
                                        case sizeof(f32): type = ImGuiDataType_Float; break;
                                        case sizeof(f64): type = ImGuiDataType_Double; break;
                                        default:
                                            printf("unsupported float size %d!\n", (s32)var.size); break;
                                    }

                                    if (type < 0) break;

                                    ImGui::InputScalar(var.name.c_str(), type, var.var);
                                    break;
                                } case VarType::STRING: {
                                    ImGui::InputText(var.name.c_str(), (std::string*)var.var);
                                    break;
                                } case VarType::BOOL: {
                                    ImGui::Checkbox(var.name.c_str(), (bool*)var.var);
                                    break;
                                } case VarType::CUSTOM: {
                                    var.custom();
                                    break;
                                } case VarType::VECTOR_2: {
                                    v2* v = (v2*)var.var;
                                    f32 arr[2] = {v->x,v->y};
                                    ImGui::InputFloat2(var.name.c_str(), arr);
                                    v->x = arr[0];
                                    v->y = arr[1];
                                    break;
                                } case VarType::VECTOR_3: {
                                    v3* v = (v3*)var.var;
                                    f32 arr[3] = {v->x,v->y,v->z};
                                    ImGui::InputFloat3(var.name.c_str(), arr);
                                    v->x = arr[0];
                                    v->y = arr[1];
                                    v->z = arr[2];
                                    break;
                                } case VarType::VECTOR_4: {
                                    v4* v = (v4*)var.var;
                                    f32 arr[4] = {v->x,v->y,v->z,v->w};
                                    ImGui::InputFloat4(var.name.c_str(), arr);
                                    v->x = arr[0];
                                    v->y = arr[1];
                                    v->z = arr[2];
                                    v->w = arr[3];
                                    break;
                                } case VarType::COLOR_3: {
                                    v3* v = (v3*)var.var;
                                    f32 arr[3] = {v->x,v->y,v->z};
                                    ImGui::ColorPicker3(var.name.c_str(), arr);
                                    v->x = arr[0];
                                    v->y = arr[1];
                                    v->z = arr[2];
                                    break;
                                } case VarType::COLOR_4: {
                                    v4* v = (v4*)var.var;
                                    f32 arr[4] = {v->x,v->y,v->z,v->w};
                                    ImGui::ColorPicker4(var.name.c_str(), arr);
                                    v->x = arr[0];
                                    v->y = arr[1];
                                    v->z = arr[2];
                                    v->w = arr[3];
                                    break;
                                } default:
                                    printf("var type unsupported in editor!\n"); break;
                            }
                }

                ImGui::End();
            }
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
