#include "sogepch.hpp"
#include "SOGE/Math/Transform.hpp"


namespace soge
{
    Transform::Transform()
    {
        mWorldScale = Point3D(1.0f);
        mWorldRotation = Point3D(0.0f);
        mWorldTranslation = Point3D(0.0f);

        mLocalScale = Point3D(1.0f);
        mLocalRotation = Point3D(0.0f);
        mLocalTranslation = Point3D(0.0f);

        mParent = std::make_unique<Transform>(nullptr);
        this->UpdateWorldMatrix();
    }

    Transform::Transform(Transform* aParentTransform)
    {
        mWorldScale = Point3D(1.0f);
        mWorldRotation = Point3D(0.0f);
        mWorldTranslation = Point3D(0.0f);

        mLocalScale = Point3D(1.0f);
        mLocalRotation = Point3D(0.0f);
        mLocalTranslation = Point3D(0.0f);

        mParent = std::make_unique<Transform>(aParentTransform);
        this->UpdateWorldMatrix();
    }

    Transform::~Transform()
    {
        mParent.release();
    }

    void Transform::UpdateWorldMatrix()
    {
        mWorldMatrix =
            Matrix4x4::CreateScale(mWorldScale) *
            Matrix4x4::CreateFromYawPitchRoll(mWorldRotation) *
            Matrix4x4::CreateTranslation(mWorldTranslation) *
            (mParent == nullptr ? Matrix4x4::Identity : mParent->mWorldMatrix);
    }

    void Transform::SetParent(Transform* aParent)
    {
        if (mParent == nullptr) {
            mParent = std::make_unique<Transform>(aParent);
            return;
        }

        mParent.reset(aParent);
    }

    Transform::Matrix4x4 Transform::WorldToLocal() const
    {
        return Matrix4x4();
    }

    Transform::Matrix4x4 Transform::LocalToWorld() const
    {
        return Matrix4x4();
    }

    // Static constructor callers

    std::shared_ptr<Transform> Transform::CreateShared()
    {
        return std::make_shared<Transform>();
    }

    std::unique_ptr<Transform> Transform::CreateUnique()
    {
        return std::make_unique<Transform>();
    }

    std::shared_ptr<Transform> Transform::CreateShared(Transform* aParentTransform)
    {
        return std::make_shared<Transform>(aParentTransform);
    }

    std::unique_ptr<Transform> Transform::CreateUnique(Transform* aParentTransform)
    {
        return std::make_unique<Transform>(aParentTransform);
    }
}