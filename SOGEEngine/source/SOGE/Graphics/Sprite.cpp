#include "sogepch.hpp"
#include "SOGE/Graphics/Sprite.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/DebugSystem/Exception.hpp"

namespace soge
{
    HRESULT Sprite::Init(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        mTranslation = { 0.0f, 0.0f, 0.0f };
        mRotation = { 0.0f, 0.0f, 0.0f };
        mScaling = { 1.0f, 1.0f, 1.0f };

        mVertices = std::vector<Vertex>(4);
        mVertices[0].position = { aCenter.x + aSize.x, aCenter.y + aSize.y, 0.5f, 1.0f };
        mVertices[0].color = { r, g, b, 1.0f };
        mVertices[1].position = { aCenter.x - aSize.x, aCenter.y - aSize.y, 0.5f, 1.0f };
        mVertices[1].color = { r, g, b, 1.0f };
        mVertices[2].position = { aCenter.x + aSize.x, aCenter.y - aSize.y, 0.5f, 1.0f };
        mVertices[2].color = { r, g, b, 1.0f };
        mVertices[3].position = { aCenter.x - aSize.x, aCenter.y + aSize.y, 0.5f, 1.0f };
        mVertices[3].color = { r, g, b, 1.0f };

        mIndices = {
            0, 1, 2, 1, 0, 3
        };

        mVertexBuffer = VertexBuffer::Create(mVertices.data(), 8);
        mIndexBuffer = IndexBuffer::Create(mIndices.data(), 6);

        ID3D11Device* device = Renderer::GetInstance()->mDevice.Get();
        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();
        mConstantBuffer = CBT::Create(device, context, mTransform);

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

        return S_OK;
    }

    void Sprite::RSStage(ID3D11DeviceContext* aContext)
    {
        return;
    }

    void Sprite::IAStage(ID3D11DeviceContext* aContext)
    {
        UINT strides[] = { 32 };
        UINT offset[] = { 0 };

        aContext->IASetInputLayout(mVertexShader->GetInputLayout());
        aContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        aContext->IASetIndexBuffer(mIndexBuffer->Get(), DXGI_FORMAT_R32_UINT, 0);
        aContext->IASetVertexBuffers(0, 1, mVertexBuffer->GetAddressOf(), strides, offset);
    }

    void Sprite::VSStage(ID3D11DeviceContext* aContext)
    {
        aContext->VSSetShader(mVertexShader->GetShader(), nullptr, 0);
    }

    void Sprite::PSStage(ID3D11DeviceContext* aContext)
    {
        aContext->PSSetShader(mPixelShader->GetShader(), nullptr, 0);
    }

    Sprite::Sprite(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        this->Init(aCenter, aSize);
    }

    Sprite::~Sprite()
    {
        mVertexBuffer.release();
        mIndexBuffer.release();
        mConstantBuffer.release();
    }

    void Sprite::Draw()
    {
        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();

        this->RSStage(context);
        this->IAStage(context);
        this->VSStage(context);
        mConstantBuffer->UpdateBufferData();
        this->PSStage(context);

        context->DrawIndexed(6, 0, 0);
    }

    void Sprite::Update(float aDeltaTime)
    {
        mConstantBuffer->SetConstantData(mTransform);
    }

    void Sprite::UpdateConstantBuffer()
    {
        CBTransform newTransform = {
            {
                dx::XMMatrixTranspose(
                    dx::XMMatrixRotationZ(mRotation.z) *
                    dx::XMMatrixScaling(mScaling.x, mScaling.y, mScaling.z) *
                    dx::XMMatrixTranslation(mTranslation.x, mTranslation.y, mTranslation.z)
                )
            },
            {
                r, g, b, 1.0f
            }
        };

        mTransform = std::move(newTransform);
    }

    void Sprite::Transform(Point3D aTranslate, Point3D aRotate, Point3D aScale)
    {
        mTranslation += aTranslate;
        mRotation += aRotate;
        mScaling += aScale;
        this->UpdateConstantBuffer();
    }

    void Sprite::Translate(Point3D aTranslate)
    {
        this->Transform(aTranslate, Point3D(), Point3D());
    }

    void Sprite::Rotate(Point3D aRotate)
    {
        this->Transform(Point3D(), aRotate, Point3D());
    }

    void Sprite::Scale(Point3D aScale)
    {
        this->Transform(Point3D(), Point3D(), aScale);
    }

    void Sprite::ChangeColor(float r, float g, float b)
    {
        this->r = r;
        this->g = g;
        this->b = b;

        //SOGE_INFO_LOG("R{0} G{1} B{2}, A{3}", r, g, b, 1.0f);
        this->UpdateConstantBuffer();
    }

    void Sprite::Move(Point3D aMoveTo)
    {
        mTranslation = aMoveTo;
    }

    std::shared_ptr<Sprite> Sprite::Create(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        return std::make_shared<Sprite>(aCenter, aSize);
    }

    std::shared_ptr<Sprite> Sprite::CreateShared(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        return std::make_shared<Sprite>(aCenter, aSize);
    }

    std::unique_ptr<Sprite> Sprite::CreateUnique(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        return std::make_unique<Sprite>(aCenter, aSize);
    }
}