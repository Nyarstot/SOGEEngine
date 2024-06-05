#ifndef SOGE_CONSTANT_BUFFER
#define SOGE_CONSTANT_BUFFER

#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/Interface/GraphicsInterfaces.hpp"

#include <memory>
#include <Windows.h>
#include <d3d11.h>
#include <SimpleMath.h>

namespace soge
{
    struct CBTransform
    {
        dx::XMMATRIX transform;
        //dxsmath::Matrix transform;

    };

    template<typename _Cd>
    class ConstantBuffer : public IBindable
    {
    private:
        float mAspectRatio  = 0.0f;
        _Cd mConstantsData;

    protected:
        wrl::ComPtr<ID3D11Buffer> mConstantBuffer;
        wrl::ComPtr<ID3D11DeviceContext> mContext;
        wrl::ComPtr<ID3D11Device> mDevice;

    protected:

        inline HRESULT Init(ID3D11Device* aDevice, ID3D11DeviceContext* aContext, const _Cd& aConstData = {}) {
            this->mDevice     = aDevice;
            this->mContext    = aContext;
            this->mConstantsData = aConstData;

            D3D11_BUFFER_DESC constantBufferDesc = {};
            ZeroMemory(&constantBufferDesc, sizeof(constantBufferDesc));

            constantBufferDesc.BindFlags            = D3D11_BIND_CONSTANT_BUFFER;
            constantBufferDesc.Usage                = D3D11_USAGE_DYNAMIC;
            constantBufferDesc.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
            constantBufferDesc.MiscFlags            = 0u;
            constantBufferDesc.StructureByteStride  = 0u;
            constantBufferDesc.ByteWidth            = static_cast<UINT>(sizeof(_Cd) + (16 - (sizeof(_Cd) % 16)));

            D3D11_SUBRESOURCE_DATA constantBufferSubres = {};
            ZeroMemory(&constantBufferSubres, sizeof(constantBufferSubres));
            constantBufferSubres.pSysMem = &mConstantsData;

            HRESULT result = mDevice->CreateBuffer(&constantBufferDesc, &constantBufferSubres, mConstantBuffer.GetAddressOf());

            return result;
        }

        ID3D11DeviceContext* GetDeviceContext() const { return mContext.Get(); }

    public:
        inline ConstantBuffer(ID3D11Device* aDevice, ID3D11DeviceContext* aContext, const _Cd& aConstData = {}) {
            HRESULT result = Init(aDevice, aContext, aConstData);
            if (FAILED(result)) {
                SOGE_ERROR_LOG("Failed to initialize constant buffer...");
            }
        }

        inline ~ConstantBuffer() {
            mConstantBuffer->Release();
            mDevice->Release();
            mContext->Release();
        }

        inline HRESULT UpdateBufferData() {
            D3D11_MAPPED_SUBRESOURCE mappedSbr = {};
            ZeroMemory(&mappedSbr, sizeof(mappedSbr));

            HRESULT result = mContext->Map(mConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedSbr);
            if (FAILED(result)) {
                SOGE_ERROR_LOG("Failed to map data to constant buffer...");
            }

            CopyMemory(mappedSbr.pData, &mConstantsData, sizeof(_Cd));
            mContext->Unmap(mConstantBuffer.Get(), 0u);

            return result;
        }

        void Bind() noexcept override
        {
            mContext->VSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf());
        }

        inline ID3D11Buffer* Get() const { return mConstantBuffer.Get(); }
        inline ID3D11Buffer* const* GetAddressOf() { return mConstantBuffer.GetAddressOf(); }
        inline void SetConstantData(const _Cd& aConstantData) { mConstantsData = aConstantData; }

    public:
        inline static std::unique_ptr<ConstantBuffer> Create(ID3D11Device* aDevice, ID3D11DeviceContext* aContext, const _Cd& aConstData = {}) {
            return std::make_unique<ConstantBuffer>(aDevice, aContext, aConstData);
        }

    };

    template<typename _Cd>
    class VertexConstantBuffer final : public ConstantBuffer<_Cd>
    {
        using ConstantBuffer<_Cd>::mConstantBuffer;
        using ConstantBuffer<_Cd>::mContext;

    public:
        using ConstantBuffer<_Cd>::ConstantBuffer;
        void Bind() noexcept override
        {
            mContext->VSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf());
        }

    };

    template<typename _Cd>
    class PixelConstantBuffer final : public ConstantBuffer<_Cd>
    {
        using ConstantBuffer<_Cd>::mConstantBuffer;
        using ConstantBuffer<_Cd>::mContext;

    public:
        using ConstantBuffer<_Cd>::ConstantBuffer;
        void Bind() noexcept override
        {
            mContext->PSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf());
        }

    };

}

#endif // !SOGE_CONSTANT_BUFFER
