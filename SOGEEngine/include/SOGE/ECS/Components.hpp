#ifndef SOGE_GAME_COMPONENTS_HPP
#define SOGE_GAME_COMPONENTS_HPP

#include "SOGE/Game/Transform.hpp"

#include <string>
#include <uuid_v4/uuid_v4.hpp>

namespace soge
{
    struct TagComponent
    {
        std::string tag;
    };

    struct UUIDComponent
    {
        UUIDv4::UUID uuid;
    };

    struct TransformComponent
    {

    };
}

#endif // !SOGE_GAME_COMPONENTS_HPP
