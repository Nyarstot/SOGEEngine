#ifndef SOGE_INDEX_BUFFER_HPP
#define SOGE_INDEX_BUFFER_HPP

#include "SOGE/Engine/EngineSetup.hpp"
#include <d3d11.h>

namespace soge
{
    class IndexBuffer final
    {
    private:
        wrl::ComPtr<ID3D11Buffer> mIndexBuffer;

    protected:
        HRESULT Init(int* indeces, int indexAmount);

    public:
        IndexBuffer(int* indeces, int indexAmount);
        ~IndexBuffer();

        ID3D11Buffer* Get() const { return mIndexBuffer.Get(); }
        ID3D11Buffer* const* GetAddresOf() { return mIndexBuffer.GetAddressOf(); }

    public:
        static std::unique_ptr<IndexBuffer> Create(int* indeces, int indexAmount);

    };
}

#endif // !SOGE_INDEX_BUFFER_HPP
