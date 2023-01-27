#include <imgui.h>

#include "modules/GlobalVariables.hpp"

namespace SRDT::Modules {

    void GlobalVariables::Draw() {
        UpdateData();

        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Global Variables");

        static ImGuiTableFlags tableFlags =
            ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
            | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
            | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
            | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
            | ImGuiTableFlags_SizingFixedFit;
        static ImGuiSliderFlags floatFlags = ImGuiSliderFlags_None;

        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
        const ImVec2 outer_size_value = ImVec2(0.0f, TEXT_BASE_HEIGHT * 12);
        const bool outer_size_enabled = true;
        const float inner_width_with_scroll = 0.0f;
        const float inner_width_to_use = (tableFlags & ImGuiTableFlags_ScrollX) ? inner_width_with_scroll : 0.0f;

        if (ImGui::BeginTable("global_variables", 2, tableFlags, outer_size_enabled ? outer_size_value : ImVec2(0, 0), inner_width_to_use)) {
            ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible

            //Columns
            ImGui::TableSetupColumn("EditorID", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHide, 0.0f);
            ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_PreferSortDescending, 0.0f);
            ImGui::TableHeadersRow();

            //Rows
            for (auto& globalVariable: globalVariables) {
                ImGui::TableNextRow();
                if (ImGui::TableSetColumnIndex(0))
                    ImGui::TextUnformatted(globalVariable.editorID.c_str());
                if (ImGui::TableSetColumnIndex(1))
                    ImGui::DragFloat("", &globalVariable.value, 0.05f, -FLT_MAX, +FLT_MAX, "%.2f", floatFlags); //TODO: Why all data is being updated instead of just the current value?
            }

            ImGui::EndTable();
        }

        ImGui::End();
    }
}
