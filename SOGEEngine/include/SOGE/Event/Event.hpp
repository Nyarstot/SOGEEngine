#ifndef SOGE_EVENT_HPP
#define SOGE_EVENT_HPP

#include "SOGE/Event/EventTypes.hpp"
#include <functional>
#include <string>

namespace soge
{
    class Event
    {
    private:
        bool mIsHandled = false;

    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const          = 0;
        virtual const char* GetEventTypeName() const    = 0;
        virtual int GetEventCategoryFlag() const        = 0;

        virtual std::string ToString() const    = 0;
        virtual const char* ToCString() const   = 0;

    public:
        bool IsHandled() const { return mIsHandled; }
        bool IsInCategory(EventCategory aEventCategory) {
            return GetEventCategoryFlag() & aEventCategory;
        }

    };

    template<typename _Drvd>
    class CompileTimeEvent : public Event
    {
    public:
        virtual ~CompileTimeEvent() = default;

        virtual EventType GetEventType() const override { return _Drvd::GetStaticEventType(); }
        virtual const char* GetEventTypeName() const override { return _Drvd::GetStaticEventTypeName(); }
        virtual int GetEventCategoryFlag() const override { return _Drvd::GetStaticCategoryFlag(); }

    };

    class EventDispatcher
    {
        template<typename _Ty>
        using eventFunction = std::function<bool(_Ty&)>;

    private:
        Event& mEvent;

    public:
        EventDispatcher(Event& aEvent) : mEvent(aEvent) {
        }

        template<typename _Ty, typename _Fn>
        bool Dispatch(const _Fn& aEventFunction) {
            if (mEvent.GetEventType() == _Ty::GetStaticEventType()) {
                mEvent.IsHandled() |= aEventFunction(static_cast<_Ty&>(mEvent));
                return true;
            }
            return false;
        }

    };

    template<typename _Ty>
    static inline constexpr _Ty& StaticEventCast(Event& aEvent) {
        return static_cast<_Ty&>(aEvent);
    }
}

#endif // !SOGE_EVENT_HPP
