#ifndef SOGE_PHYSICS_ENGINE_HPP
#define SOGE_PHYSICS_ENGINE_HPP

#include "SOGE/Event/Event.hpp"
#include "SOGE/Event/PhysicsEvents/ColliderEvents.hpp"

namespace soge
{
    class PhysicsEngine final
    {
        friend class Collider;

        using fnEventCallback = std::function<void(Event&)>;

    private:
        fnEventCallback mEventFunc;
        std::vector<Collider*> mColliderBuffer;
        int mCollisionInsertIndex = 0;

    protected:
        PhysicsEngine() = default;
        static PhysicsEngine* sInstance;

    public:
        PhysicsEngine(PhysicsEngine&)       = delete;
        void operator = (PhysicsEngine&)    = delete;

        void SetEventCallback(const fnEventCallback& aCallbackFunction);
        void PushCollider(Collider* aCollider);
        void PopCollider(Collider* aCollider);
        void CollisionTest(Collider* aCollider1, Collider* aCollider2);

    public:
        static PhysicsEngine* GetInstance();

    };
}

#endif // !SOGE_PHYSICS_ENGINE_HPP
