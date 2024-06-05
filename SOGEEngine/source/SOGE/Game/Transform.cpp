#include "sogepch.hpp"
#include "SOGE/Game/Transform.hpp"


namespace soge
{
    Transform::Transform()
    {
        mRotation       = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
        mScale          = Point3D(1.0f, 1.0f, 1.0f);
        mTranslation    = Point3D(0.0f, 0.0f, 0.0f);
        mWorldPosition  = Point3D(0.0f, 0.0f, 0.0f);
        this->UpdateWorldMatrix();
    }

    Transform::Transform(Transform* aParentTransform)
    {
        mRotation       = aParentTransform->mRotation;
        mScale          = aParentTransform->mScale;
        mTranslation    = aParentTransform->mTranslation;
        mWorldPosition  = aParentTransform->mWorldPosition;

        mParent = std::make_unique<Transform>(aParentTransform);
        this->UpdateWorldMatrix();
    }

    Transform::~Transform()
    {
        mParent.release();
    }

    void Transform::UpdateWorldMatrix()
    {
        mWorldTransformMatrix =
            Matrix4x4::CreateFromQuaternion(mRotation) *
            Matrix4x4::CreateScale(mScale) *
            Matrix4x4::CreateTranslation(mTranslation) *
            (mParent == nullptr ? Matrix4x4::Identity : mParent->mWorldTransformMatrix);
    }

    void Transform::SetParent(Transform* aParent)
    {
        if (mParent == nullptr) {
            mParent = std::make_unique<Transform>(aParent);
            return;
        }

        mParent.reset(aParent);
    }

    Transform::Matrix4x4& const Transform::GetWorldMatrix()
    {
        this->UpdateWorldMatrix();
        return mWorldTransformMatrix;
    }

    Transform::Matrix4x4& const Transform::GetLocalMatrix()
    {
        return mLocalTransformMatrix;
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