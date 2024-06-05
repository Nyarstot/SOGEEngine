#ifndef SOGE_RENDERER_HPP
#define SOGE_RENDERER_HPP

#include <windows.h>
#include <WinUser.h>
#include <wrl.h>

#include <d3d.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#include <SOGE/System/Window.hpp>
#include <SOGE/Engine/EngineSetup.hpp>
#include "SOGE/Containers/LayerStack.hpp"

namespace soge
{

    class Renderer final
    {
        friend class SwapChain;
        friend class VertexBuffer;
        friend class IndexBuffer;
        friend class VertexShader;
        friend class PixelShader;
        friend class Sprite;
        friend class SpriteFont;
        friend class ZBuffer;

        friend class IDrawable;

    private:
        Window* mAppWindow = nullptr;

        wrl::ComPtr<ID3D11Device> mDevice;
        wrl::ComPtr<IDXGIDevice> mDXGIDevice;
        wrl::ComPtr<IDXGIAdapter> mDXGIAdapter;
        wrl::ComPtr<IDXGIAdapter3> mDXGIAdapter3;
        wrl::ComPtr<IDXGIFactory> mDXGIFactory;
        wrl::ComPtr<ID3D11DeviceContext> mDeviceContext;
        wrl::ComPtr<ID3D11RasterizerState> mRasterizerState;

        D3D_FEATURE_LEVEL mFeatureLevel;

        std::unique_ptr<SwapChain> mSwapChain;
        std::unique_ptr<ZBuffer> mZBuffer;

    protected:
        Renderer() = default;
        static Renderer* sInstance;

        void CreateRasterizer();
        void PrintGPUInfo(IDXGIAdapter* aDXGIAdapter);

    public:
        Renderer(Renderer&)         = delete;
        void operator = (Renderer&) = delete;

        void Init(const std::unique_ptr<Window>& aWindow);
        void SetupViewport();
        void Release();
        void Render(LayerStack& aRenderLayers, float aDeltaTime);
        void DrawIndexed(UINT aIndicesCount) noexcept(!SOGE_DEBUG);

        ID3D11RasterizerState* GetRasterizerState() const { return mRasterizerState.Get(); }
        ID3D11Device* GetDevice() const { return mDevice.Get(); }
        ID3D11DeviceContext* GetDeviceContext() const { return mDeviceContext.Get(); }

    public:
        static Renderer* GetInstance();

    };
}

#endif // !SOGE_RENDERER_HPP
