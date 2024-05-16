#ifndef SOGE_PHYSICS_ENGINE_HPP
#define SOGE_PHYSICS_ENGINE_HPP

#include "SOGE/Physics/Collider.hpp"
#include <SimpleMath.h>

namespace soge
{
    class PhysicsEngine final
    {
    private:

    protected:
        PhysicsEngine() = default;
        static PhysicsEngine* sInstance;

    public:
        PhysicsEngine(PhysicsEngine&)       = delete;
        void operator = (PhysicsEngine&)    = delete;

        void Update();
        void CollisionTest(Collider* aCollider1, Collider* aCollider2);

    public:
        static PhysicsEngine* GetInstance();

    };
}

#endif // !SOGE_PHYSICS_ENGINE_HPP
