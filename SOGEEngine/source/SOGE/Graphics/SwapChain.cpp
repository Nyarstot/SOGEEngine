#include "sogepch.hpp"
#include "SOGE/Graphics/SwapChain.hpp"
#include "SOGE/DebugSystem/Exception.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    SwapChain::SwapChain(Window* aSystemWindow)
    {
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

        swapChainDesc.BufferCount = 2;
        swapChainDesc.BufferDesc.Width = aSystemWindow->GetWidth();
        swapChainDesc.BufferDesc.Height = aSystemWindow->GetHeight();
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 1;
        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        //swapChainDesc.OutputWindow = (HWND)686;
        swapChainDesc.OutputWindow = (HWND)aSystemWindow->GetHandle();
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Windowed = TRUE;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();

        HRESULT hr = Renderer::GetInstance()->mDXGIFactory->CreateSwapChain(device, &swapChainDesc, &mSwapChain);
        DXThrowIfFailed(hr, "Failed to create SwapChain");


        ID3D11Texture2D* backTexture = nullptr;
        hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTexture);
        DXThrowIfFailed(hr, "Failed to create back texture");

        hr = device->CreateRenderTargetView(backTexture, nullptr, &mRenderTargetView);
        DXThrowIfFailed(hr, "Failed to create render target view");
    }

    SwapChain::~SwapChain()
    {
        this->Release();
    }

    HRESULT SwapChain::Present(bool aVSync)
    {
        return mSwapChain->Present(aVSync, NULL);
    }

    void SwapChain::Release()
    {
        mSwapChain->Release();
        mRenderTargetView->Release();
    }

    std::shared_ptr<SwapChain> SwapChain::CreateShared(Window* aSystemWindow)
    {
        return std::make_shared<SwapChain>(aSystemWindow);
    }

    std::unique_ptr<SwapChain> SwapChain::CreateUnique(Window* aSystemWindow)
    {
        return std::make_unique<SwapChain>(aSystemWindow);
    }
}
