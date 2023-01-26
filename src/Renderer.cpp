#include "Renderer.hpp"

#include "modules/GlobalVariables.hpp"
#include "modules/Logger.hpp"
#include "modules/Scripts.hpp"

namespace SRDT::D3D {
    bool Renderer::Initialize() {
        return InitializeD3D() && InitializeImGui();
    }

    void Renderer::RegisterModule(std::unique_ptr<Module> module) {
        _modules.push_back(std::move(module));
    }

    void Renderer::Render() const {
        StartRender();
        Draw();
        EndRender();
    }

    void Renderer::EnableVsync() {
        _enableVsync = true;
    }

    void Renderer::DisableVsync() {
        _enableVsync = false;
    }

    [[nodiscard]] const D3DData& Renderer::GetData() const {
        return _data;
    }

    [[nodiscard]] bool Renderer::InitializeD3D() {
        auto render_manager = RE::BSRenderManager::GetSingleton();
        if (!render_manager) {
            logger::error("Cannot find render manager. Initialization failed!");
            return false;
        }

        auto render_data = render_manager->GetRuntimeData();

        logger::trace("Getting swapchain...");
        _data.swapChain = render_data.swapChain;
        if (!_data.swapChain) {
            logger::error("Cannot find swapchain. Initialization failed!");
            return false;
        }

        logger::trace("Getting swapchain desc...");
        if (_data.swapChain->GetDesc(std::addressof(_data.swapChainDesc)) < 0) {
            logger::error("IDXGISwapChain::GetDesc failed.");
            return false;
        }

        _data.device = render_data.forwarder;
        _data.deviceContext = render_data.context;
        _data.renderTargetView = render_data.renderView;

        return true;
    }

    [[nodiscard]] bool Renderer::InitializeImGui() const {
        logger::trace("Initializing ImGui...");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        auto& io = ImGui::GetIO(); (void)io;
        io.MouseDrawCursor = true;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;
        //io.ConfigViewportsNoDefaultParent = true;
        //io.ConfigDockingAlwaysTabBar = true;
        //io.ConfigDockingTransparentPayload = true;

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        if (!ImGui_ImplWin32_Init(_data.swapChainDesc.OutputWindow)) {
            logger::error("ImGui initialization failed (Win32)");
            return false;
        }
        if (!ImGui_ImplDX11_Init(_data.device, _data.deviceContext)) {
            logger::error("ImGui initialization failed (DX11)");
            return false;
        }

        WndProcHook::func = reinterpret_cast<WNDPROC>(
            SetWindowLongPtrA(
                _data.swapChainDesc.OutputWindow,
                GWLP_WNDPROC,
                reinterpret_cast<LONG_PTR>(WndProcHook::thunk)));
        if (!WndProcHook::func) {
            logger::error("SetWindowLongPtrA failed!");
            return false;
        }

        logger::trace("ImGui initialized!");
        return true;
    }

    void Renderer::StartRender() const {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    void Renderer::EndRender() const {
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        auto& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        _data.swapChain->Present(_enableVsync, 0);
    }

    void Renderer::Draw() const {
        std::ranges::for_each(_modules, [](const std::unique_ptr<Module>& module) {
            if (module->CanDraw()) {
                module->Draw();
            }
        });
    }

    void Setup() {
        auto& renderer = SRDT::D3D::Renderer::GetSingleton();
        renderer.RegisterModule(std::make_unique<SRDT::Modules::GlobalVariables>());
        renderer.RegisterModule(std::make_unique<SRDT::Modules::Scripts>());
        renderer.RegisterModule(std::make_unique<SRDT::Modules::Logger>());
    }

}
