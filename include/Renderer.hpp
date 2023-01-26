#pragma once

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#include "D3D.hpp"
#include "Module.hpp"
#include "modules/HelloWorld.hpp"
#include "modules/Logger.hpp"

namespace SRDT::D3D {
    class Renderer {
        Renderer() = default;
        ~Renderer() = default;
    public:
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&&) = delete;

        static Renderer& GetSingleton() {
            static Renderer singleton;
            return singleton;
        };

        bool Initialize();
        void RegisterModule(std::unique_ptr<Module> module);
        void Render() const;
        void EnableVsync();
        void DisableVsync();
        [[nodiscard]] const D3DData& GetData() const;
    private:
        [[nodiscard]] bool InitializeD3D();
        [[nodiscard]] bool InitializeImGui() const;
        void StartRender() const;
        void EndRender() const;
        void Draw() const;

        D3DData _data {};
        std::vector<std::unique_ptr<Module>> _modules;
        bool _enableVsync {};
    };

    void Setup();
}
