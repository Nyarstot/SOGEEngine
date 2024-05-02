#include "sogepch.hpp"
#include "SOGE/Scene/Scene.hpp"

namespace soge
{
    Scene::Scene()
    {
        mRegistry = std::make_unique<entt::registry>();
        entt::entity entity = mRegistry->create();
        auto& transform = mRegistry->emplace<TransformComponent>(entity, dxsmath::Vector4(1.0f));
    }

    Scene::~Scene()
    {

    }
}