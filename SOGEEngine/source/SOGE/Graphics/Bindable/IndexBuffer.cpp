#include "sogepch.hpp"
#include "SOGE/Graphics/Bindable/IndexBuffer.hpp"
#include "SOGE/DebugSystem/Exception.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    IndexBuffer::IndexBuffer(std::vector<UINT> aIndices)
    {
        mIndicesCount = static_cast<UINT>(aIndices.size());

        D3D11_BUFFER_DESC indexBufDesc = {};
        ZeroMemory(&indexBufDesc, sizeof(indexBufDesc));

        indexBufDesc.Usage                  = D3D11_USAGE_DEFAULT;
        indexBufDesc.BindFlags              = D3D11_BIND_INDEX_BUFFER;
        indexBufDesc.CPUAccessFlags         = 0;
        indexBufDesc.MiscFlags              = 0;
        indexBufDesc.StructureByteStride    = 0;
        indexBufDesc.ByteWidth              = sizeof(UINT) * mIndicesCount;

        D3D11_SUBRESOURCE_DATA indexData = {};
        ZeroMemory(&indexData, sizeof(indexData));

        indexData.pSysMem           = aIndices.data();
        indexData.SysMemPitch       = 0;
        indexData.SysMemSlicePitch  = 0;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        HRESULT result = device->CreateBuffer(&indexBufDesc, &indexData, &mIndexBuffer);
        DXThrowIfFailed(result, "Failed to create index buffer");
    }

    IndexBuffer::IndexBuffer(const IndexBuffer& aIndexBuffer)
    {
        mIndexBuffer = aIndexBuffer.mIndexBuffer;
        mIndicesCount = aIndexBuffer.mIndicesCount;
    }

    IndexBuffer::~IndexBuffer()
    {
        mIndexBuffer->Release();
    }

    void IndexBuffer::Bind() noexcept
    {
        auto context = Renderer::GetInstance()->mDeviceContext.Get();
        context->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    }

    // Static constructor callers

    std::shared_ptr<IndexBuffer> IndexBuffer::CreateShared(std::vector<UINT> aIndices)
    {
        return std::make_shared<IndexBuffer>(aIndices);
    }

    std::unique_ptr<IndexBuffer> IndexBuffer::CreateUnique(std::vector<UINT> aIndices)
    {
        return std::make_unique<IndexBuffer>(aIndices);
    }

}