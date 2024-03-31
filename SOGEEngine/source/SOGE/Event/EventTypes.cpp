#include "sogepch.hpp"
#include "SOGE/Event/EventTypes.hpp"

#include <iomanip>

namespace soge
{
    void EventTypeID::GenerateID(const EventCategory aEventCategory, const std::string& aEventTypeName)
    {
        std::hash<std::string> hasher;
        mHash = hasher(aEventTypeName);

        std::stringstream ss;
        ss << std::setw(3) << std::setfill('0') << aEventCategory;
        std::string formatCategory = ss.str().c_str();
        mStringRepr = formatCategory + std::to_string(mHash).c_str();
    }

    EventTypeID::EventTypeID(const EventCategory aEventCategory, const std::string& aEventTypeName)
    {
        this->GenerateID(aEventCategory, aEventTypeName);
    }

    EventType::EventType(const std::string& aEventTypeName, const EventCategory aEventCategory)
        : mEventTypeName(aEventTypeName), mEventCategory(aEventCategory), mEventTypeID(aEventCategory, aEventTypeName)
    {
    }

    EventType::EventType(const EventType& aEventType)
        : mEventCategory(aEventType.mEventCategory), mEventTypeName(aEventType.mEventTypeName), mEventTypeID(aEventType.mEventTypeID)
    {
    }

}