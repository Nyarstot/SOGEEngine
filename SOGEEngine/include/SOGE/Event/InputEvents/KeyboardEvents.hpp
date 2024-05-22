#ifndef SOGE_KEYBOARD_EVENTS_HPP
#define SOGE_KEYBOARD_EVENTS_HPP

#include "SOGE/Event/Event.hpp"
#include "SOGE/Event/EventTypes.hpp"

namespace soge
{
    template<typename _Drvd>
    class KeyEventBase : public CompileTimeEvent<_Drvd>
    {
    protected:
        int mKeyCode;

    protected:
        KeyEventBase(int aKeyCode) : mKeyCode(aKeyCode) {
        }

    public:
        ~KeyEventBase() override = default;
        int GetKeyCode() const { return mKeyCode; }

    public:
        static int GetStaticCategoryFlag() { return EventCategory::InputEvent | EventCategory::KeyboardEvent; }

    };

    class KeyPressedEvent final : public KeyEventBase<KeyPressedEvent>
    {
    private:
        int mRepeatCount;

    public:
        KeyPressedEvent(int aKeyCode, int aRepeatCount)
            : KeyEventBase(aKeyCode), mRepeatCount(aRepeatCount)
        {
        }

        int GetRepeatCount() const { return mRepeatCount; }
        std::string ToString() const override;
        const char* ToCString() const override;


    public:
        static EventType GetStaticEventType() { return EventTypes::InputEvents::eKeyPressed; }
        static const char* GetStaticEventTypeName() { return EventTypes::InputEvents::eKeyPressed.GetCStringTypeName(); }

    };

    class KeyReleasedEvent final : public KeyEventBase<KeyReleasedEvent>
    {
    public:
        KeyReleasedEvent(int aKeyCode)
            : KeyEventBase(aKeyCode)
        {
        }

        std::string ToString() const override;
        const char* ToCString() const override;

    public:
        static EventType GetStaticEventType() { return EventTypes::InputEvents::eKeyReleased; }
        static const char* GetStaticEventTypeName() { return EventTypes::InputEvents::eKeyReleased.GetCStringTypeName(); }

    };
}

#endif // !SOGE_KEYBOARD_EVENTS_HPP
