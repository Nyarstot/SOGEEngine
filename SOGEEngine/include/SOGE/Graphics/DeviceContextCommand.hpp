#ifndef SOGE_DEVICE_CONTEXT_COMMAND_HPP
#define SOGE_DEVICE_CONTEXT_COMMAND_HPP

#include <d3d.h>
#include <d3d11.h>

#include "SOGE/Engine/EngineSetup.hpp"

namespace soge
{
    class DeviceContextCommand
    {
    private:
        wrl::ComPtr<ID3D11DeviceContext> mDeviceContext;

    protected:
        HRESULT Init(ID3D11DeviceContext* aDeviceContext);

    public:
        DeviceContextCommand(ID3D11DeviceContext* aDeviceContext);
        ~DeviceContextCommand();

        void ClearWithColor(float r, float g, float b, float a);

    public:
        static std::unique_ptr<DeviceContextCommand> Create(ID3D11DeviceContext* aDeviceContext);

    };
}

#endif // !SOGE_DEVICE_CONTEXT_COMMAND_HPP
