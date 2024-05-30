#include "sogepch.hpp"
#include "SOGE/Graphics/Bindable/VertexBuffer.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/DebugSystem/Exception.hpp"

namespace soge
{
    void VertexBuffer::InitBufferData(Vertex* aVertices)
    {
        this->mVertexTypeSize = sizeof(Vertex);
        this->mVertexCount = 8;

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags = 0u;
        vertexBufferDesc.MiscFlags = 0u;
        vertexBufferDesc.StructureByteStride = 0u;
        vertexBufferDesc.ByteWidth = mVertexTypeSize * mVertexCount;

        D3D11_SUBRESOURCE_DATA vertexData = {};
        ZeroMemory(&vertexData, sizeof(vertexData));

        vertexData.pSysMem = aVertices;
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, mVertexBuffer.GetAddressOf());
        DXThrowIfFailed(result, "Failed to create vertex buffer");
    }

    VertexBuffer::VertexBuffer(Vertex* aVertices)
    {
        mStrides = std::make_unique<UINT>(32);
        mOffset = std::make_unique<UINT>(0);
        this->InitBufferData(aVertices);
    }

    VertexBuffer::VertexBuffer(Vertex* aVertices, UINT aStrides, UINT aOffset)
    {
        mStrides = std::make_unique<UINT>(aStrides);
        mOffset = std::make_unique<UINT>(aOffset);
        this->InitBufferData(aVertices);
    }

    VertexBuffer::~VertexBuffer()
    {
        mVertexBuffer->Release();
    }

    void VertexBuffer::SetStrides(UINT aStrides)
    {
        mStrides.reset(new UINT(aStrides));
    }

    void VertexBuffer::SetOffset(UINT aOffset)
    {
        mOffset.reset(new UINT(aOffset));
    }

    void VertexBuffer::Bind() noexcept
    {
        auto context = Renderer::GetInstance()->mDeviceContext.Get();
        context->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), mStrides.get(), mOffset.get());
    }

    // Static constructor callers

    std::shared_ptr<VertexBuffer> VertexBuffer::CreateShared(Vertex* aVertices)
    {
        return std::make_shared<VertexBuffer>(aVertices);
    }

    std::unique_ptr<VertexBuffer> VertexBuffer::CreateUnique(Vertex* aVertices)
    {
        return std::make_unique<VertexBuffer>(aVertices);
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::CreateShared(Vertex* aVertices, UINT aStrides, UINT aOffset)
    {
        return std::make_shared<VertexBuffer>(aVertices, aStrides, aOffset);
    }

    std::unique_ptr<VertexBuffer> VertexBuffer::CreateUnique(Vertex* aVertices, UINT aStrides, UINT aOffset)
    {
        return std::make_unique<VertexBuffer>(aVertices, aStrides, aOffset);
    }

}