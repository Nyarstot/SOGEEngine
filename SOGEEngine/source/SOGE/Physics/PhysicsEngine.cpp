#include "sogepch.hpp"
#include "SOGE/Physics/PhysicsEngine.hpp"

namespace soge
{
    PhysicsEngine* PhysicsEngine::sInstance = nullptr;
    PhysicsEngine* PhysicsEngine::GetInstance() {
        if (sInstance == nullptr) {
            sInstance = new PhysicsEngine();
        }

        return sInstance;
    }

    void PhysicsEngine::Update()
    {

    }

    void PhysicsEngine::CollisionTest(Collider* aCollider1, Collider* aCollider2)
    {
        if (!aCollider1->Intersects(aCollider2)) return;
    }
}