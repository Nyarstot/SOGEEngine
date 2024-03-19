#ifndef SOGE_VERTEX_HPP
#define SOGE_VERTEX_HPP

#include "SOGE/Engine/EngineSetup.hpp"

namespace soge
{
    struct Vertex
    {
        DirectX::XMFLOAT4 position;
        DirectX::XMFLOAT4 color;
    };
}

#endif // !SOGE_VERTEX_HPP
