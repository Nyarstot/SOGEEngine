#ifndef SOGE_ENGINE_COMPONENT_HPP
#define SOGE_ENGINE_COMPONENT_HPP

#include <winerror.h>

namespace soge
{
    class EngineComponent
    {
    public:
        virtual ~EngineComponent() = default;
        virtual HRESULT InitComponent() = 0;

    };
}

#endif // !SOGE_ENGINE_COMPONENT_HPP
