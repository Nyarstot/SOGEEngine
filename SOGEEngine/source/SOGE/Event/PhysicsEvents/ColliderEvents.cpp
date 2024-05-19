#include "sogepch.hpp"
#include "SOGE/Event/PhysicsEvents/ColliderEvents.hpp"

namespace soge
{
    std::string CollidedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "ObjectCollided";
        return ss.str();
    }

    const char* CollidedEvent::ToCString() const
    {
        return this->ToString().c_str();
    }
}