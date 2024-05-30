#ifndef SOGE_VERTEX_BUFFER_HPP
#define SOGE_VERTEX_BUFFER_HPP

#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/Graphics/Vertex.hpp"

#include <d3d11.h>
#include <SimpleMath.h>

namespace soge
{
    class VertexBuffer final
    {
    private:
        wrl::ComPtr<ID3D11Buffer> mVertexBuffer;
        UINT mVertexTypeSize = 0;
        UINT mVertexCount = 0;

    protected:
        HRESULT Init(Vertex* aVertices, int vertexAmount);

    public:
        VertexBuffer(Vertex* aVertices, int vertexAmount);
        ~VertexBuffer();

        ID3D11Buffer* GetVertices() const { return mVertexBuffer.Get(); }
        ID3D11Buffer* const* GetAddressOf() { return mVertexBuffer.GetAddressOf(); }

    public:
        static std::unique_ptr<VertexBuffer> Create(Vertex* aVertices, int vertexAmount);

    };
}

#endif // !SOGE_VERTEX_BUFFER_HPP
