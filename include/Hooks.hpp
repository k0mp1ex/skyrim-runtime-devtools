#pragma once

namespace SRDT::Hooks {
    void D3DInit();
    void DXGIPresent(std::uint32_t);
    bool ScriptGetsProcessed(RE::BSScript::LinkerProcessor*, const RE::BSFixedString&);
    void Setup();
}
