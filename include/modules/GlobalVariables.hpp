#pragma once

#include "Module.hpp"

namespace SRDT::Modules {
    struct GlobalVariableData {
        std::string editorID;
        float value;
    };

    class GlobalVariables : public Module {
    private:
        inline static std::vector<GlobalVariableData> globalVariables;
    public:
        GlobalVariables() = default;
        ~GlobalVariables() override = default;
        void Draw() override;

        static void UpdateData(bool forceUpdate = false) {
            //TODO: Check when the data can be updated and add update intervals
            if (!globalVariables.empty()) {
                if (!forceUpdate) return;
                globalVariables.clear();
            }

            logger::info("Updating global variables...");
            logger::info("forceUpdate = {}", forceUpdate);

            const auto& [forms, lock] = RE::TESForm::GetAllForms();
            const RE::BSReadLockGuard locker{ lock };

            for (auto& [id, form] : *forms) {
                auto* globalVariable = form->As<RE::TESGlobal>();
                if (globalVariable)
                    globalVariables.emplace_back(GlobalVariableData{ globalVariable->GetFormEditorID(), globalVariable->value });
            }
            logger::info("{} global variables loaded.", globalVariables.size());
        }
    };
}
