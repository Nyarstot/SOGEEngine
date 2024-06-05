#include "sogepch.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/Graphics/SwapChain.hpp"
#include "SOGE/Graphics/Bindable/VertexBuffer.hpp"
#include "SOGE/Graphics/Bindable/IndexBuffer.hpp"
#include "SOGE/Graphics/Bindable/Shader.hpp"
#include "SOGE/Graphics/SpriteFont.hpp"
#include "SOGE/Graphics/ZBuffer.hpp"

namespace soge
{
    Renderer* Renderer::sInstance = nullptr;
    Renderer* Renderer::GetInstance() {
        if (sInstance == nullptr) {
            sInstance = new Renderer();
        }

        return sInstance;
    }

    void Renderer::Init(const std::unique_ptr<Window>& aWindow)
    {
        SOGE_INFO_LOG("Initialize renderer...");
        mAppWindow = aWindow.get();
        D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

        D3D_DRIVER_TYPE driverTypes[] = {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE
        };

        UINT numDriverTypes = ARRAYSIZE(driverTypes);
        SOGE_INFO_LOG("Number of graphics drivers {0}", numDriverTypes);
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
        mDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mDXGIAdapter3);
        mDXGIAdapter3->GetParent(__uuidof(IDXGIFactory), (void**)&mDXGIFactory);
        this->PrintGPUInfo(mDXGIAdapter.Get());


        mSwapChain = SwapChain::CreateUnique(mAppWindow);
        mZBuffer = ZBuffer::CreateUnique({
                static_cast<float>(mAppWindow->GetWidth()),
                static_cast<float>(mAppWindow->GetHeight())
            });
        this->CreateRasterizer();
    }

    void Renderer::SetupViewport()
    {
        D3D11_VIEWPORT viewport = {};
        viewport.Width = static_cast<float>(mAppWindow->GetWidth());
        viewport.Height = static_cast<float>(mAppWindow->GetHeight());
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.MinDepth = 0;
        viewport.MaxDepth = 1.0f;

        mDeviceContext->RSSetViewports(1, &viewport);
    }

    void Renderer::CreateRasterizer()
    {
        CD3D11_RASTERIZER_DESC rastDesc = {};
        rastDesc.CullMode = D3D11_CULL_NONE;
        rastDesc.FillMode = D3D11_FILL_SOLID;

        HRESULT res = mDevice->CreateRasterizerState(&rastDesc, mRasterizerState.GetAddressOf());
        if (FAILED(res)) {
            SOGE_ERROR_LOG("Failed to create rasterizer state...");
        }
        mDeviceContext->RSSetState(mRasterizerState.Get());
    }

    void Renderer::PrintGPUInfo(IDXGIAdapter* aDXGIAdapter)
    {
        #ifdef SOGE_DEBUG

        DXGI_ADAPTER_DESC adapterDesc;
        ZeroMemory(&adapterDesc, sizeof(adapterDesc));
        aDXGIAdapter->GetDesc(&adapterDesc);

        std::wstring vendorName = L"Unknown";
        if (adapterDesc.VendorId == 0x10DE) {
            vendorName = L"NVIDIA";
        }
        else if (adapterDesc.VendorId == 0x1002 || adapterDesc.VendorId == 0x1022) {
            vendorName = L"AMD";
        }
        else if (adapterDesc.VendorId == 0x163 || adapterDesc.VendorId == 0x8086 || adapterDesc.VendorId == 0x8087) {
            vendorName = L"Intel";
        }

        DXGI_QUERY_VIDEO_MEMORY_INFO queryVideoMemoryInfo;
        ZeroMemory(&queryVideoMemoryInfo, sizeof(queryVideoMemoryInfo));
        HRESULT result = mDXGIAdapter3->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &queryVideoMemoryInfo);

        SOGE_INFO_LOG("");
        SOGE_INFO_LOG("============== GPU INFO ==============");
        SOGE_INFO_LOG(L"\tDevice ID: {0}", adapterDesc.DeviceId);
        SOGE_INFO_LOG(L"\tGPU device model: {0}", adapterDesc.Description);
        SOGE_INFO_LOG(L"\tGPU device vendor: {0}", vendorName.c_str());
        SOGE_INFO_LOG(L"\tGPU budget: {0} bytes", queryVideoMemoryInfo.Budget);
        SOGE_INFO_LOG(L"\tGPU memory available for reservation: {0} bytes", queryVideoMemoryInfo.AvailableForReservation);
        SOGE_INFO_LOG(L"\tGPU memory currently reserved: {0} bytes", queryVideoMemoryInfo.CurrentReservation);
        SOGE_INFO_LOG(L"\tGPU memory currently used: {0} bytes", queryVideoMemoryInfo.CurrentUsage);
        SOGE_INFO_LOG(L"\tDedicated video memory: {0} bytes", adapterDesc.DedicatedVideoMemory);
        SOGE_INFO_LOG("======================================");

        #endif // DEBUG

        return;
    }

    void Renderer::Release()
    {

    }

    void Renderer::Render(LayerStack& aRenderLayers, float aDeltaTime)
    {

        mDeviceContext->ClearState();
        mDeviceContext->RSSetState(mRasterizerState.Get());
        SetupViewport();


        float color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        mDeviceContext->ClearRenderTargetView(mSwapChain->GetRenderTargetView(), color);
        mDeviceContext->OMSetRenderTargets(1u, mSwapChain->GetAddresOfRenderTargetView(), mZBuffer->GetDepthStencilView());

        mDeviceContext->ClearDepthStencilView(
            mZBuffer->GetDepthStencilView(),
            D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u
        );

        for (auto layer : aRenderLayers) {
            layer->OnUpdate(aDeltaTime);
        }
        mSwapChain->Present(1);
    }

    void Renderer::DrawIndexed(UINT aIndicesCount) noexcept(!SOGE_DEBUG)
    {
        mDeviceContext->DrawIndexed(aIndicesCount, 0u, 0u);
    }

}