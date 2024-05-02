#ifndef SOGE_SCENE_HPP
#define SOGE_SCENE_HPP

#include "SOGE/Scene/Components.hpp"
#include <entt/entt.hpp>

namespace soge
{
    class Scene
    {
    private:
        std::unique_ptr<entt::registry> mRegistry;

    public:
        Scene();
        ~Scene();

    };
}

#endif // !SOGE_SCENE_HPP
