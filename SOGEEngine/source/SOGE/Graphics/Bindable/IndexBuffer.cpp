#include "sogepch.hpp"
#include "SOGE/Graphics/Bindable/IndexBuffer.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    HRESULT IndexBuffer::Init(int* indeces)
    {
        D3D11_BUFFER_DESC indexBufDesc = {};
        ZeroMemory(&indexBufDesc, sizeof(indexBufDesc));

        indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
        indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        indexBufDesc.CPUAccessFlags = 0;
        indexBufDesc.MiscFlags = 0;
        indexBufDesc.StructureByteStride = 0;
        indexBufDesc.ByteWidth = sizeof(int) * 6;

        D3D11_SUBRESOURCE_DATA indexData = {};
        ZeroMemory(&indexData, sizeof(indexData));

        indexData.pSysMem = indeces;
        indexData.SysMemPitch = 0;
        indexData.SysMemSlicePitch = 0;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        HRESULT result = device->CreateBuffer(&indexBufDesc, &indexData, &mIndexBuffer);

        return result;
    }

    IndexBuffer::IndexBuffer(int* indeces)
    {
        HRESULT result = this->Init(indeces);
        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to create index buffer");
        }
    }

    IndexBuffer::~IndexBuffer()
    {

    }

    void IndexBuffer::Bind() noexcept
    {
        auto context = Renderer::GetInstance()->mDeviceContext.Get();
        context->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    }

    std::unique_ptr<IndexBuffer> IndexBuffer::Create(int* indeces)
    {
        return std::make_unique<IndexBuffer>(indeces);
    }
}