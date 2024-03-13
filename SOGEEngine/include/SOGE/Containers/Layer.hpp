#ifndef SOGE_LAYER_HPP
#define SOGE_LAYER_HPP

#include <string>

namespace soge
{
    class Layer
    {
    protected:
        std::string mLayerName;

    public:
        Layer(const std::string& aLayerName = "DefaultLayerName");
        virtual ~Layer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate() {};

        const std::string& GetName() const { return mLayerName; }

    };
}

#endif // !SOGE_LAYER_HPP
