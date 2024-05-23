#ifndef SOGE_COLLIDER_HPP
#define SOGE_COLLIDER_HPP

#include "SOGE/Containers/Simple.hpp"
#include "SOGE/Engine/EngineSetup.hpp"

#include <SimpleMath.h>
#include <d3d11.h>

namespace soge
{
    class GameObject;

    class Collider
    {

    private:
        std::shared_ptr<DirectX::BoundingBox> mBoundingBox;
        std::string mColliderName = "default";
        GameObject* mOwner;

    public:
        Collider(const Point2D& aCenter, const Point2D& aSize);
        ~Collider();

        bool Intersects(Collider* aCollider);
        void Collided(Collider* aCollidedWith);
        DirectX::BoundingBox& GetBoundingBox() { return *mBoundingBox.get(); }

        void Translate(Point3D aTranslate);
        void Move(Point3D aMoveTo);

        std::string GetColliderName() const { return mColliderName; }
        void SetColliderName(std::string aName) { mColliderName = aName; }
        GameObject* GetOwner() const { return mOwner; }
        void SetOwner(GameObject* aOwner) { mOwner = aOwner; }

    public:
        static std::shared_ptr<Collider> CreateShared(const Point2D& aCenter, const Point2D& aSize);
        static std::unique_ptr<Collider> CreateUnique(const Point2D& aCenter, const Point2D& aSize);

    };
}

#endif // !SOGE_COLLIDER_HPP
