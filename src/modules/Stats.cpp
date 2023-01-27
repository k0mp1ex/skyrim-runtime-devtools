#include <imgui.h>

#include "modules/Stats.hpp"

namespace SRDT::Modules {

    void Stats::Draw() {
        ImGui::Begin("Stats", NULL, ImGuiWindowFlags_NoResize);

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        ImGui::End();
    }
}
