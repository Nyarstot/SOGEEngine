#ifndef SOGE_COLLIDE_EVENTS_HPP
#define SOGE_COLLIDE_EVENTS_HPP

#include "SOGE/Event/Event.hpp"
#include "SOGE/Event/EventTypes.hpp"

namespace soge
{
    template<typename _Drvd>
    class CollideEventBase : public CompileTimeEvent<_Drvd>
    {
    protected:
        // Object collidedObject

    protected:
        CollideEventBase(){
        }

    public:
        ~CollideEventBase() override = default;
        int GetKeyCode() const { return mKeyCode; }
        // Object GetCollidedObject() const { return mCollidedObject; }

    public:
        static int GetStaticCategoryFlag() { return EventCategory::ApplicationEvent }

    };
}

#endif // !SOGE_COLLIDE_EVENTS_HPP
