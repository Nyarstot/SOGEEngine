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
        std::shared_ptr<DirectX::BoundingBox> mBoundingBox;
        std::string mColliderName = "default";

    public:
        Collider(const Point2D& aCenter, const Point2D& aSize, std::string aName);
        ~Collider();

        bool Intersects(Collider* aCollider);
        void Collided(Collider* aCollidedWith);
        DirectX::BoundingBox& GetBoundingBox() { return *mBoundingBox.get(); }

        std::string GetName() const { return mColliderName; }
        void SetName(std::string aName) { mColliderName = aName; }

    public:
        static std::shared_ptr<Collider> CreateShared(const Point2D& aCenter, const Point2D& aSize, std::string aName);
        static std::unique_ptr<Collider> CreateUnique(const Point2D& aCenter, const Point2D& aSize, std::string aName);

    };
}

#endif // !SOGE_COLLIDER_HPP
