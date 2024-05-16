#ifndef SOGE_ACTOR_HPP
#define SOGE_ACTOR_HPP

#include "SOGE/Graphics/Sprite.hpp"
#include "SOGE/Physics/Collider.hpp"
#include "SOGE/Containers/Simple.hpp"
#include "SOGE/Game/GameObject.hpp"

namespace soge
{
    class Actor
    {
    private:
        std::unique_ptr<GameObject> mGameObject;

    public:
        Actor(GameObject* aGameObject);
        ~Actor();

    public:

    };
}

#endif // !SOGE_ACTOR_HPP
