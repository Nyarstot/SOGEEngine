#ifndef SOGE_VERTEX_BUFFER_HPP
#define SOGE_VERTEX_BUFFER_HPP

#include "SOGE/Interface/GraphicsInterfaces.hpp"
#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/Graphics/Vertex.hpp"

#include <d3d11.h>
#include <SimpleMath.h>

namespace soge
{
    class VertexBuffer final : public IBindable
    {
    private:
        wrl::ComPtr<ID3D11Buffer> mVertexBuffer;
        std::unique_ptr<UINT> mStrides  = nullptr;
        std::unique_ptr<UINT> mOffset   = nullptr;

        UINT mVertexTypeSize = 0;
        UINT mVertexCount = 0;

    public:
        void InitBufferData(Vertex* aVertices);

    public:
        VertexBuffer(Vertex* aVertices);
        VertexBuffer(Vertex* aVertices, UINT aStrides, UINT aOffset);
        ~VertexBuffer();

        void SetStrides(UINT aStrides);
        UINT* GetStrides() const { return mStrides.get(); }
        void SetOffset(UINT aOffset);
        UINT* GetOffset() const { return mOffset.get(); }

        void Bind() noexcept override;
        ID3D11Buffer* GetVertices() const { return mVertexBuffer.Get(); }
        ID3D11Buffer* const* GetAddressOf() { return mVertexBuffer.GetAddressOf(); }

    public:
        static std::shared_ptr<VertexBuffer> CreateShared(Vertex* aVertices);
        static std::unique_ptr<VertexBuffer> CreateUnique(Vertex* aVertices);

        static std::shared_ptr<VertexBuffer> CreateShared(Vertex* aVertices, UINT aStrides, UINT aOffset);
        static std::unique_ptr<VertexBuffer> CreateUnique(Vertex* aVertices, UINT aStrides, UINT aOffset);

    };
}

#endif // !SOGE_VERTEX_BUFFER_HPP
