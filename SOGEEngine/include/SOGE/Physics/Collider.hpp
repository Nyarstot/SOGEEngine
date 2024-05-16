#ifndef SOGE_COLLIDER_HPP
#define SOGE_COLLIDER_HPP

#include "SOGE/Containers/Simple.hpp"
#include "SOGE/Engine/EngineSetup.hpp"

#include <SimpleMath.h>
#include <d3d11.h>

namespace soge
{
    class Collider
    {
    private:
        std::unique_ptr<DirectX::BoundingBox> mBoundingBox;

    public:
        Collider(const Point2D& aCenter, const Point2D& aSize);
        ~Collider();

        bool Intersects(DirectX::FXMVECTOR aPlane);
        DirectX::BoundingBox* GetBoundingBox() { return mBoundingBox.get(); }

    public:
        static std::shared_ptr<Collider> CreateShared(const Point2D& aCenter, const Point2D& aSize);
        static std::unique_ptr<Collider> CreateUnique(const Point2D& aCenter, const Point2D& aSize);

    };
}

#endif // !SOGE_COLLIDER_HPP
