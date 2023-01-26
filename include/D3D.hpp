#pragma once

#include <d3d11.h>

struct D3DData {
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    IDXGISwapChain* swapChain;
    ID3D11RenderTargetView1* renderTargetView;
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
};

struct WndProcHook {
    static inline WNDPROC func;
    static LRESULT thunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        auto& io = ImGui::GetIO();
        if (uMsg == WM_KILLFOCUS) {
            io.ClearInputCharacters();
            io.ClearInputKeys();
        }

        return func(hWnd, uMsg, wParam, lParam);
    }
};
