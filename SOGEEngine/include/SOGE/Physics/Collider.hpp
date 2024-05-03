#ifndef SOGE_COLLIDER_HPP
#define SOGE_COLLIDER_HPP

#include <SimpleMath.h>
#include <d3d11.h>

namespace soge
{
    class Collider
    {
    private:
        std::unique_ptr<DirectX::BoundingBox> mBoundingBox;

    public:


    };
}

#endif // !SOGE_COLLIDER_HPP
