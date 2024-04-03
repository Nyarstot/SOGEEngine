#ifndef SOGE_PHYSICS_COMPONENT_HPP
#define SOGE_PHYSICS_COMPONENT_HPP

#include "SOGE/ComponentSystem/EngineComponent.hpp"

namespace soge
{
    class PhysicsComponent : public EngineComponent
    {
    public:
        virtual ~PhysicsComponent() = default;
        virtual void Update()   = 0;
    };
}

#endif // !SOGE_PHYSICS_COMPONENT_HPP
