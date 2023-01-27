#include <imgui.h>

#include "modules/Scripts.hpp"

namespace SRDT::Modules {

    void Scripts::Draw() {
        ImGui::Begin("Scripts Visualizer!");
        ImGui::Text("%zu scripts loaded.", scripts.size());
        ImGui::Spacing();

        for (const auto& script : scripts) {
            ImGui::Text("%s => %s", script.name.c_str(), script.parentChain.c_str());
        }

        ImGui::End();
    }
}
