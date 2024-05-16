#include "sogepch.hpp"
#include "SOGE/Physics/Collider.hpp"


namespace soge
{
    Collider::Collider(const Point2D& aCenter, const Point2D& aSize)
    {
        mBoundingBox = std::make_unique<DirectX::BoundingBox>(dxsmath::Vector3(aCenter), dxsmath::Vector3(aSize));
    }

    Collider::~Collider()
    {
        mBoundingBox.release();
    }

    bool Collider::Intersects(DirectX::FXMVECTOR aPlane)
    {
        return mBoundingBox->Intersects(aPlane);
    }

    std::shared_ptr<Collider> Collider::CreateShared(const Point2D& aCenter, const Point2D& aSize)
    {
        return std::make_shared<Collider>(aCenter, aSize);
    }

    std::unique_ptr<Collider> Collider::CreateUnique(const Point2D& aCenter, const Point2D& aSize)
    {
        return std::make_unique<Collider>(aCenter, aSize);
    }
}