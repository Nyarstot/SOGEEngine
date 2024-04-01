#ifndef SOGE_CONSTANT_BUFFER
#define SOGE_CONSTANT_BUFFER

#include "SOGE/Engine/EngineSetup.hpp"
#include <d3d11.h>

namespace soge
{
    struct CBTransform
    {
        struct
        {
            float element[4][4];
        }transformation;
    };

    typedef struct SOGE_CONSTANT_BUFFER_DESC
    {
        void* bufferData;
        float aspectRatio;
    } SOGE_CONSTANT_BUFFER_DESC;

    class ConstantBuffer
    {
    private:
        float mAspectRatio  = 0.0f;
        void* mBufferData   = nullptr;

        wrl::ComPtr<ID3D11Buffer> mConstantBuffer;

    protected:
        HRESULT Init(void* aBuffer, float aAspectRatio);

    public:
        ConstantBuffer(void* aBuffer, float aAspectRatio);
        ConstantBuffer(SOGE_CONSTANT_BUFFER_DESC aDescriptor);
        ~ConstantBuffer();

        void Update(float aData);
        ID3D11Buffer* Get() const { return mConstantBuffer.Get(); }
        ID3D11Buffer* const* GetAddressOf() { return mConstantBuffer.GetAddressOf(); }

    public:
        static std::unique_ptr<ConstantBuffer> Create(void* aBuffer, float aAspectRatio);
        static std::unique_ptr<ConstantBuffer> Create(SOGE_CONSTANT_BUFFER_DESC aDescriptor);

    };
}

#endif // !SOGE_CONSTANT_BUFFER
