#include "sogepch.hpp"
#include "SOGE/Graphics/CircleSprite.hpp"
#include "SOGE/Graphics/Renderer.hpp"
#include "SOGE/DebugSystem/Exception.hpp"
#include <memory>

#define PI 3.14159265358979323846  

namespace soge
{
    HRESULT CircleSprite::Init(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        mTranslation = { 0.0f, 0.0f, 0.0f };
        mRotation = { 0.0f, 0.0f, 0.0f };
        mScaling = { 1.0f, 1.0f, 1.0f };

        //Vertex points[] = {
        //    DirectX::XMFLOAT4(aCenter.x + aSize.x, aCenter.y + aSize.y, 0.5f, 1.0f),
        //    DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
        //    DirectX::XMFLOAT4(aCenter.x - aSize.x, aCenter.y - aSize.y, 0.5f, 1.0f),
        //    DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
        //    DirectX::XMFLOAT4(aCenter.x + aSize.x, aCenter.y - aSize.y, 0.5f, 1.0f),
        //    DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
        //    DirectX::XMFLOAT4(aCenter.x - aSize.x, aCenter.y + aSize.y, 0.5f, 1.0f),
        //    DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
        //};

        int segments = 100;
        std::vector<Vertex> points(segments + 1);
        points[0] = { DirectX::XMFLOAT4(aCenter.x, aCenter.y, 0.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) };

        const float theta = 2.0f * PI / segments;
        for (int i = 1; i < segments + 1; ++i) {
            float angle = i * theta;
            points[i] = { DirectX::XMFLOAT4(aCenter.x + aSize.x * cosf(angle),
                aCenter.y + aSize.y * sinf(angle), 0.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) };
        }

        std::vector<int> indices(segments * 3);
        for (int i = 0; i < segments; ++i) {
            indices[i * 3] = 0;
            indices[i * 3 + 1] = i + 1;
            indices[i * 3 + 2] = (i + 1) % segments + 1;
        }

        mVertices = points.data();
        mIndices = indices.data();

        vertexAmount = points.size();
        indexAmount = indices.size();

        //int indices[] = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5};

        mVertexBuffer = VertexBuffer::Create(mVertices, vertexAmount);
        mIndexBuffer = IndexBuffer::Create(mIndices, indexAmount);

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

    void CircleSprite::RSStage(ID3D11DeviceContext* aContext)
    {
        return;
    }

    void CircleSprite::IAStage(ID3D11DeviceContext* aContext)
    {
        UINT strides[] = { 32 };
        UINT offset[] = { 0 };

        aContext->IASetInputLayout(mVertexShader->GetInputLayout());
        aContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        aContext->IASetIndexBuffer(mIndexBuffer->Get(), DXGI_FORMAT_R32_UINT, 0);
        aContext->IASetVertexBuffers(0, 1, mVertexBuffer->GetAddressOf(), strides, offset);
    }

    void CircleSprite::VSStage(ID3D11DeviceContext* aContext)
    {
        aContext->VSSetShader(mVertexShader->GetShader(), nullptr, 0);
    }

    void CircleSprite::PSStage(ID3D11DeviceContext* aContext)
    {
        aContext->PSSetShader(mPixelShader->GetShader(), nullptr, 0);
    }

    CircleSprite::CircleSprite(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        this->Init(aCenter, aSize);
    }

    CircleSprite::~CircleSprite()
    {
        mVertexBuffer.release();
        mIndexBuffer.release();
        mConstantBuffer.release();
    }

    void CircleSprite::Draw()
    {
        ID3D11DeviceContext* context = Renderer::GetInstance()->mDeviceContext.Get();

        this->RSStage(context);
        this->IAStage(context);
        this->VSStage(context);
        mConstantBuffer->UpdateBufferData();
        this->PSStage(context);

        context->DrawIndexed(indexAmount, 0, 0);
    }

    void CircleSprite::Update(float aDeltaTime)
    {
        mConstantBuffer->SetConstantData(mTransform);
    }

    void CircleSprite::UpdateConstantBuffer()
    {
        CBTransform newTransform = {
            {
                dx::XMMatrixTranspose(
                    dx::XMMatrixRotationZ(mRotation.z) *
                    dx::XMMatrixScaling(mScaling.x, mScaling.y, mScaling.z) *
                    dx::XMMatrixTranslation(mTranslation.x, mTranslation.y, mTranslation.z)
                )
            }, { r, g, b, 1.0f }
        };

        mTransform = std::move(newTransform);
    }

    void CircleSprite::Transform(Point3D aTranslate, Point3D aRotate, Point3D aScale)
    {
        mTranslation += aTranslate;
        mRotation += aRotate;
        mScaling += aScale;
        this->UpdateConstantBuffer();
    }

    void CircleSprite::Translate(Point3D aTranslate)
    {
        this->Transform(aTranslate, Point3D(), Point3D());
    }

    void CircleSprite::Rotate(Point3D aRotate)
    {
        this->Transform(Point3D(), aRotate, Point3D());
    }

    void CircleSprite::Scale(Point3D aScale)
    {
        this->Transform(Point3D(), Point3D(), aScale);
    }

    void CircleSprite::Move(Point3D aMoveTo)
    {
        mTranslation = aMoveTo;
    }

    std::shared_ptr<CircleSprite> CircleSprite::Create(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        return std::make_shared<CircleSprite>(aCenter, aSize);
    }

    std::shared_ptr<CircleSprite> CircleSprite::CreateShared(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        return std::make_shared<CircleSprite>(aCenter, aSize);
    }

    std::unique_ptr<CircleSprite> CircleSprite::CreateUnique(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize)
    {
        return std::make_unique<CircleSprite>(aCenter, aSize);
    }
}