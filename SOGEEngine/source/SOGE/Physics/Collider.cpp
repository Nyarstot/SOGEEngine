#include "sogepch.hpp"
#include "SOGE/Physics/Collider.hpp"
#include "SOGE/Event/PhysicsEvents/ColliderEvents.hpp"
#include "SOGE/Physics/PhysicsEngine.hpp"


namespace soge
{
    Collider::Collider(const Point2D& aCenter, const Point2D& aSize, std::string aName)
    {
        mBoundingBox = std::make_shared<DirectX::BoundingBox>(dxsmath::Vector3(aCenter), dxsmath::Vector3(aSize));
        mColliderName = aName;
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
        //if (mWindowMessage.message == WM_KEYDOWN) {
        //    KeyPressedEvent fnEvent(mWindowMessage.wParam, 1);
        //    mEventCallbackFunction(fnEvent);
        //}
    }

    void Collider::Translate(Point3D aTranslate)
    {
        mBoundingBox->Center.x += aTranslate.x;
        mBoundingBox->Center.y += aTranslate.y;
        mBoundingBox->Center.z += aTranslate.z;

        /*SOGE_APP_INFO_LOG("Bounding box: {0}, {1}, {2}", mBoundingBox->Center.x, mBoundingBox->Center.y, mBoundingBox->Center.z);*/
    }

    std::shared_ptr<Collider> Collider::CreateShared(const Point2D& aCenter, const Point2D& aSize, std::string aName)
    {
        return std::make_shared<Collider>(aCenter, aSize, aName);
    }

    std::unique_ptr<Collider> Collider::CreateUnique(const Point2D& aCenter, const Point2D& aSize, std::string aName)
    {
        return std::make_unique<Collider>(aCenter, aSize, aName);
    }
}