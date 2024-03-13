#ifndef SOGE_RENDERER_HPP
#define SOGE_RENDERER_HPP

#include <windows.h>
#include <WinUser.h>
#include <wrl.h>

#include <d3d.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#include <SOGE/System/Window.hpp>
#include <SOGE/Engine/EngineSetup.hpp>

namespace soge
{

    class Renderer
    {
        friend class SwapChain;
        friend class DeviceContextCommand;

    private:
        wrl::ComPtr<ID3D11Device> mDevice;
        wrl::ComPtr<IDXGIDevice> mDXGIDevice;
        wrl::ComPtr<IDXGIAdapter> mDXGIAdapter;
        wrl::ComPtr<IDXGIFactory> mDXGIFactory;
        wrl::ComPtr<ID3D11DeviceContext> mDeviceContext;
        D3D_FEATURE_LEVEL mFeatureLevel;

        std::unique_ptr<SwapChain> mSwapChain;
        std::unique_ptr<DeviceContextCommand> mDeviceContextCommand;

    protected:
        Renderer() = default;
        static Renderer* sInstance;

    public:
        Renderer(Renderer&)         = delete;
        void operator = (Renderer&) = delete;

        void Init(const std::unique_ptr<Window>& aSystemWindow);
        void Release();
        void Render();

    public:
        static Renderer* GetInstance();

    };
}

#endif // !SOGE_RENDERER_HPP
