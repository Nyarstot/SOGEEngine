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
        UINT mVertexTypeSize = 0;
        UINT mVertexCount = 0;
        UINT mStrides = 0;
        UINT mOffset = 0;

    public:
        VertexBuffer(std::vector<Vertex>& aVertices, UINT aOffset=0);
        ~VertexBuffer();

        void SetStrides(UINT aStrides) { mStrides = aStrides; }
        UINT GetStrides() const { return mStrides; }
        void SetOffset(UINT aOffset) { mOffset = aOffset; }
        UINT GetOffset() const { return mOffset; }

        void Bind() noexcept override;
        ID3D11Buffer* GetVertices() const { return mVertexBuffer.Get(); }
        ID3D11Buffer* const* GetAddressOf() { return mVertexBuffer.GetAddressOf(); }

    public:
        static std::shared_ptr<VertexBuffer> CreateShared(std::vector<Vertex>& aVertices, UINT aOffset=0);
        static std::unique_ptr<VertexBuffer> CreateUnique(std::vector<Vertex>& aVertices, UINT aOffset=0);

    };
}

#endif // !SOGE_VERTEX_BUFFER_HPP
