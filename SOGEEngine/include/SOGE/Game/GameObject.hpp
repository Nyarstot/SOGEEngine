#ifndef SOGE_GAME_OBJECT_HPP
#define SOGE_GAME_OBJECT_HPP

#include "SOGE/Graphics/Sprite.hpp"
#include "SOGE/Physics/Collider.hpp"
#include "SOGE/Containers/Simple.hpp"

namespace soge
{
    class GameObject
    {
    protected:
        std::unique_ptr<Sprite> mObjectSprite;
        std::unique_ptr<Collider> mObjectCollider;

    public:
        GameObject() = default;
        GameObject(const Point3D& aCenter, const Point3D& aSize);
        ~GameObject() = default;

        Sprite* GetSprite() const { return mObjectSprite.get(); }
        Collider* GetCollision() const { return mObjectCollider.get(); }
        void MoveTo(Point3D aMoveCoord);

        virtual void Update(float aDeltaTime) {};
        virtual void Collide(Collider* aCollider) {};

    public:
        static std::shared_ptr<GameObject> CreateShared(const Point3D& aCenter, const Point3D& aSize);
        static std::unique_ptr<GameObject> CreateUnique(const Point3D& aCenter, const Point3D& aSize);

    };
}

#endif // !SOGE_GAME_OBJECT_HPP
