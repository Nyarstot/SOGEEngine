#include "sogepch.hpp"
#include "SOGE/Graphics/Primitives/Square.hpp"
#include "SOGE/Graphics/Renderer.hpp"

namespace soge
{
    void Square::Init(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
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
        //Vertex points[] = {
        //    DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),      DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
        //    DirectX::XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f),    DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
        //    DirectX::XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f),     DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
        //    DirectX::XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f),     DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
        //};
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

        mVertexShader = std::make_shared<VertexShader>(vShaderDesc);
        mVertexShader->CompileAndCreate();

        mPixelShader = std::make_shared<PixelShader>(pShaderDesc);
        mPixelShader->CompileAndCreate();
    }

    Square::Square(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        this->Init(aCenter, aSize);
        this->InitComponent();
    }

    Square::~Square()
    {
        mVertexBuffer.release();
        mIndexBuffer.release();
    }

    HRESULT Square::InitComponent()
    {
        return E_NOTIMPL;
    }

    void Square::Draw(ID3D11DeviceContext* aContext)
    {
        RSStage(aContext);
        IAStage(aContext);
        VSStage(aContext);
        PSStage(aContext);
        aContext->DrawIndexed(6, 0, 0);
    }

    void Square::PreRenderStage(ID3D11DeviceContext* aContext)
    {

    }

    void Square::RSStage(ID3D11DeviceContext* aContext)
    {

    }

    void Square::IAStage(ID3D11DeviceContext* aContext)
    {
        UINT strides[] = { 32 };
        UINT offsets[] = { 0 };

        aContext->IASetInputLayout(mVertexShader->GetInputLayout());
        aContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        aContext->IASetIndexBuffer(mIndexBuffer->Get(), DXGI_FORMAT_R32_UINT, 0);
        aContext->IASetVertexBuffers(0, 1, mVertexBuffer->GetAddresOf(), strides, offsets);
    }

    void Square::VSStage(ID3D11DeviceContext* aContext)
    {
        aContext->VSSetShader(mVertexShader->GetShader(), nullptr, 0);
    }

    void Square::PSStage(ID3D11DeviceContext* aContext)
    {
        aContext->PSSetShader(mPixelShader->GetShader(), nullptr, 0);
    }

    std::shared_ptr<Square> Square::Create(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        return std::make_shared<Square>(aCenter, aSize);
    }
}