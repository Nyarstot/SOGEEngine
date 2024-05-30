#include "sogepch.hpp"
#include "SOGE/ECS/Entity.hpp"


namespace soge
{
    Entity::Entity()
    {
        mEntityHandle = {};
        mScene = nullptr;
    }

    Entity::Entity(entt::entity aEntity, Scene* aScenePtr)
    {
        mEntityHandle = aEntity;
        mScene = aScenePtr;
    }

    Entity::~Entity()
    {

    }
}