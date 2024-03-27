#ifndef SOGE_RENDERABLE_COMPONENT_HPP
#define SOGE_RENDERABLE_COMPONENT_HPP

#include "SOGE/ComponentSystem/GraphicsComponents/GraphicsComponent.hpp"
#include <d3d11.h>

namespace soge
{
    class RenderableComponent : public GraphicsComponent
    {
    protected:
        virtual void RSStage(ID3D11DeviceContext* aContext) = 0;
        virtual void IAStage(ID3D11DeviceContext* aContext) = 0;
        virtual void VSStage(ID3D11DeviceContext* aContext) = 0;
        virtual void PSStage(ID3D11DeviceContext* aContext) = 0;

    public:
        virtual ~RenderableComponent() = default;

        virtual void PreRenderStage(ID3D11DeviceContext* aContext)  = 0;
        virtual void Draw(ID3D11DeviceContext* aContext)            = 0;

    };
}

#endif // !SOGE_RENDERABLE_COMPONENT_HPP
