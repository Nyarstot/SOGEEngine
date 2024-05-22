#include "sogepch.hpp"
#include "SOGE/Game/GameObject.hpp"

namespace soge
{
    GameObject::GameObject(const Point3D& aCenter, const Point3D& aSize)
    {
        mObjectName = "gameObject";
        std::string colliderName = mObjectName + " _collider";

        mObjectSprite = Sprite::CreateUnique(dxsmath::Vector2(aCenter.x, aCenter.y), dxsmath::Vector2(aSize.x, aSize.y));
        mObjectCollider = Collider::CreateUnique(Point2D(aCenter.x, aCenter.y), Point2D(aSize.x, aSize.y), colliderName);
    }

    void GameObject::Translate(Point3D aTranslate)
    {
        mObjectSprite->Translate(aTranslate);
        mObjectCollider->Translate(aTranslate);
    }

    void GameObject::Update(float aDeltaTime)
    {

    }

    std::shared_ptr<GameObject> GameObject::CreateShared(const Point3D& aCenter, const Point3D& aSize)
    {
        return std::make_shared<GameObject>(aCenter, aSize);
    }

    std::unique_ptr<GameObject> GameObject::CreateUnique(const Point3D& aCenter, const Point3D& aSize)
    {
        return std::make_unique<GameObject>(aCenter, aSize);
    }
}