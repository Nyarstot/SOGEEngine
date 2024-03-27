#include "sogepch.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/Graphics/SwapChain.hpp"
#include "SOGE/Graphics/VertexBuffer.hpp"
#include "SOGE/Graphics/IndexBuffer.hpp"
#include "SOGE/Graphics/Shader.hpp"
#include "SOGE/Graphics/Primitives/Square.hpp"

namespace soge
{
    Renderer* Renderer::sInstance = nullptr;
    Renderer* Renderer::GetInstance() {
        if (sInstance == nullptr) {
            sInstance = new Renderer();
        }

        return sInstance;
    }

    void Renderer::Init(const std::unique_ptr<Window>& aSystemWindow)
    {
        D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

        D3D_DRIVER_TYPE driverTypes[] = {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE
        };

        UINT numDriverTypes = ARRAYSIZE(driverTypes);
        UINT numFeatureLevels = ARRAYSIZE(featureLevel);
        HRESULT result;

        for (UINT iDriver = 0; iDriver < numDriverTypes;) {
            result = D3D11CreateDevice(
                NULL,
                driverTypes[iDriver],
                NULL,
                NULL,
                featureLevel,
                numFeatureLevels,
                D3D11_SDK_VERSION,
                &mDevice,
                &mFeatureLevel,
                &mDeviceContext
            );

            if (SUCCEEDED(result)) {
                break;
            }

            ++iDriver;
        }

        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to create D3D11 Device");
        }

        mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&mDXGIDevice);
        mDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mDXGIAdapter);
        mDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mDXGIFactory);

        mSwapChain = SwapChain::Create(aSystemWindow);
        square = Square::Create({ -0.9f, 0.0f }, { 0.01f, 0.2f });
        square1 = Square::Create({ 0.9f, 0.0f }, { 0.01f, 0.2f });
        this->CreateRasterizer();
        this->InitScene();
    }

    void Renderer::CreateRasterizer()
    {
        CD3D11_RASTERIZER_DESC rastDesc = {};
        rastDesc.CullMode = D3D11_CULL_NONE;
        rastDesc.FillMode = D3D11_FILL_SOLID;

        HRESULT res = mDevice->CreateRasterizerState(&rastDesc, mRasterizerState.GetAddressOf());
        if (FAILED(res)) {
            SOGE_ERROR_LOG("FAILED TO CREATE RAST STATE");
        }
        mDeviceContext->RSSetState(mRasterizerState.Get());
    }

    void Renderer::InitScene()
    {
        Vertex points[] = {
            DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),      DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
            DirectX::XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f),    DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
            DirectX::XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f),     DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
            DirectX::XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f),     DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
        };

        int indeces[] = { 0,1,2, 1,0,3 };

        mVertexBuffer = VertexBuffer::Create(points);
        mIndexBuffer = IndexBuffer::Create(indeces);

        SOGE_SHADER_DESC vShaderDesc;
        vShaderDesc.name = L"TestVerexShader";
        vShaderDesc.path = L"shaders/MyVeryFirstShader.hlsl";
        vShaderDesc.entryPoint = "VSMain";
        vShaderDesc.target = "vs_5_0";

        SOGE_SHADER_DESC pShaderDesc;
        pShaderDesc.name = L"TestPixelShader";
        pShaderDesc.path = L"shaders/MyVeryFirstShader.hlsl";
        pShaderDesc.entryPoint = "PSMain";
        pShaderDesc.target = "ps_5_0";

        mTestPShader = std::make_unique<PixelShader>(pShaderDesc);
        mTestPShader->CompileAndCreate();

        mTestVShader = std::make_unique<VertexShader>(vShaderDesc);
        mTestVShader->CompileAndCreate();
    }

    void Renderer::Release()
    {

    }

    void Renderer::Render()
    {
        mDeviceContext->ClearState();
        mDeviceContext->RSSetState(mRasterizerState.Get());

        D3D11_VIEWPORT viewport = {};
        viewport.Width = static_cast<float>(1280);
        viewport.Height = static_cast<float>(720);
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.MinDepth = 0;
        viewport.MaxDepth = 1.0f;

        mDeviceContext->RSSetViewports(1, &viewport);

        mDeviceContext->OMSetRenderTargets(1, mSwapChain->GetAddresOfRenderTargetView(), nullptr);

        float color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        mDeviceContext->ClearRenderTargetView(mSwapChain->GetRenderTargetView(), color);
        square->Draw(mDeviceContext.Get());
        square1->Draw(mDeviceContext.Get());

        mSwapChain->Present(1);
    }

}