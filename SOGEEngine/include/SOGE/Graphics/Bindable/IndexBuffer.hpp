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

    protected:
        HRESULT Init(int* indeces);

    public:
        IndexBuffer(int* indeces);
        ~IndexBuffer();

        void Bind() noexcept override;
        ID3D11Buffer* Get() const { return mIndexBuffer.Get(); }
        ID3D11Buffer* const* GetAddresOf() { return mIndexBuffer.GetAddressOf(); }

    public:
        static std::unique_ptr<IndexBuffer> Create(int* indeces);

    };
}

#endif // !SOGE_INDEX_BUFFER_HPP
