#ifndef SOGE_CAMERA_HPP
#define SOGE_CAMERA_HPP

#include "SOGE/Game/Transform.hpp"
#include "SOGE/ECS/Components.hpp"
#include "SOGE/Containers/Simple.hpp"

namespace soge
{
    enum class ProjectionType
    {
        Perspective     = 0x00,
        Orthographic    = 0x01
    };

    struct PerspectiveCameraDescriptor
    {
        float aspectRatio   = 1.0f;
        float nearClip      = 0.01f;    // Nearest view frustum plane
        float farClip       = 1000.0f;  // Farthest view frustum plane
        float fov           = 3.14f / 2.0f;
    };

    struct OrthographicCameraDescriptor
    {
        float nearClip  = 0.01f;
        float farClip   = 1000.0f;
        Point2D size    = { 8, 8 };
    };

    class Camera
    {
        using Matrix4x4 = DirectX::SimpleMath::Matrix;

    private:
        ProjectionType mProjectionType;
        PerspectiveCameraDescriptor mPerspectiveCameraDesc;
        OrthographicCameraDescriptor mOrthographicCameraDesc;

        std::unique_ptr<Transform> mCameraTransform;
        Matrix4x4 mViewMatrix;
        Matrix4x4 mProjectionMatrix;

    private:
        void RecalculateProjection();
        void UpdateProjectionMatrix();
        void UpdateViewMatrix();

    public:
        Camera(ProjectionType aProjectionType);
        ~Camera();

        void SetPerspective(float aVFOV, float aAspectRatio, float aNearClip, float aFarClip);
        void SetPerspective(PerspectiveCameraDescriptor aPerspCameraDesc);
        void SetOrthographic(Point2D aSize, float aNearClip, float aFarClip);
        void SetOrthographic(OrthographicCameraDescriptor aOrthoCameraDesc);

        float GetPerspectiveVerticalFOV() const { return mPerspectiveCameraDesc.fov; }
        void SetPerspectiveVerticalFOV(float aVFOV) { mPerspectiveCameraDesc.fov = aVFOV; }
        float GetPerspectiveAspectRatio() const { return mPerspectiveCameraDesc.aspectRatio; }
        void SetPerspectiveAspectRatio(float aAspectRatio) { mPerspectiveCameraDesc.aspectRatio = aAspectRatio; }
        float GetPerspectiveFarClip() const { mPerspectiveCameraDesc.farClip; }
        void SetPerspectiveFarClip(float aFarClip) { mPerspectiveCameraDesc.farClip = aFarClip; }
        float GetPerspectiveNearClip() const { mPerspectiveCameraDesc.nearClip; }
        void SetPerspectiveNearClip(float aNearClip) { mPerspectiveCameraDesc.nearClip = aNearClip; }

        Point2D GetOrthographicSize() const { return mOrthographicCameraDesc.size; }
        void SetOrthographicSize(Point2D aSize) { mOrthographicCameraDesc.size = aSize; }
        float GetOrthographicFarClip() const { mOrthographicCameraDesc.farClip; }
        void SetOrthographicFarClip(float aFarClip) { mOrthographicCameraDesc.farClip = aFarClip; }
        float GetOrthographicNearClip() const { return mOrthographicCameraDesc.nearClip; }
        void SetOrthographicNearClip(float aNearClip) { mOrthographicCameraDesc.nearClip = aNearClip; }

        ProjectionType GetProjectionType() const { return mProjectionType; }
        void SetProjectionType(ProjectionType aProjectionType);

    public:
        std::shared_ptr<Camera> CreateShared(ProjectionType aProjectionType);
        std::unique_ptr<Camera> CreateUnique(ProjectionType aProjectionType);

    };
}

#endif // !SOGE_CAMERA_HPP
