#ifndef SOGE_GRAPHICS_INTERFACES_HPP
#define SOGE_GRAPHICS_INTERFACES_HPP

#include "SOGE/Containers/Simple.hpp"
#include <d3d11.h>

namespace soge
{
    class IShaderEnabled
    {
    protected:
        virtual void RSStage(ID3D11DeviceContext* aContext) = 0;
        virtual void IAStage(ID3D11DeviceContext* aContext) = 0;
        virtual void VSStage(ID3D11DeviceContext* aContext) = 0;
        virtual void PSStage(ID3D11DeviceContext* aContext) = 0;

    public:
        virtual ~IShaderEnabled() = default;
        virtual void Draw() = 0;
        virtual void Update(float aDeltaTime) = 0;
        virtual void Transform(Point3D aTranslate, Point3D aRotate, Point3D aScale) = 0;

    };
}

#endif // !SOGE_GRAPHICS_INTERFACES_HPP
