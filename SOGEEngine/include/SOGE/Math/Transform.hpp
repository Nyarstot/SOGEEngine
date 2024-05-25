#ifndef SOGE_TRANSFORM_HPP
#define SOGE_TRANSFORM_HPP

#include "SOGE/Containers/Simple.hpp"

namespace soge
{
    class Transform final
    {
        using Matrix4x4 = DirectX::SimpleMath::Matrix;

    private:
        std::unique_ptr<Transform> mParent = nullptr;
        Matrix4x4 mWorldMatrix;

        Point3D mWorldTranslation;
        Point3D mWorldRotation;
        Point3D mWorldScale;

        Point3D mLocalTranslation;
        Point3D mLocalRotation;
        Point3D mLocalScale;

    public:
        Transform();
        Transform(Transform* aParentTransform);
        ~Transform();

        void UpdateWorldMatrix();
        void SetParent(Transform* aParent);

        Matrix4x4 WorldToLocal() const;
        Matrix4x4 LocalToWorld() const;

        Transform* const GetParent() const { return mParent.get(); }
        Matrix4x4& const GetWorldMatrix() { return mWorldMatrix; }

        Point3D& const GetWorldTranslation() { return mWorldTranslation; }
        Point3D& const GetWorldRotation() { return mWorldRotation; }
        Point3D& const GetWorldScale() { return mWorldScale; }

        Point3D& const GetLocalTranslation() { return mLocalTranslation; }
        Point3D& const GetLocalRotation() { return mLocalRotation; }
        Point3D& const GetLocalScale() { return mLocalScale; }

    public:
        static std::shared_ptr<Transform> CreateShared();
        static std::unique_ptr<Transform> CreateUnique();

        static std::shared_ptr<Transform> CreateShared(Transform* aParentTransform);
        static std::unique_ptr<Transform> CreateUnique(Transform* aParentTransform);

    };
}

#endif // !SOGE_TRANSFORM_HPP
