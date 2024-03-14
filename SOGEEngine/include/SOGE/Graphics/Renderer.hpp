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
        friend class VertexBuffer;
        friend class Triangle;
        friend class Shader;
        friend class VertexShader;
        friend class PixelShader;
        friend class IndexBuffer;

    private:
        wrl::ComPtr<ID3D11Device> mDevice;
        wrl::ComPtr<IDXGIDevice> mDXGIDevice;
        wrl::ComPtr<IDXGIAdapter> mDXGIAdapter;
        wrl::ComPtr<IDXGIFactory> mDXGIFactory;
        wrl::ComPtr<ID3D11DeviceContext> mDeviceContext;
        wrl::ComPtr<ID3D11RasterizerState> mRasterState;

        D3D_FEATURE_LEVEL mFeatureLevel;

        std::unique_ptr<SwapChain> mSwapChain;
        std::unique_ptr<DeviceContextCommand> mDeviceContextCommand;

        // REMOVE ASAP
        Triangle* test;
        std::chrono::time_point<std::chrono::steady_clock> PrevTime = std::chrono::steady_clock::now();
        float totalTime = 0;
        unsigned int frameCount = 0;

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
