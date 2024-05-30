#include "sogepch.hpp"
#include "SOGE/Physics/Collider.hpp"
#include "SOGE/Event/PhysicsEvents/ColliderEvents.hpp"
#include "SOGE/Physics/PhysicsEngine.hpp"


namespace soge
{
    Collider::Collider(const Point2D& aCenter, const Point2D& aSize)
    {
        mBoundingBox = std::make_shared<DirectX::BoundingBox>(dxsmath::Vector3(aCenter), dxsmath::Vector3(aSize));
    }

    Collider::~Collider()
    {
        mBoundingBox.reset();
    }

    bool Collider::Intersects(Collider* aCollider)
    {
        return mBoundingBox->Intersects(aCollider->GetBoundingBox());
    }

    void Collider::Collided(Collider* aCollidedWith)
    {

    }

    void Collider::Translate(Point3D aTranslate)
    {
        mBoundingBox->Center.x += aTranslate.x;
        mBoundingBox->Center.y += aTranslate.y;
        mBoundingBox->Center.z += aTranslate.z;
    }

    void Collider::Scale(Point3D aScale)
    {
        dx::FXMVECTOR vec = dx::FXMVECTOR({ 0 });
        mBoundingBox->Transform(*mBoundingBox.get(), aScale.y, vec, vec);
    }

    void Collider::Move(Point3D aMoveTo)
    {
        mBoundingBox->Center.x = aMoveTo.x;
        mBoundingBox->Center.y = aMoveTo.y;
        mBoundingBox->Center.z = aMoveTo.z;
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