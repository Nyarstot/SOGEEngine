#include "sogepch.hpp"
#include "SOGE/Graphics/ConstantBuffer.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    HRESULT ConstantBuffer::Init(void* aBuffer, float aAspectRatio)
    {
        const CBTransform cbt = {
            {
                dx::XMMatrixTranspose(
                    dx::XMMatrixRotationZ(0.0f) *
                    dx::XMMatrixScaling(aAspectRatio, 1.0f, 1.0f)
                )
            }
        };

        D3D11_BUFFER_DESC constantBufferDesc = {};
        ZeroMemory(&constantBufferDesc, sizeof(constantBufferDesc));

        constantBufferDesc.BindFlags            = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.Usage                = D3D11_USAGE_DYNAMIC;
        constantBufferDesc.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
        constantBufferDesc.MiscFlags            = 0u;
        constantBufferDesc.StructureByteStride  = 0u;
        constantBufferDesc.ByteWidth            = sizeof(cbt);

        D3D11_SUBRESOURCE_DATA constantBufferSubres = {};
        ZeroMemory(&constantBufferSubres, sizeof(constantBufferSubres));

        constantBufferSubres.pSysMem            = &cbt;
        constantBufferSubres.SysMemPitch        = 0;
        constantBufferSubres.SysMemSlicePitch   = 0;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        HRESULT result = device->CreateBuffer(&constantBufferDesc, &constantBufferSubres, mConstantBuffer.GetAddressOf());

        return result;
    }

    ConstantBuffer::ConstantBuffer(void* aBuffer, float aAspectRatio)
    {
        this->mBufferData = aBuffer;
        this->mAspectRatio = aAspectRatio;

        HRESULT result = Init(aBuffer, aAspectRatio);
        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to initialize constant buffer...");
        }
    }

    ConstantBuffer::ConstantBuffer(SOGE_CONSTANT_BUFFER_DESC aDescriptor)
    {
        this->mBufferData = aDescriptor.bufferData;
        this->mAspectRatio = aDescriptor.aspectRatio;

        HRESULT result = Init(aDescriptor.bufferData, aDescriptor.aspectRatio);
        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to initialize constant buffer...");
        }
    }

    ConstantBuffer::~ConstantBuffer()
    {
    }

    void ConstantBuffer::Update(float aData)
    {
        const CBTransform cbt = {
            {
                dx::XMMatrixTranspose(
                    dx::XMMatrixRotationZ(aData) *
                    dx::XMMatrixScaling(mAspectRatio, 1.0f, 1.0f)
                )
            }
        };

        D3D11_MAPPED_SUBRESOURCE mappedSbr = {};
        ZeroMemory(&mappedSbr, sizeof(mappedSbr));

        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();
        HRESULT res = context->Map(mConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSbr);
        CopyMemory(mappedSbr.pData, &cbt, sizeof(cbt));
        context->Unmap(mConstantBuffer.Get(), 0);
        context->VSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf());
    }

    std::unique_ptr<ConstantBuffer> ConstantBuffer::Create(void* aBuffer, float aAspectRatio)
    {
        return std::make_unique<ConstantBuffer>(aBuffer, aAspectRatio);
    }

    std::unique_ptr<ConstantBuffer> ConstantBuffer::Create(SOGE_CONSTANT_BUFFER_DESC aDescriptor)
    {
        return std::make_unique<ConstantBuffer>(aDescriptor);
    }
}