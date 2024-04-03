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
}