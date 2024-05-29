#include "sogepch.hpp"
#include "SOGE/Utils/UUID.hpp"


namespace soge
{
    UUIDv4::UUID UUIDGenerator::GenerateUUID()
    {
        return mUUIDGenerator.getUUID();
    }
}