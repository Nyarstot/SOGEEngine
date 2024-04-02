#ifndef SOGE_COLLIDEABLE_COMPONENT_HPP
#define SOGE_COLLIDEABLE_COMPONENT_HPP

#include "SOGE/ComponentSystem/PhysicsComponents/PhysicsComponent.hpp"

namespace soge
{
    class CollideableComponent : public PhysicsComponent
    {
    public:
        virtual ~CollideableComponent() = default;

    };
}

#endif // !SOGE_COLLIDEABLE_COMPONENT_HPP
