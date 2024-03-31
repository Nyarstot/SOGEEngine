#include "sogepch.hpp"
#include "SOGE/Event/InputEvents/KeyboardEvents.hpp"

namespace soge
{
    std::string KeyPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyPressedEvent " << mKeyCode << " pressed " << mRepeatCount << " times";
        return ss.str();
    }

    const char* KeyPressedEvent::ToCString() const
    {
        return ToString().c_str();
    }

    std::string KeyReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent " << mKeyCode << " released";
        return ss.str();
    }

    const char* KeyReleasedEvent::ToCString() const
    {
        return ToString().c_str();
    }
}