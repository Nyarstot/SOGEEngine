#include "sogepch.hpp"
#include "SOGE/Graphics/Primiteives/Primitive3DBox.hpp"
#include "SOGE/DebugSystem/Exception.hpp"


namespace soge
{
    Primitive3DBox::Primitive3DBox(const Point3D& aSize, const Point3D& aCenter)
    {
        mTransform = Transform::CreateUnique();

        mVertices = std::vector<Vertex>(8);
        mVertices[0].position = { aCenter.x - aSize.x, aCenter.y + aSize.y, 0.0f, 1.0f };
        mVertices[0].color = { 1.0f, 0.0f, 0.0f, 1.0f };
        mVertices[1].position = { aCenter.x - aSize.x, aCenter.y - aSize.y, 0.0f, 1.0f };
        mVertices[1].color = { 0.0f, 0.0f, 1.0f, 1.0f };
        mVertices[2].position = { aCenter.x + aSize.x, aCenter.y - aSize.y, 0.0f, 1.0f };
        mVertices[2].color = { 0.0f, 1.0f, 0.0f, 1.0f };
        mVertices[3].position = { aCenter.x + aSize.x, aCenter.y + aSize.y, 0.0f, 1.0f };
        mVertices[3].color = { 1.0f, 0.0f, 1.0f, 1.0f };
        mVertices[4].position = { aCenter.x - aSize.x, aCenter.y + aSize.y, aCenter.z - aSize.z, 1.0f };
        mVertices[4].color = { 1.0f, 0.0f, 0.0f, 1.0f };
        mVertices[5].position = { aCenter.x - aSize.x, aCenter.y - aSize.y, aCenter.z - aSize.z, 1.0f };
        mVertices[5].color = { 0.0f, 0.0f, 1.0f, 1.0f };
        mVertices[6].position = { aCenter.x + aSize.x, aCenter.y - aSize.y, aCenter.z - aSize.z, 1.0f };
        mVertices[6].color = { 0.0f, 1.0f, 0.0f, 1.0f };
        mVertices[7].position = { aCenter.x + aSize.x, aCenter.y + aSize.y, aCenter.z - aSize.z, 1.0f };
        mVertices[7].color = { 1.0f, 0.0f, 1.0f, 1.0f };

        mIndices = {
            0,2,1, 2,3,1,
            1,3,5, 3,7,5,
            2,6,3, 3,6,7,
            4,5,7, 4,7,6,
            0,4,2, 2,4,6,
            0,1,4, 1,5,4
        };

        mVertexBuffer = VertexBuffer::CreateUnique(mVertices);
        mIndexBuffer = IndexBuffer::CreateUnique(mIndices);

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

        //this->AddBindable(std::make_unique<VertexBuffer>());
        //this->AddIndexBuffer(mIndexBuffer);
    }

    Primitive3DBox::~Primitive3DBox()
    {

    }

    void Primitive3DBox::Update(float aDeltaTime)
    {
        //mVertexShader->Bind();
        //mIndexBuffer->Bind();
        //mVertexBuffer->Bind();
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