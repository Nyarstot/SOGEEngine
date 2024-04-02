#ifndef SOGE_SQUARE_HPP
#define SOGE_SQUARE_HPP

#include "SOGE/Graphics/Vertex.hpp"
#include "SOGE/Graphics/Shader.hpp"
#include "SOGE/Graphics/VertexBuffer.hpp"
#include "SOGE/Graphics/IndexBuffer.hpp"
#include "SOGE/Graphics/ConstantBuffer.hpp"
#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/ComponentSystem/GraphicsComponents/RenderableComponent.hpp"

namespace soge
{
    class Square : public RenderableComponent
    {
    private:
        std::shared_ptr<VertexShader> mVertexShader;
        std::shared_ptr<PixelShader> mPixelShader;

        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<IndexBuffer> mIndexBuffer;
        std::unique_ptr<ConstantBuffer> mConstantBuffer;

        Vertex* mVertices;
        int* mIndices;
        float a = 0.0f;

    protected:
        void Init(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize);
        void RSStage(ID3D11DeviceContext* aContext) override;
        void IAStage(ID3D11DeviceContext* aContext) override;
        void VSStage(ID3D11DeviceContext* aContext) override;
        void PSStage(ID3D11DeviceContext* aContext) override;

    public:
        Square(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize);
        ~Square();

        virtual HRESULT InitComponent() override;
        void PreRenderStage(ID3D11DeviceContext* aContext) override;
        void Draw(ID3D11DeviceContext* aContext) override;
        void test(float a);

    public:
        static std::shared_ptr<Square> Create(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize);

    };
}

#endif // !SOGE_SQUARE_HPP
