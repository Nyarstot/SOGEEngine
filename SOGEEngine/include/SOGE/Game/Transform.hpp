#ifndef SOGE_TRANSFORM_HPP
#define SOGE_TRANSFORM_HPP

#include "SOGE/Engine/EngineSetup.hpp"
#include "SOGE/Containers/Simple.hpp"

namespace soge
{
    class Transform final
    {
        using Matrix4x4     = DirectX::SimpleMath::Matrix;
        using Quaternion    = DirectX::SimpleMath::Quaternion;

    private:
        std::unique_ptr<Transform> mParent = nullptr;
        Matrix4x4 mWorldTransformMatrix;
        Matrix4x4 mLocalTransformMatrix;

        Point3D mWorldPosition;
        Quaternion mRotation;
        Point3D mTranslation;
        Point3D mScale;

    public:
        Transform();
        Transform(Transform* aParentTransform);
        ~Transform();

        void UpdateWorldMatrix();
        void SetParent(Transform* aParent);

        Transform* const GetParent() const { return mParent.get(); }
        Matrix4x4& const GetWorldMatrix();
        Matrix4x4& const GetLocalMatrix();

    public:
        static std::shared_ptr<Transform> CreateShared();
        static std::unique_ptr<Transform> CreateUnique();

        static std::shared_ptr<Transform> CreateShared(Transform* aParentTransform);
        static std::unique_ptr<Transform> CreateUnique(Transform* aParentTransform);

    };
}

#endif // !SOGE_TRANSFORM_HPP
