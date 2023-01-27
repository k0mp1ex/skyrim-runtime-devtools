#include <imgui.h>

#include "modules/Logger.hpp"

namespace SRDT::Modules {
    void Logger::Draw() {
        UpdateData();

        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Logs Visualizer");

        for (const auto& log: logs) {
            ImGui::Text("Filename: %s", log.fileName.c_str());
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}
