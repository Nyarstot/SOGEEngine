#ifndef SOGE_TRIANGLE_HPP
#define SOGE_TRIANGLE_HPP

#include "SOGE/Graphics/VertexBuffer.hpp"
#include "SOGE/Graphics/IndexBuffer.hpp"
#include "SOGE/Graphics/Vertex.hpp"
#include "SOGE/Graphics/Shader.hpp"

namespace soge
{
    class Triangle
    {
    private:
        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<IndexBuffer> mIndexBuffer;

        Vertex* mVertices           = nullptr;
        VertexShader* mVertexShader = nullptr;
        PixelShader* mPixelShader   = nullptr;

        const UINT mStrides = sizeof(Vertex);
        const UINT mOffset = 0u;

    protected:
        HRESULT Init();

    public:
        Triangle();
        ~Triangle();

        void OnUpdate();

    };
}

#endif // !SOGE_TRIANGLE_HPP
