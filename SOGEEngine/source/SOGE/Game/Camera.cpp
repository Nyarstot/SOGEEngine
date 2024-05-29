#include "sogepch.hpp"
#include "SOGE/Game/Camera.hpp"


namespace soge
{
    Camera::Camera(ProjectionType aProjectionType = ProjectionType::Perspective)
    {
        mProjectionType = aProjectionType;
    }

    Camera::~Camera()
    {

    }

    void Camera::RecalculateProjection()
    {

    }

    void Camera::UpdateProjectionMatrix()
    {

    }

    void Camera::UpdateViewMatrix()
    {
        const Matrix4x4 rotation = Matrix4x4::CreateFromYawPitchRoll(mCameraTransform->GetWorldRotation());
    }

    void Camera::SetPerspective(float aVFOV, float aAspectRatio, float aNearClip, float aFarClip)
    {
        mPerspectiveCameraDesc.fov          = aVFOV;
        mPerspectiveCameraDesc.aspectRatio  = aAspectRatio;
        mPerspectiveCameraDesc.nearClip     = aNearClip;
        mPerspectiveCameraDesc.farClip      = aFarClip;
        this->RecalculateProjection();
    }

    void Camera::SetPerspective(PerspectiveCameraDescriptor aPerspCameraDesc)
    {
        mPerspectiveCameraDesc.fov          = aPerspCameraDesc.fov;
        mPerspectiveCameraDesc.aspectRatio  = aPerspCameraDesc.aspectRatio;
        mPerspectiveCameraDesc.nearClip     = aPerspCameraDesc.nearClip;
        mPerspectiveCameraDesc.farClip      = aPerspCameraDesc.farClip;
        this->RecalculateProjection();
    }

    void Camera::SetOrthographic(Point2D aSize, float aNearClip, float aFarClip)
    {
        mOrthographicCameraDesc.size        = aSize;
        mOrthographicCameraDesc.nearClip    = aNearClip;
        mOrthographicCameraDesc.farClip     = aFarClip;
        this->RecalculateProjection();
    }

    void Camera::SetOrthographic(OrthographicCameraDescriptor aOrthoCameraDesc)
    {
        mOrthographicCameraDesc.size        = aOrthoCameraDesc.size;
        mOrthographicCameraDesc.nearClip    = aOrthoCameraDesc.nearClip;
        mOrthographicCameraDesc.farClip     = aOrthoCameraDesc.farClip;
        this->RecalculateProjection();
    }

    void Camera::SetProjectionType(ProjectionType aProjectionType)
    {
        mProjectionType = aProjectionType;
        if (aProjectionType == ProjectionType::Perspective) {
            this->SetPerspective(this->mPerspectiveCameraDesc);
            return;
        }
        this->SetOrthographic(this->mOrthographicCameraDesc);
        return;
    }

    // Static constructor callers

    std::shared_ptr<Camera> Camera::CreateShared(ProjectionType aProjectionType)
    {
        return std::make_shared<Camera>(aProjectionType);
    }

    std::unique_ptr<Camera> Camera::CreateUnique(ProjectionType aProjectionType)
    {
        return std::make_unique<Camera>(aProjectionType);
    }
}