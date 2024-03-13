#include "sogepch.hpp"
#include "SOGE/Graphics/DeviceContextCommand.hpp"
#include "SOGE/Graphics/SwapChain.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    HRESULT DeviceContextCommand::Init(ID3D11DeviceContext* aDeviceContext)
    {
        mDeviceContext = aDeviceContext;
        if (mDeviceContext == nullptr) {
            return E_FAIL;
        }

        return S_OK;
    }

    DeviceContextCommand::DeviceContextCommand(ID3D11DeviceContext* aDeviceContext)
    {
        HRESULT result = this->Init(aDeviceContext);
        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to handle D3D11DeviceContext. Pointer was nullptr");
        }
    }

    DeviceContextCommand::~DeviceContextCommand()
    {
        mDeviceContext->Release();
    }

    void DeviceContextCommand::ClearWithColor(float r, float g, float b, float a)
    {
        SwapChain* swapChain = Renderer::GetInstance()->mSwapChain.get();

        FLOAT clearColor[] = { r, g, b, a };
        mDeviceContext->ClearRenderTargetView(swapChain->GetRenderTargetView(), clearColor);
        mDeviceContext->OMSetRenderTargets(1, swapChain->GetAddresOfRenderTargetView(), NULL);
    }

    std::unique_ptr<DeviceContextCommand> DeviceContextCommand::Create(ID3D11DeviceContext* aDeviceContext)
    {
        return std::make_unique<DeviceContextCommand>(aDeviceContext);
    }

}