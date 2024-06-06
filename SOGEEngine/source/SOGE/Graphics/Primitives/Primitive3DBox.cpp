#include "sogepch.hpp"
#include "SOGE/Graphics/Primiteives/Primitive3DBox.hpp"
#include "SOGE/DebugSystem/Exception.hpp"
#include "SOGE/Graphics/Renderer.hpp"


namespace soge
{
    void Primitive3DBox::RSStage(ID3D11DeviceContext* aContext)
    {
        return;
    }

    void Primitive3DBox::IAStage(ID3D11DeviceContext* aContext)
    {
        mVertexShader->Bind();
        aContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        mIndexBuffer->Bind();
        mVertexBuffer->Bind();
    }

    void Primitive3DBox::VSStage(ID3D11DeviceContext* aContext)
    {
        aContext->VSSetShader(mVertexShader->GetShader(), nullptr, 0);
    }

    void Primitive3DBox::PSStage(ID3D11DeviceContext* aContext)
    {
        //mPixelShader->Bind();
        aContext->PSSetShader(mPixelShader->GetShader(), nullptr, 0);
    }

    Primitive3DBox::Primitive3DBox(const Point3D& aSize, const Point3D& aCenter)
    {
        mTransform = Transform::CreateUnique();

        mVertices = std::vector<Vertex>(8);
        mVertices[0].position = { aCenter.x - aSize.x, aCenter.y + aSize.y, 0.0f, 1.0f };
        mVertices[0].color = { 1.0f, 1.0f, 1.0f, 1.0f };
        mVertices[1].position = { aCenter.x - aSize.x, aCenter.y - aSize.y, 0.0f, 1.0f };
        mVertices[1].color = { 1.0f, 1.0f, 1.0f, 1.0f };
        mVertices[2].position = { aCenter.x + aSize.x, aCenter.y - aSize.y, 0.0f, 1.0f };
        mVertices[2].color = { 1.0f, 1.0f, 1.0f, 1.0f };
        mVertices[3].position = { aCenter.x + aSize.x, aCenter.y + aSize.y, 0.0f, 1.0f };
        mVertices[3].color = { 1.0f, 1.0f, 1.0f, 1.0f };
        mVertices[4].position = { aCenter.x - aSize.x, aCenter.y + aSize.y, aCenter.z - aSize.z, 1.0f };
        mVertices[4].color = { 1.0f, 0.0f, 0.0f, 1.0f };
        mVertices[5].position = { aCenter.x - aSize.x, aCenter.y - aSize.y, aCenter.z - aSize.z, 1.0f };
        mVertices[5].color = { 1.0f, 0.0f, 0.0f, 1.0f };
        mVertices[6].position = { aCenter.x + aSize.x, aCenter.y - aSize.y, aCenter.z - aSize.z, 1.0f };
        mVertices[6].color = { 1.0f, 0.0f, 0.0f, 1.0f };
        mVertices[7].position = { aCenter.x + aSize.x, aCenter.y + aSize.y, aCenter.z - aSize.z, 1.0f };
        mVertices[7].color = { 1.0f, 0.0f, 0.0f, 1.0f };

        mIndices = {
            0,2,3, 0,2,1,
            3,6,2, 3,6,7,
            7,5,6, 7,5,4,
            4,1,5, 4,1,0,
            0,7,3, 0,7,4,
            1,6,2, 1,6,5
        };

        mVertexBuffer = VertexBuffer::CreateUnique(mVertices);
        mIndexBuffer = IndexBuffer::CreateUnique(mIndices);

        ID3D11Device* device = Renderer::GetInstance()->GetDevice();
        ID3D11DeviceContext* context = Renderer::GetInstance()->GetDeviceContext();
        mConstantBuffer = std::make_unique<CBT>(device, context, mTransformB);

        SOGE_SHADER_DESC vtxShaderDesc;
        vtxShaderDesc.name = L"TestVerexShader";
        vtxShaderDesc.path = L"shaders/MyVeryFirstShader.hlsl";
        vtxShaderDesc.entryPoint = "VSMain";
        vtxShaderDesc.target = "vs_5_0";

        SOGE_SHADER_DESC pxShaderDesc;
        pxShaderDesc.name = L"TestPixelShader";
        pxShaderDesc.path = L"shaders/MyVeryFirstShader.hlsl";
        pxShaderDesc.entryPoint = "PSMain";
        pxShaderDesc.target = "ps_5_0";

        mVertexShader = std::make_shared<VertexShader>(vtxShaderDesc);
        HRESULT result = mVertexShader->CompileAndCreate();
        DXThrowIfFailed(result, "Failed to compile sprite vertex shader");

        mPixelShader = std::make_shared<PixelShader>(pxShaderDesc);
        result = mPixelShader->CompileAndCreate();
        DXThrowIfFailed(result, "Failed to compile sprite pixel shader");
    }

    Primitive3DBox::~Primitive3DBox()
    {
        
    }

    void Primitive3DBox::Draw()
    {
        ID3D11DeviceContext* context = Renderer::GetInstance()->GetDeviceContext();

        this->RSStage(context);
        this->IAStage(context);
        this->VSStage(context);
        mConstantBuffer->UpdateBufferData();
        mConstantBuffer->Bind();
        this->PSStage(context);

        context->DrawIndexed(mIndexBuffer->GetIndicesCount(), 0u, 0u);
    }

    void Primitive3DBox::Update(float aDeltaTime)
    {

    }

    // Static constructor callers

    std::shared_ptr<Primitive3DBox> Primitive3DBox::CreateShared(const Point3D& aSize, const Point3D& aCenter)
    {
        return std::make_shared<Primitive3DBox>(aSize, aCenter);
    }

    std::unique_ptr<Primitive3DBox> Primitive3DBox::CreateUnique(const Point3D& aSize, const Point3D& aCenter)
    {
        return std::make_unique<Primitive3DBox>(aSize, aCenter);
    }
}