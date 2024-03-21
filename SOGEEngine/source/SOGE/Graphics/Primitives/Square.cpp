#include "sogepch.hpp"
#include "SOGE/Graphics/Primitives/Square.hpp"

namespace soge
{
    void Square::Init(const dxsmath::Vector2& aCenter, dxsmath::Vector2& aSize)
    {
        Vertex points[] = {
            DirectX::XMFLOAT4(aCenter.x + aSize.x, aCenter.y + aSize.y, 0.5f, 1.0f),
            DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
            DirectX::XMFLOAT4(aCenter.x - aSize.x, aCenter.y - aSize.y, 0.5f, 1.0f),
            DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
            DirectX::XMFLOAT4(aCenter.x + aSize.x, aCenter.y - aSize.y, 0.5f, 1.0f),
            DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
            DirectX::XMFLOAT4(aCenter.x - aSize.x, aCenter.y + aSize.y, 0.5f, 1.0f),
            DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
        };
        mVertices = points;

        int indeces[] = { 0,1,2, 1,0,3 };
        mIndices = indeces;

        mVertexBuffer   = VertexBuffer::Create(mVertices);
        mIndexBuffer    = IndexBuffer::Create(mIndices);

        SOGE_SHADER_DESC vShaderDesc;
        vShaderDesc.name = L"TestVerexShader";
        vShaderDesc.path = L"shaders/MyVeryFirstShader.hlsl";
        vShaderDesc.entryPoint = "VSMain";
        vShaderDesc.target = "vs_5_0";

        SOGE_SHADER_DESC pShaderDesc;
        pShaderDesc.name = L"TestPixelShader";
        pShaderDesc.path = L"shaders/MyVeryFirstShader.hlsl";
        pShaderDesc.entryPoint = "PSMain";
        pShaderDesc.target = "ps_5_0";

        mVertexShader = std::make_shared<VertexShader>(pShaderDesc);
        mVertexShader->CompileAndCreate();

        mPixelShader = std::make_shared<PixelShader>(vShaderDesc);
        mPixelShader->CompileAndCreate();
    }

    Square::Square(const dxsmath::Vector2& aCenter, dxsmath::Vector2& aSize)
    {
        this->Init(aCenter, aSize);
    }

    Square::~Square()
    {
        mVertexBuffer.release();
        mIndexBuffer.release();
    }

    std::unique_ptr<Square> Square::Create(const dxsmath::Vector2& aCenter, dxsmath::Vector2& aSize)
    {
        return std::make_unique<Square>(aCenter, aSize);
    }
}