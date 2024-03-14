#include "sogepch.hpp"
#include "SOGE/Graphics/VertexBuffer.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    HRESULT VertexBuffer::Init(Vertex* aVertices)
    {
        this->mVertexTypeSize = sizeof(Vertex);
        this->mVertexCount = 8;

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags = 0;
        vertexBufferDesc.MiscFlags = 0;
        vertexBufferDesc.StructureByteStride = 0;
        vertexBufferDesc.ByteWidth = mVertexTypeSize * mVertexCount;

        D3D11_SUBRESOURCE_DATA vertexData = {};
        ZeroMemory(&vertexData, sizeof(vertexData));

        vertexData.pSysMem = aVertices;
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        HRESULT result = device->CreateBuffer(&vertexBufferDesc, &vertexData, mVertexBuffer.GetAddressOf());

        return result;
    }

    VertexBuffer::VertexBuffer(Vertex* aVertices)
    {
        HRESULT result = Init(aVertices);
        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to create D3D11 vertex buffer");
        }
    }

    VertexBuffer::~VertexBuffer()
    {
        mVertexBuffer->Release();
    }

    std::unique_ptr<VertexBuffer> VertexBuffer::Create(Vertex* aVertices)
    {
        return std::make_unique<VertexBuffer>(aVertices);
    }

}