#ifndef SOGE_COLLIDER_EVENTS_HPP
#define SOGE_COLLIDER_EVENTS_HPP

#include "SOGE/Event/Event.hpp"
#include "SOGE/Event/EventTypes.hpp"
#include "SOGE/Physics/Collider.hpp"

namespace soge
{
    template<typename _Drvd>
    class CollideEventBase : public CompileTimeEvent<_Drvd>
    {
    protected:
        Collider* mCollidedObject;

    protected:
        CollideEventBase(Collider* aCollidedObject) : mCollidedObject(aCollidedObject) {};

    public:
        ~CollideEventBase() override = default;
        Collider* GetColliderObject() const { return mCollidedObject; }

    public:
        static int GetStaticCategoryFlag() { return EventCategory::GameplayEvents; }

    };

    class CollidedEvent final : public CollideEventBase<CollidedEvent>
    {
    public:
        CollidedEvent(Collider* aCollidedObject) : CollideEventBase(aCollidedObject) {};
        ~CollidedEvent() override = default;

        Collider* GetCollidedObject() const { return mCollidedObject; }
        std::string ToString() const override;
        const char* ToCString() const override;

    public:
        static EventType GetStaticEventType() { return EventTypes::GameplayEvents::eObjectCollided; }
        static const char* GetStaticEventTypeName() { return EventTypes::GameplayEvents::eObjectCollided.GetCStringTypeName(); }

    };
}

#endif // !SOGE_COLLIDER_EVENTS_HPP
