#include "sogepch.hpp"
#include "SOGE/Graphics/Primitives/Triangle.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    HRESULT Triangle::Init()
    {
        Vertex vertices[] = {
            DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
            DirectX::XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
            DirectX::XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
            DirectX::XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        }; mVertices = vertices;
        int indeces[] = { 0,1,2, 1,0,3 };

        mVertexBuffer = VertexBuffer::Create(mVertices);
        mIndexBuffer = IndexBuffer::Create(indeces);

        mVertexShader = new VertexShader(L"TriangleVertexShader", L"shaders/SimpleShader_vert.hlsl");
        mVertexShader->CompileAndCreate();

        mPixelShader = new PixelShader(L"TrianglePixelShader", L"shaders/SimpleShader_frag.hlsl");
        mPixelShader->CompileAndCreate();

        return S_OK;
    }

    Triangle::Triangle()
    {
        HRESULT result = Init();
        if (FAILED(result)) {
            SOGE_ERROR_LOG("Failed to initialize primitive data");
        }
    }

    Triangle::~Triangle()
    {

    }

    void Triangle::OnUpdate()
    {
        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();
        context->IASetInputLayout(mVertexShader->GetInputLayout());
        context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        context->IASetIndexBuffer(mIndexBuffer->Get(), DXGI_FORMAT_R32_UINT, 0);
        context->IASetVertexBuffers(0u, 1u, mVertexBuffer->GetAddresOf(), &mStrides, &mOffset);
        mVertexShader->Bind();
        mPixelShader->Bind();
        context->DrawIndexed(6, 0, 0);
    }

}