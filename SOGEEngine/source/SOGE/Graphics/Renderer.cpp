#include "sogepch.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/Graphics/SwapChain.hpp"
#include "SOGE/Graphics/DeviceContextCommand.hpp"

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
        //mSwapChain->Init(aSystemWindow);
        //mRenderContext->Init(context);
        //mVertexBuffer = new VertexBuffer();
        //mTestShader->Compile();
        //this->InitScene();

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
        mDeviceContextCommand->ClearWithColor(1.0f, 0.0f, 0.0f, 1.0f);
        mSwapChain->Present(false);
    }

}