#ifndef SOGE_ENTITY_HPP
#define SOGE_ENTITY_HPP

#include "SOGE/Game/Scene.hpp"
#include <entt/entt.hpp>

namespace soge
{
    class Entity
    {
    private:
        entt::entity mEntityHandle;
        Scene* mScene = nullptr;

    protected:

    public:
        Entity();
        Entity(entt::entity aEntity, Scene* aScenePtr);
        ~Entity();

        /**
        * @brief adds component to the entity
        * @returns added component of _Ty type
        * @example struct Position { float x, float y; }; entity.AddComponent<Position>(0.0f, 10.0f);
        **/
        template<typename _Ty, typename... _Args>
        _Ty& AddComponent(_Args&&... aArgs)
        {
            if (this->HasComponent<_Ty>()) {
                SOGE_WARN_LOG("Entity already has given component");
            }

            _Ty& component = mScene->mEntityRegistry->emplace<_Ty>(mEntityHandle, std::forward<_Args>(aArgs)...);
            // TODO: add onComponentAdded event
            return component;
        }

        template<typename _Ty, typename... _Args>
        _Ty& EmplaceOrReplaceComponent(_Args&&... aArgs)
        {
            _Ty& component = mScene->mEntityRegistry->emplace_or_replace<_Ty>(mEntityHandle, std::forward<_Args>(aArgs)...);
            // TODO: add onComponentAdded event
            return component;
        }

        template<typename _Ty>
        bool HasComponent()
        {
            return mScene->mEntityRegistry->any_of<_Ty>(mEntityHandle);
        }

        template<typename _Ty>
        _Ty& GetComponent()
        {
            if (!this->HasComponent<_Ty>()) {
                SOGE_ERROR_LOG("Entity doesn't have given component");
            }
            return mScene->mEntityRegistry->get<_Ty>(mEntityHandle);
        }

        template<typename _Ty>
        void RemoveComponent()
        {
            if (!this->HasComponent<_Ty>()) {
                SOGE_ERROR_LOG("Entity doesn't have given component");
            }
            this->mScene->mEntityRegistry->remove<_Ty>(mEntityHandle);
        }

    };
}

#endif // !SOGE_ENTITY_HPP
