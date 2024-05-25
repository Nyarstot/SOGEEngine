#include "sogepch.hpp"
#include "SOGE/Graphics/SpriteBatch.hpp"


namespace soge
{
    SpriteBatch::SpriteBatch(ID3D11DeviceContext* aDeviceContext)
    {
        mDTKSpriteBatch = std::make_unique<dx::SpriteBatch>(aDeviceContext);
    }

    SpriteBatch::~SpriteBatch()
    {
        mDTKSpriteBatch.release();
    }

    void SpriteBatch::Begin(SpriteBatchDescriptor& aBatchDescriptor)
    {
        auto sortMode = static_cast<dtkBatch::SpriteSortMode>((int)aBatchDescriptor.sortMode);

        mDTKSpriteBatch->Begin(
            sortMode,
            aBatchDescriptor.blendState,
            aBatchDescriptor.samplerState,
            aBatchDescriptor.depthStencilState,
            aBatchDescriptor.rasterizerState,
            aBatchDescriptor.setCustomShaders
        );
    }

    void SpriteBatch::End()
    {
        mDTKSpriteBatch->End();
    }

    std::shared_ptr<SpriteBatch> SpriteBatch::CreateShared(ID3D11DeviceContext* aDeviceContext)
    {
        return std::make_shared<SpriteBatch>(aDeviceContext);
    }

    std::unique_ptr<SpriteBatch> SpriteBatch::CreateUnique(ID3D11DeviceContext* aDeviceContext)
    {
        return std::make_unique<SpriteBatch>(aDeviceContext);
    }
}