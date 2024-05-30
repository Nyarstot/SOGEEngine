#include "sogepch.hpp"
#include "SOGE/Graphics/ZBuffer.hpp"
#include "SOGE/DebugSystem/Exception.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/Graphics/SwapChain.hpp"


namespace soge
{
    ZBuffer::ZBuffer(const Point2D& aSize)
    {
        mStencilSize = aSize;

        // Stencil buffer description

        D3D11_TEXTURE2D_DESC stencilBufferDesc;
        ZeroMemory(&stencilBufferDesc, sizeof(stencilBufferDesc));

        stencilBufferDesc.Width              = aSize.x; // width and height should match those of SwapChain
        stencilBufferDesc.Height             = aSize.y;
        stencilBufferDesc.MipLevels          = 1u;
        stencilBufferDesc.ArraySize          = 1u;
        stencilBufferDesc.Format             = DXGI_FORMAT_D32_FLOAT; // can also be DXGI_FORMAT_D24_UNORM_S8_UINT
        stencilBufferDesc.Usage              = D3D11_USAGE_DEFAULT;
        stencilBufferDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
        stencilBufferDesc.CPUAccessFlags     = 0u;
        stencilBufferDesc.MiscFlags          = 0u;
        stencilBufferDesc.SampleDesc.Count   = 1u; // Number of anit aliasing samples
        stencilBufferDesc.SampleDesc.Quality = 0u;

        // Depth stencil description

        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

        depthStencilDesc.DepthEnable = TRUE;
        depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

        // Depth stencil view description

        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
        ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

        depthStencilViewDesc.Format             = stencilBufferDesc.Format;
        depthStencilViewDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Texture2D.MipSlice = 0u;

        // Get objects from Renderer

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();
        SwapChain* swapChain = Renderer::GetInstance()->mSwapChain.get();

        // Bind data

        HRESULT result = device->CreateTexture2D(&stencilBufferDesc, nullptr, mStencilBuffer.GetAddressOf());
        DXThrowIfFailed(result, "Failed to create stencil buffer");

        result = device->CreateDepthStencilView(mStencilBuffer.Get(), &depthStencilViewDesc, mDepthStencilView.GetAddressOf());
        DXThrowIfFailed(result, "Failed to create depth stencil view");

        result = device->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.GetAddressOf());
        DXThrowIfFailed(result, "Failed to create depth stencil state");

        //context->OMSetRenderTargets(1u, swapChain->GetAddresOfRenderTargetView(), mDepthStencilView.Get());
        context->OMSetDepthStencilState(mDepthStencilState.Get(), 1u);

    }

    ZBuffer::~ZBuffer()
    {
        mDepthStencilView.Reset();
        mStencilBuffer.Reset();
    }

    // Static constructor callers

    std::shared_ptr<ZBuffer> ZBuffer::CreateShared(const Point2D& aSize)
    {
        return std::make_shared<ZBuffer>(aSize);
    }

    std::unique_ptr<ZBuffer> ZBuffer::CreateUnique(const Point2D& aSize)
    {
        return std::make_unique<ZBuffer>(aSize);
    }
}