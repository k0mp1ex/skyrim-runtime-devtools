#pragma once

#include "Module.hpp"

namespace SRDT::Modules {
    struct ScriptData {
        std::string name;
        std::string parentChain;
    };

    class Scripts : public Module {
    private:
        inline static std::vector<ScriptData> scripts;
    public:
        Scripts() = default;
        ~Scripts() override = default;
        void Draw() override;

        static void AddScript(const RE::BSFixedString& scriptName) {
            RE::BSScript::IVirtualMachine* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
            RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> typeInfo;

            // NOTE: Some scripts WILL fail to load, mainly scripts that don't exist, but other scripts reference it
            // When looping the class map, check the objectTypeinfo link status to ensure it is NOT `kLinkInvalid`
            if (vm && vm->GetScriptObjectType(scriptName, typeInfo)) {
                if (!typeInfo->IsLinked()) {
                    logger::info("!!!!! Script {} is not linked, skipping it.", scriptName);
                    return;
                }
                ScriptData script {
                    typeInfo->GetName(),
                    typeInfo->parentTypeInfo ? typeInfo->parentTypeInfo->GetName() : ""
                };
                logger::info("Adding script data {}", scriptName);
                scripts.emplace_back(script);
            }
        }
    };
}
