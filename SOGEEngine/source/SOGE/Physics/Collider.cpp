#include "sogepch.hpp"
#include "SOGE/Physics/Collider.hpp"


namespace soge
{
    Collider::Collider(const Point2D& aCenter, const Point2D& aSize)
    {
        //mBoundingBox = std::make_unique<DirectX::BoundingBox>(dxsmath::Vector3(aCenter), dxsmath::Vector3(aSize));
        mBoundingBox = std::make_shared<DirectX::BoundingBox>(dxsmath::Vector3(aCenter), dxsmath::Vector3(aSize));
            //DirectX::FXMVECTOR aPlane
    }

    Collider::~Collider()
    {
        //mBoundingBox.release();
        mBoundingBox.reset();
    }

    bool Collider::Intersects(Collider* aOtherCollider)
    {
        return mBoundingBox->Intersects(*aOtherCollider->GetBoundingBox());
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