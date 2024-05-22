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
        Collider* mCollidedObject1;
        Collider* mCollidedObject2;

    protected:
        CollideEventBase(Collider* aCollidedObject1, Collider* aCollidedObject2) 
            : mCollidedObject1(aCollidedObject1), mCollidedObject2(aCollidedObject2) {};

    public:
        ~CollideEventBase() override = default;
        Collider* GetColliderObject1() const { return mCollidedObject1; }
        Collider* GetColliderObject2() const { return mCollidedObject2; }

    public:
        static int GetStaticCategoryFlag() { return EventCategory::GameplayEvents; }

    };

    class CollidedEvent final : public CollideEventBase<CollidedEvent>
    {
    public:
        CollidedEvent(Collider* aCollidedObject1, Collider* aCollidedObject2) 
            : CollideEventBase(aCollidedObject1, aCollidedObject2) {};
        ~CollidedEvent() override = default;

        std::string ToString() const override;
        const char* ToCString() const override;

    public:
        static EventType GetStaticEventType() { return EventTypes::GameplayEvents::eObjectCollided; }
        static const char* GetStaticEventTypeName() { return EventTypes::GameplayEvents::eObjectCollided.GetCStringTypeName(); }

    };
}

#endif // !SOGE_COLLIDER_EVENTS_HPP
