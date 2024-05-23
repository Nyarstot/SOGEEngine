#ifndef SOGE_SPRITE_BATCH_HPP
#define SOGE_SPRITE_BATCH_HPP

#include "SOGE/Engine/EngineSetup.hpp"
#include <SpriteBatch.h> // DirectXTK SpriteBatch

namespace dtkBatch = DirectX::DX11;

namespace soge
{
    enum SpriteSortMode
    {
        SpriteSortMode_Deferred,
        SpriteSortMode_Immediate,
        SpriteSortMode_Texture,
        SpriteSortMode_BackToFront,
        SpriteSortMode_FrontToBack
    };

    struct BatchDesc
    {
        SpriteSortMode sortMode = SpriteSortMode::SpriteSortMode_Deferred;
        ID3D11BlendState* blendState                            = nullptr;
        ID3D11SamplerState* samplerState                        = nullptr;
        ID3D11DepthStencilState* depthStencilState              = nullptr;
        ID3D11RasterizerState* rasterizerState                  = nullptr;
        std::function<void __cdecl()> setCustomShaders          = nullptr;
    };

    class SpriteBatch
    {
    private:
        std::unique_ptr<dx::SpriteBatch> mDTKSpriteBatch;

    public:
        SpriteBatch(ID3D11DeviceContext* aDeviceContext);
        ~SpriteBatch();

        dx::SpriteBatch* GetNative() const { return mDTKSpriteBatch.get(); }
        void Begin(BatchDesc aBatchDescriptor);
        void End();

    public:
        static std::shared_ptr<SpriteBatch> CreateShared(ID3D11DeviceContext* aDeviceContext);
        static std::unique_ptr<SpriteBatch> CreateUnique(ID3D11DeviceContext* aDeviceContext);

    };
}

#endif // !SOGE_SPRITE_BATCH_HPP
