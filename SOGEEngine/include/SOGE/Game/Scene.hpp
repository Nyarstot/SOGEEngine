#ifndef SOGE_SCENE_HPP
#define SOGE_SCENE_HPP

#include "SOGE/Game/Components.hpp"
#include <entt/entt.hpp>

namespace soge
{
    class Scene
    {
        friend class Entity;

    private:
        std::unique_ptr<entt::registry> mEntityRegistry;

    public:
        Scene();
        ~Scene();

        Entity CreateEntity(std::string aEntityTag);

    };
}

#endif // !SOGE_SCENE_HPP
