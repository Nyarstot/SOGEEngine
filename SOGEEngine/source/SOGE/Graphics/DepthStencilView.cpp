#include "sogepch.hpp"
#include "SOGE/Graphics/DepthStencilView.hpp"
#include "SOGE/DebugSystem/Exception.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/Graphics/SwapChain.hpp"


namespace soge
{
    DepthStencilView::DepthStencilView(const Point2D& aSize)
    {
        mStencilSize = aSize;

        D3D11_TEXTURE2D_DESC stencilBufferDesc;
        ZeroMemory(&stencilBufferDesc, sizeof(stencilBufferDesc));

        stencilBufferDesc.Width              = aSize.x;
        stencilBufferDesc.Height             = aSize.y;
        stencilBufferDesc.MipLevels          = 1;
        stencilBufferDesc.ArraySize          = 1;
        stencilBufferDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
        stencilBufferDesc.Usage              = D3D11_USAGE_DEFAULT;
        stencilBufferDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
        stencilBufferDesc.CPUAccessFlags     = 0;
        stencilBufferDesc.MiscFlags          = 0;
        stencilBufferDesc.SampleDesc.Count   = 1;
        stencilBufferDesc.SampleDesc.Quality = 0;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();
        SwapChain* swapChain = Renderer::GetInstance()->mSwapChain.get();

        //D3D11_DEPTH_STENCIL_VIEW_DESC stencilViewDesc;
        //ZeroMemory(&stencilViewDesc, sizeof(stencilViewDesc));
        //stencilViewDesc.Format = stencilBufferDesc.Format;

        HRESULT result = device->CreateTexture2D(&stencilBufferDesc, nullptr, mStencilBuffer.GetAddressOf());
        DXThrowIfFailed(result, "Failed to create stencil buffer");

        result = device->CreateDepthStencilView(mStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf());
        DXThrowIfFailed(result, "Failed to create depth stencil view");

        context->OMSetRenderTargets(1, swapChain->GetAddresOfRenderTargetView(), mDepthStencilView.Get());

    }

    DepthStencilView::~DepthStencilView()
    {
        mDepthStencilView.Reset();
        mStencilBuffer.Reset();
    }

    // Static constructor callers

    std::shared_ptr<DepthStencilView> DepthStencilView::CreateShared(const Point2D& aSize)
    {
        return std::make_shared<DepthStencilView>(aSize);
    }

    std::unique_ptr<DepthStencilView> DepthStencilView::CreateUnique(const Point2D& aSize)
    {
        return std::make_unique<DepthStencilView>(aSize);
    }
}