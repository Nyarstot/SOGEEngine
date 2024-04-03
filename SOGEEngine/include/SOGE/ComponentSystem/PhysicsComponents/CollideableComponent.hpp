#ifndef SOGE_COLLIDEABLE_COMPONENT_HPP
#define SOGE_COLLIDEABLE_COMPONENT_HPP

#include "SOGE/ComponentSystem/PhysicsComponents/PhysicsComponent.hpp"

namespace soge
{
    class CollideableComponent : public PhysicsComponent
    {
        using CComponent = CollideableComponent;

    public:
        virtual ~CollideableComponent() = default;

        virtual bool IsCollide(CComponent* aCollideable)    = 0;
        virtual void OnCollide()                            = 0;
    };
}

#endif // !SOGE_COLLIDEABLE_COMPONENT_HPP
