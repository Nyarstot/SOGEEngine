#ifndef SOGE_BOX_HPP
#define SOGE_BOX_HPP

#include "SOGE/Interface/GraphicsInterfaces.hpp"
#include "SOGE/Graphics/Bindable/IndexBuffer.hpp"
#include "SOGE/Graphics/Bindable/VertexBuffer.hpp"
#include "SOGE/Graphics/Bindable/ConstantBuffer.hpp"
#include "SOGE/Graphics/Bindable/Shader.hpp"
#include "SOGE/Containers/Simple.hpp"
#include "SOGE/Game/Transform.hpp"

namespace soge
{
    class Primitive3DBox : public IDrawable
    {
        using CBT = VertexConstantBuffer<CBTransform>;

    private:
        std::unique_ptr<Transform> mTransform       = nullptr;
        std::shared_ptr<VertexShader> mVertexShader = nullptr;
        std::shared_ptr<PixelShader> mPixelShader   = nullptr;
        std::unique_ptr<IndexBuffer> mIndexBuffer   = nullptr;
        std::unique_ptr<VertexBuffer> mVertexBuffer = nullptr;
        std::unique_ptr<CBT> mConstantBuffer        = nullptr;

        std::vector<Vertex> mVertices;
        std::vector<UINT> mIndices;

    protected:
        virtual void RSStage(ID3D11DeviceContext* aContext) override;
        virtual void IAStage(ID3D11DeviceContext* aContext) override;
        virtual void VSStage(ID3D11DeviceContext* aContext) override;
        virtual void PSStage(ID3D11DeviceContext* aContext) override;

        CBTransform mTransformB = {
            {
                dx::XMMatrixTranspose(
                    dx::XMMatrixRotationZ(0.0f) *
                    dx::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
                    dx::XMMatrixTranslation(0.0f, 0.0f, 0.0f)
                )
            }
        };

    public:
        Primitive3DBox(const Point3D& aSize, const Point3D& aCenter);
        ~Primitive3DBox();

        void Draw() override;
        void Update(float aDeltaTime) override;

    public:
        static std::shared_ptr<Primitive3DBox> CreateShared(const Point3D& aSize, const Point3D& aCenter);
        static std::unique_ptr<Primitive3DBox> CreateUnique(const Point3D& aSize, const Point3D& aCenter);

    };
}

#endif // !SOGE_BOX_HPP
