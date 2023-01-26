#include <imgui.h>

#include "modules/Logger.hpp"

namespace SRDT::Modules {
    void Logger::Draw() {
        static float f = 0.0f;
        static int local_counter = 0;

        ImGui::Begin("Logger Visualizer");

        ImGui::Text("This is some useful text.");
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        if (ImGui::Button("Button")) local_counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", local_counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}
