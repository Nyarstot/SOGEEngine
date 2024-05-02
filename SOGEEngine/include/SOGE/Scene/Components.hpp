#ifndef SOGE_COMPONENTS_HPP
#define SOGE_COMPONENTS_HPP

#include "SOGE/Engine/EngineSetup.hpp"

namespace soge
{
    struct TransformComponent
    {
        dxsmath::Vector4 transform;

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const dxsmath::Vector4& aTransform)
            : transform(aTransform) {}

        operator dxsmath::Vector4& () { return transform; }
        operator const dxsmath::Vector4& () const { return transform; }
    };
}

#endif // !SOGE_COMPONENTS_HPP
