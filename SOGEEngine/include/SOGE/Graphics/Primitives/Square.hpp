#ifndef SOGE_SQUARE_HPP
#define SOGE_SQUARE_HPP

#include "SOGE/Graphics/Vertex.hpp"
#include "SOGE/Graphics/Shader.hpp"
#include "SOGE/Graphics/VertexBuffer.hpp"
#include "SOGE/Graphics/IndexBuffer.hpp"
#include "SOGE/Engine/EngineSetup.hpp"

namespace soge
{
    class Square
    {
    private:
        std::shared_ptr<VertexShader> mVertexShader;
        std::shared_ptr<PixelShader> mPixelShader;

        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<IndexBuffer> mIndexBuffer;

        Vertex* mVertices;
        int* mIndices;

    protected:
        void Init(const dxsmath::Vector2& aCenter, dxsmath::Vector2& aSize);

    public:
        Square(const dxsmath::Vector2& aCenter, dxsmath::Vector2& aSize);
        ~Square();

    public:
        std::unique_ptr<Square> Create(const dxsmath::Vector2& aCenter, dxsmath::Vector2& aSize);

    };
}

#endif // !SOGE_SQUARE_HPP
