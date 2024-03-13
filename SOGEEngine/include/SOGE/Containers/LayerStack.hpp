#ifndef SOGE_LAYER_STACK_HPP
#define SOGE_LAYER_STACK_HPP

#include "SOGE/Containers/Layer.hpp"
#include <vector>

namespace soge
{
    class LayerStack
    {
    private:
        std::vector<Layer*> mLayerBuffer;
        unsigned mLayerInsertionIndex = 0;

    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* aLayer);
        void PopLayer(Layer* aLayer);

        void PushOverlay(Layer* aOverlayLayer);
        void PopOverlay(Layer* aOverlayLayer);

        std::vector<Layer*>::iterator begin() { return mLayerBuffer.begin(); }
        std::vector<Layer*>::iterator end() { return mLayerBuffer.end(); }

    };
}

#endif // !SOGE_LAYER_STACK_HPP
