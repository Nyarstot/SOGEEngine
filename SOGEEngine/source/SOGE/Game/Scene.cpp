#include "sogepch.hpp"
#include "SOGE/Game/Scene.hpp"
#include "SOGE/ECS/Entity.hpp"
#include "SOGE/Utils/UUID.hpp"


namespace soge
{
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(std::string aEntityTag)
    {
        Entity entity(mEntityRegistry->create(), this);
        entity.AddComponent<TagComponent>(aEntityTag);
        entity.AddComponent<UUIDComponent>(UUIDGenerator::GenerateUUID());
        return entity;
    }
}