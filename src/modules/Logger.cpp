#include <imgui.h>

#include "modules/Logger.hpp"

namespace SRDT::Modules {
    void Logger::Draw() {
        UpdateData();

        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Logs");

        for (const auto& log: logs) {
            ImGui::Text("Filename: %s", log.fileName.c_str());
        }

        ImGui::End();
    }
}
