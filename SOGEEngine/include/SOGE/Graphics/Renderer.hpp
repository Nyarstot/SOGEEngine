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

    class Renderer final
    {
        friend class SwapChain;
        friend class VertexBuffer;
        friend class IndexBuffer;
        friend class VertexShader;
        friend class PixelShader;
        friend class GeneralizedShader;

    private:
        wrl::ComPtr<ID3D11Device> mDevice;
        wrl::ComPtr<IDXGIDevice> mDXGIDevice;
        wrl::ComPtr<IDXGIAdapter> mDXGIAdapter;
        wrl::ComPtr<IDXGIFactory> mDXGIFactory;
        wrl::ComPtr<ID3D11DeviceContext> mDeviceContext;
        wrl::ComPtr<ID3D11RasterizerState> mRasterState;

        D3D_FEATURE_LEVEL mFeatureLevel;

        // TEST

        std::unique_ptr<SwapChain> mSwapChain;
        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<IndexBuffer> mIndexBuffer;
        std::unique_ptr<VertexShader> mTestVShader;
        std::unique_ptr<PixelShader> mTestPShader;
        wrl::ComPtr<ID3D11RasterizerState> mRasterizerState;

        std::chrono::time_point<std::chrono::steady_clock> PrevTime = std::chrono::steady_clock::now();
        float totalTime = 0;
        unsigned int frameCount = 0;


        MSG msg = {};

    protected:
        Renderer() = default;
        static Renderer* sInstance;

        void SetupRasterizer();
        void CreateVertexShader();
        void CreatePixelShader();
        void CreateRasterizer();
        void InitScene();

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
