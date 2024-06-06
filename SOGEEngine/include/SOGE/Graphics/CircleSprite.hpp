#ifndef SOGE_CIRCLE_HPP
#define SOGE_CIRCLE_HPP

#include "SOGE/Graphics/Shader.hpp"
#include "SOGE/Graphics/VertexBuffer.hpp"
#include "SOGE/Graphics/IndexBuffer.hpp"
#include "SOGE/Graphics/ConstantBuffer.hpp"
#include "SOGE/Interface/GraphicsInterfaces.hpp"
#include "SOGE/Graphics/Vertex.hpp"
#include "SOGE/Containers/Simple.hpp"

namespace soge
{
    class CircleSprite : public IShaderEnabled
    {
        using CBT = ConstantBuffer<CBTransform>;

    private:
        std::shared_ptr<VertexShader> mVertexShader;
        std::shared_ptr<PixelShader> mPixelShader;

        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<IndexBuffer> mIndexBuffer;
        std::unique_ptr<CBT> mConstantBuffer;

        Vertex* mVertices;
        int* mIndices;

        int vertexAmount;
        int indexAmount;

        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;

        Point3D mTranslation;
        Point3D mRotation;
        Point3D mScaling;

        CBTransform mTransform = {
            {
                dx::XMMatrixTranspose(
                    dx::XMMatrixRotationZ(0.0f) *
                    dx::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
                    dx::XMMatrixTranslation(0.0f, 0.0f, 0.0f)
                )
            }, { r, g, b, 1.0f }
        };

        void UpdateConstantBuffer();

    protected:
        HRESULT Init(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize);
        void RSStage(ID3D11DeviceContext* aContext) override;
        void IAStage(ID3D11DeviceContext* aContext) override;
        void VSStage(ID3D11DeviceContext* aContext) override;
        void PSStage(ID3D11DeviceContext* aContext) override;

    public:
        CircleSprite(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize);
        ~CircleSprite();

        void Draw() override;
        void Update(float aDeltaTime) override;
        void Transform(Point3D aTranslate, Point3D aRotate, Point3D aScale) override;
        void Translate(Point3D aTranslate);
        void Rotate(Point3D aRotate);
        void Scale(Point3D aScale);

        void Move(Point3D aMoveTo);

        inline const Point3D GetTranslation() const { return mTranslation; }
        inline const Point3D& GetTranslation() { return mTranslation; }
        inline const Point3D GetRotation() const { return mRotation; }
        inline const Point3D& GetRotation() { return mRotation; }
        inline const Point3D GetScaling() const { return mScaling; }
        inline const Point3D& GetScaling() { return mScaling; }

    public:
        static std::shared_ptr<CircleSprite> Create(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize);
        static std::shared_ptr<CircleSprite> CreateShared(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize);
        static std::unique_ptr<CircleSprite> CreateUnique(const dxsmath::Vector2& aCenter, const dxsmath::Vector2& aSize);
    };
}

#endif // !SOGE_CIRCLE_HPP
