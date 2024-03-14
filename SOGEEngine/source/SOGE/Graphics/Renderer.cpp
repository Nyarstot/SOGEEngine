#include "sogepch.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/Graphics/SwapChain.hpp"
#include "SOGE/Graphics/DeviceContextCommand.hpp"
#include "SOGE/Graphics/VertexBuffer.hpp"
#include "SOGE/Graphics/IndexBuffer.hpp"
#include "SOGE/Graphics/Primitives/Triangle.hpp"
#include "SOGE/Graphics/Shader.hpp"

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
        D3D_DRIVER_TYPE driverTypes[] = {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE
        };

        D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_11_1
        };

        UINT numDriverTypes = ARRAYSIZE(driverTypes);
        UINT numFeatureLevels = ARRAYSIZE(featureLevels);
        HRESULT result;

        for (UINT iDriver = 0; iDriver < numDriverTypes;) {
            result = D3D11CreateDevice(
                NULL,
                driverTypes[iDriver],
                NULL,
                NULL,
                featureLevels,
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

        ID3D11DeviceContext* context = mDeviceContext.Get();

        mSwapChain = SwapChain::Create(aSystemWindow);
        mDeviceContextCommand = DeviceContextCommand::Create(context);

        CD3D11_RASTERIZER_DESC rastDesc = {};
        ZeroMemory(&rastDesc, sizeof(rastDesc));

        rastDesc.CullMode = D3D11_CULL_NONE;
        rastDesc.FillMode = D3D11_FILL_SOLID;
        mDevice->CreateRasterizerState(&rastDesc, &mRasterState);
        context->RSSetState(mRasterState.Get());

        test = new Triangle();
    }

    void Renderer::Release()
    {
        mDevice->Release();
        mDXGIDevice->Release();
        mDXGIAdapter->Release();
        mDXGIFactory->Release();
        mDeviceContext->Release();

        mSwapChain->Release();
    }

    void Renderer::Render()
    {
        mDeviceContext->ClearState();
        mDeviceContext->RSSetState(mRasterState.Get());

        D3D11_VIEWPORT mMainViewport = {};
        ZeroMemory(&mMainViewport, sizeof(mMainViewport));
        mMainViewport.Width = 1280;
        mMainViewport.Height = 720;
        mMainViewport.MinDepth = 0;
        mMainViewport.MaxDepth = 1;
        mMainViewport.TopLeftX = 0;
        mMainViewport.TopLeftY = 0;
        mDeviceContext->RSSetViewports(1u, &mMainViewport);
        test->OnUpdate();

        auto	curTime = std::chrono::steady_clock::now();
        float	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - PrevTime).count() / 1000000.0f;
        PrevTime = curTime;

        totalTime += deltaTime;
        frameCount++;

        if (totalTime > 1.0f) {
            float fps = frameCount / totalTime;

            totalTime -= 1.0f;

            WCHAR text[256];
            SOGE_WARN_LOG("FPS: {0}: ", fps);

            frameCount = 0;
        }

        mDeviceContext->OMSetRenderTargets(1, mSwapChain->GetAddresOfRenderTargetView(), NULL);
        mDeviceContextCommand->ClearWithColor(totalTime, 0.0f, 0.0f, 1.0f);
        mSwapChain->Get()->Present(1, 0);
    }

}