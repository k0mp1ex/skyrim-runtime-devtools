#include <imgui.h>

#include "modules/Scripts.hpp"

namespace SRDT::Modules {

    void Scripts::Draw() {
        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Scripts");

        ImGui::Text("%zu scripts loaded.", scripts.size());
        ImGui::Spacing();

        for (const auto& script : scripts) {
            ImGui::Text("%s => %s", script.name.c_str(), script.parentChain.c_str());
        }

        ImGui::End();
    }
}
