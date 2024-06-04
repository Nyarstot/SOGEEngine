#ifndef SOGE_INDEX_BUFFER_HPP
#define SOGE_INDEX_BUFFER_HPP

#include "SOGE/Interface/GraphicsInterfaces.hpp"
#include "SOGE/Engine/EngineSetup.hpp"
#include <d3d11.h>

namespace soge
{
    class IndexBuffer final : public IBindable
    {
    private:
        wrl::ComPtr<ID3D11Buffer> mIndexBuffer;

    public:
        IndexBuffer() = delete;
        IndexBuffer(std::vector<UINT> aIndices);
        ~IndexBuffer();

        void Bind() noexcept override;
        ID3D11Buffer* Get() const { return mIndexBuffer.Get(); }
        ID3D11Buffer* const* GetAddresOf() { return mIndexBuffer.GetAddressOf(); }

    public:
        static std::shared_ptr<IndexBuffer> CreateShared(std::vector<UINT> aIndices);
        static std::unique_ptr<IndexBuffer> CreateUnique(std::vector<UINT> aIndices);

    };
}

#endif // !SOGE_INDEX_BUFFER_HPP
