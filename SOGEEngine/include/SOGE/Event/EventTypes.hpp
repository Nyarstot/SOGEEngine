#ifndef SOGE_EVENT_TYPES_HPP
#define SOGE_EVENT_TYPES_HPP

namespace soge
{
    ////////////////////////////////
    // Event type internal classes
    ////////////////////////////////

    #define BIT(x) 1 << (x)

    enum EventCategory : int
    {
        None                = 0,
        ApplicationEvent    = BIT(0),
        InputEvent          = BIT(1),
        KeyboardEvent       = BIT(2),
        MouseEvent          = BIT(3),
        FloatingMouseEvent  = BIT(4),
        GamepadEvent        = BIT(5),
        GameplayEvents      = BIT(6)
    };

    class EventTypeID final
    {
    private:
        std::size_t     mHash;
        std::string     mStringRepr;

    protected:
        void GenerateID(const EventCategory aEventCategory, const std::string& aEventTypeName);

    public:
        EventTypeID(const EventCategory aEventCategory, const std::string& aEventTypeName);
        ~EventTypeID() = default;

        std::size_t GetHash() const { return mHash; }
        std::string ToString() const { return mStringRepr; }

    public:
        bool operator == (const EventTypeID& aEventTypeID) {
            return aEventTypeID.GetHash() == mHash;
        }

    };

    class EventType final
    {
    private:
        std::string mEventTypeName;
        EventCategory mEventCategory;
        EventTypeID mEventTypeID;

    public:
        EventType(const std::string& aEventTypeName, const EventCategory aEventCategory);
        EventType(const EventType& aEventType);
        ~EventType() = default;

        const char* GetCStringTypeName() const { return mEventTypeName.c_str(); }
        std::string GetTypeName() const { return mEventTypeName; }
        EventCategory GetEventCategory() const { return mEventCategory; }
        EventTypeID GetEventTypeID() const { return mEventTypeID; }

    public:
        bool operator == (const EventType& aOtherEvent) {
            return mEventTypeID == aOtherEvent.GetEventTypeID();
        }

    };

    ////////////////////////////////
    // Global event types
    ////////////////////////////////

    namespace EventTypes
    {
        namespace InputEvents
        {
            inline const EventType eKeyPressed("KeyPressed", EventCategory::InputEvent);
            inline const EventType eKeyReleased("KeyReleased", EventCategory::InputEvent);
        }

        namespace GameplayEvents
        {
            inline const EventType eObjectCollided("ObjectCollided", EventCategory::GameplayEvents);
        }
    }
}

#endif // !SOGE_EVENT_TYPES_HPP
