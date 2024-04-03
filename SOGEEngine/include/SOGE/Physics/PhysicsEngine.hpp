#ifndef SOGE_PHYSICS_ENGINE_HPP
#define SOGE_PHYSICS_ENGINE_HPP

#include "SOGE/ComponentSystem/PhysicsComponents/PhysicsComponent.hpp"

namespace soge
{
    class PhysicsEngine final : public PhysicsComponent
    {
    private:


    protected:
        PhysicsEngine() = default;
        static PhysicsEngine* sInstance;

    public:
        PhysicsEngine(PhysicsEngine&)       = delete;
        void operator = (PhysicsEngine&)    = delete;

        void Update() override;

    public:
        static PhysicsEngine* GetInstance();

    };
}

#endif // !SOGE_PHYSICS_ENGINE_HPP
