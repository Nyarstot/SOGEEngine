#ifndef SOGE_GRAPHICS_COMPONENT_HPP
#define SOGE_GRAPHICS_COMPONENT_HPP

#include "SOGE/ComponentSystem/EngineComponent.hpp"

namespace soge
{
    class GraphicsComponent : public EngineComponent
    {
    public:
        virtual ~GraphicsComponent() = default;

    };
}

#endif // !SOGE_GRAPHICS_COMPONENT_HPP
