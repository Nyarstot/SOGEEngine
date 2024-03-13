#include "sogepch.hpp"
#include "SOGE/Containers/LayerStack.hpp"

namespace soge
{
    LayerStack::~LayerStack()
    {
        for (Layer* iLayer : mLayerBuffer) {
            delete iLayer;
        }
    }

    void LayerStack::PushLayer(Layer* aLayer)
    {
        mLayerBuffer.emplace(mLayerBuffer.begin() + mLayerInsertionIndex, aLayer);
        mLayerInsertionIndex++;
    }

    void LayerStack::PopLayer(Layer* aLayer)
    {
        auto it = std::find(mLayerBuffer.begin(), mLayerBuffer.end(), aLayer);
        if (it != mLayerBuffer.end()) {
            mLayerBuffer.erase(it);
            mLayerInsertionIndex--;
        }
    }

    void LayerStack::PushOverlay(Layer* aOverlayLayer)
    {
        mLayerBuffer.emplace_back(aOverlayLayer);
    }

    void LayerStack::PopOverlay(Layer* aOverlayLayer)
    {
        auto it = std::find(mLayerBuffer.begin(), mLayerBuffer.end(), aOverlayLayer);
        if (it != mLayerBuffer.end()) {
            mLayerBuffer.erase(it);
        }
    }

}