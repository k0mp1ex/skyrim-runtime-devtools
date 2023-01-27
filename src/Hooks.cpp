#include "Hooks.hpp"
#include "Renderer.hpp"
#include "modules/Scripts.hpp"

namespace SRDT::Hooks {
    REL::Relocation<decltype(D3DInit)> originalD3DInit;
    REL::Relocation<decltype(DXGIPresent)> originalDXGIPresent;
    REL::Relocation<decltype(ScriptGetsProcessed)> originalScriptGetsProcessed;
    bool successfullyInitialized = false;

    void D3DInit() {
        originalD3DInit();
        auto& renderer = SRDT::Renderer::GetSingleton();
        successfullyInitialized = renderer.Initialize();
    }

    void DXGIPresent(std::uint32_t arg) {
        originalDXGIPresent(arg);
        if (!successfullyInitialized) return;
        auto& renderer = SRDT::Renderer::GetSingleton();
        renderer.Render();
    }

    bool ScriptGetsProcessed(RE::BSScript::LinkerProcessor* self, const RE::BSFixedString& className) {
        bool result = originalScriptGetsProcessed(self, className);
        SRDT::Modules::Scripts::AddScript(className);
        return result;
    }

    void HookD3DInit() {
        auto& trampoline = SKSE::GetTrampoline();
        originalD3DInit = trampoline.write_call<5>(REL::Relocation<decltype(D3DInit)>(RELOCATION_ID(75595, 77226), REL::VariantOffset(0x9, 0x275, 0x9)).address(),
                                                   reinterpret_cast<uintptr_t>(D3DInit));
        logger::trace("D3DInit hook written.");
    }

    void HookDXGIPresent() {
        auto& trampoline = SKSE::GetTrampoline();
        originalDXGIPresent = trampoline.write_call<5>(REL::Relocation<decltype(DXGIPresent)>(RELOCATION_ID(75461, 77246), 0x9).address(),
                                                       reinterpret_cast<uintptr_t>(DXGIPresent));
        logger::trace("DXGIPresent hook written.");
    }

    void HookScriptGetsProcessed() {
        REL::Relocation<std::uintptr_t> vtbl { RE::VTABLE_BSScript__LinkerProcessor[0] };
        originalScriptGetsProcessed = vtbl.write_vfunc(3, ScriptGetsProcessed);
        logger::info("ScriptGetsProcessed hook written.");
    }

    void Setup() {
        logger::trace("Allocating trampoline and initializing hooks...");
        SKSE::AllocTrampoline(14 * 2);
        HookD3DInit();
        HookDXGIPresent();
        HookScriptGetsProcessed();
        logger::trace("Hooks setup completed.");
    }
}
