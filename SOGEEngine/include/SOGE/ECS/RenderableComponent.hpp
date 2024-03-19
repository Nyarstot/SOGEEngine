#ifndef SOGE_RENDERABLE_COMPONENT_HPP
#define SOGE_RENDERABLE_COMPONENT_HPP

#include "SOGE/ECS/ComponentBase.hpp"

namespace soge
{
    class RenderableComponent : public ComponentBase
    {
    public:
        ~RenderableComponent() = default;

        virtual void Render() = 0;
        virtual void Destroy() = 0;

    };
}

#endif // !SOGE_RENDERABLE_COMPONENT_HPP
