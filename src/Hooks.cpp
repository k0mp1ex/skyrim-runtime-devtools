#include "Hooks.hpp"
#include "Renderer.hpp"

namespace SRDT::Hooks {
    REL::Relocation<decltype(D3DInit)> originalD3DInit;
    REL::Relocation<decltype(DXGIPresent)> originalDXGIPresent;
    bool dx11_initialized = false;

    void D3DInit() {
        logger::trace("void D3DInit(int) called");
        originalD3DInit();
        Renderer::Initialize();
        dx11_initialized = true;
    }

    void DXGIPresent(std::uint32_t arg) {
//        logger::trace("void DXGIPresent(int) called");
        originalDXGIPresent(arg);
        if (!dx11_initialized) return;
        Renderer::Draw();
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

    void Setup() {
        logger::trace("Allocating trampoline and initializing hooks...");
        SKSE::AllocTrampoline(14 * 2);
        HookD3DInit();
        HookDXGIPresent();
        logger::trace("Hooks setup completed.");
    }
}
