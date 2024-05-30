#include "sogepch.hpp"
#include "SOGE/Game/GameObject.hpp"
#include "SOGE/Graphics/CircleSprite.hpp"

namespace soge
{
    GameObject::GameObject(const Point3D& aCenter, const Point3D& aSize, bool circle)
    {
        mObjectSprite = Sprite::CreateUnique(dxsmath::Vector2(aCenter.x, aCenter.y), dxsmath::Vector2(aSize.x, aSize.y ));
        if (circle == false) {
            mCircle = CircleSprite::CreateUnique(dxsmath::Vector2(aCenter.x, aCenter.y), dxsmath::Vector2(aSize.x + 0.05, aSize.y + 0.055));
        }

        mObjectCollider = Collider::CreateUnique(Point2D(aCenter.x, aCenter.y), Point2D(aSize.x, aSize.y));

        this->SetObjectName("defaultObjectName");
        mObjectCollider->SetOwner(this);
    }

    void GameObject::SetObjectName(std::string aObjectName)
    {
        mObjectName = aObjectName;
        mObjectCollider->SetColliderName(mObjectName + "_collider");
    }

    void GameObject::Move(Point3D aMoveTo)
    {
        mObjectSprite->Move(aMoveTo);
        if (circ == true) {
            mCircle->Move(aMoveTo);
        }

        mObjectCollider->Move(aMoveTo);
    }

    void GameObject::Translate(Point3D aTranslate)
    {
        mObjectSprite->Translate(aTranslate);
        if (circ == true) {
            mCircle->Translate(aTranslate);
        }

        mObjectCollider->Translate(aTranslate);
    }

    void GameObject::Scale(Point3D aScale)
    {
        mObjectSprite->Scale(aScale);
        if (circ == true) {
            mCircle->Scale(aScale);
        }
        //mObjectCollider->Scale(aScale);
    }

    void GameObject::Update(float aDeltaTime)
    {
        if (circ == true) {
            mCircle->Update(aDeltaTime);
            mCircle->Draw();
        }
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