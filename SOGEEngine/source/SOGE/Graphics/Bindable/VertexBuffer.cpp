#include "sogepch.hpp"
#include "SOGE/Graphics/Bindable/VertexBuffer.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/DebugSystem/Exception.hpp"

namespace soge
{
    VertexBuffer::VertexBuffer(std::vector<Vertex>& aVertices, UINT aOffset)
    {
        mStrides = sizeof(Vertex);
        mOffset = aOffset;
        
        this->mVertexTypeSize = sizeof(Vertex);
        this->mVertexCount = aVertices.size();

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

        vertexBufferDesc.Usage                  = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.BindFlags              = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags         = 0u;
        vertexBufferDesc.MiscFlags              = 0u;
        vertexBufferDesc.StructureByteStride    = 0u;
        vertexBufferDesc.ByteWidth              = mVertexTypeSize * mVertexCount;

        D3D11_SUBRESOURCE_DATA vertexData = {};
        ZeroMemory(&vertexData, sizeof(vertexData));

        vertexData.pSysMem = aVertices.data();
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, mVertexBuffer.GetAddressOf());
        DXThrowIfFailed(result, "Failed to create vertex buffer");
    }

    VertexBuffer::~VertexBuffer()
    {
        mVertexBuffer->Release();
    }

    void VertexBuffer::Bind() noexcept
    {
        auto context = Renderer::GetInstance()->mDeviceContext.Get();
        context->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &mStrides, &mOffset);
    }

    // Static constructor callers

    std::shared_ptr<VertexBuffer> VertexBuffer::CreateShared(std::vector<Vertex>& aVertices, UINT aOffset)
    {
        return std::make_shared<VertexBuffer>(aVertices, aOffset);
    }

    std::unique_ptr<VertexBuffer> VertexBuffer::CreateUnique(std::vector<Vertex>& aVertices, UINT aOffset)
    {
        return std::make_unique<VertexBuffer>(aVertices, aOffset);
    }

}