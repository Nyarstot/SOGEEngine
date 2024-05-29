#include "sogepch.hpp"
#include "SOGE/Game/Scene.hpp"
#include "SOGE/Game/Entity.hpp"


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
        return entity;
    }
}