#include <imgui.h>

#include "modules/HelloWorld.hpp"

namespace SRDT::Modules {
    void HelloWorld::Draw() {
        ImGui::Begin("Hello, World!");
        ImGui::End();
    }
}
