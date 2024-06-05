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
        std::shared_ptr<VertexShader> mVertexShader;
        std::shared_ptr<PixelShader> mPixelShader;
        std::unique_ptr<Transform> mTransform;
        std::unique_ptr<IndexBuffer> mIndexBuffer;
        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<CBT> mConstantBuffer;

        std::vector<Vertex> mVertices;
        std::vector<UINT> mIndices;

    public:
        Primitive3DBox(const Point3D& aSize, const Point3D& aCenter);
        ~Primitive3DBox();

        void Update(float aDeltaTime) override;

    public:
        static std::shared_ptr<Primitive3DBox> CreateShared(const Point3D& aSize, const Point3D& aCenter);
        static std::unique_ptr<Primitive3DBox> CreateUnique(const Point3D& aSize, const Point3D& aCenter);

    };
}

#endif // !SOGE_BOX_HPP
