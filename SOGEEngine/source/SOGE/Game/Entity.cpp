#include "sogepch.hpp"
#include "SOGE/Game/Entity.hpp"


namespace soge
{
    Entity::Entity()
    {
        mEntityHandle = {};
        mScene = nullptr;
    }

    //Entity::Entity(const Entity& aCopy)
    //{
    //    auto entity = std::move(aCopy.GetEntt());
    //    mEntityHandle = std::make_unique<entt::entity>(std::move(entity));
    //    aCopy.mEntityHandle.get_deleter();
    //    mScene = aCopy.mScene;
    //}

    Entity::Entity(entt::entity aEntity, Scene* aScenePtr)
    {
        mEntityHandle = aEntity;
        mScene = aScenePtr;
    }

    Entity::~Entity()
    {

    }
}