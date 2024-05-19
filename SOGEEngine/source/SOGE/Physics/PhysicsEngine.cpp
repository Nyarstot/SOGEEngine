#include "sogepch.hpp"
#include "SOGE/Physics/PhysicsEngine.hpp"
#include "SOGE/Physics/Collider.hpp"

namespace soge
{
    PhysicsEngine* PhysicsEngine::sInstance = nullptr;
    PhysicsEngine* PhysicsEngine::GetInstance() {
        if (sInstance == nullptr) {
            sInstance = new PhysicsEngine();
        }

        return sInstance;
    }

    void PhysicsEngine::SetEventCallback(const fnEventCallback& aCallbackFunction)
    {
        mEventFunc = aCallbackFunction;
    }

    void PhysicsEngine::PushCollider(Collider* aCollider)
    {
        mColliderBuffer.emplace(mColliderBuffer.begin() + mCollisionInsertIndex, aCollider);
        mCollisionInsertIndex++;
    }

    void PhysicsEngine::PopCollider(Collider* aCollider)
    {
        auto it = std::find(mColliderBuffer.begin(), mColliderBuffer.end(), aCollider);
        if (it != mColliderBuffer.end()) {
            mColliderBuffer.erase(it);
            mCollisionInsertIndex--;
        }
    }

    void PhysicsEngine::CollisionTest(Collider* aCollider1, Collider* aCollider2)
    {
        if (!aCollider1->Intersects(aCollider2)) return;
        aCollider1->Collided(aCollider2);
        aCollider2->Collided(aCollider1);
    }
}