#ifndef SOGE_SIMPLE_HPP
#define SOGE_SIMPLE_HPP

#include <SimpleMath.h>

namespace soge
{
    struct Point2D
    {
        float x = 0.0f;
        float y = 0.0f;

        Point2D operator+ (Point2D const& other) {
            Point2D result;
            result.x = other.x + x;
            result.y = other.y + y;

            return result;
        }

        Point2D operator+= (Point2D const& other) {
            Point2D result = other;
            result.x += x;
            result.y += y;

            return result;
        }

        Point2D operator- (Point2D const& other) {
            Point2D result;
            result.x = x - other.x;
            result.y = y - other.y;

            return result;
        }

        operator DirectX::SimpleMath::Vector2() const {
            return DirectX::SimpleMath::Vector2(x, y);
        }
    };

    struct Point3D
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Point3D() : x(0.0f), y(0.0f), z(0.0f) {};
        Point3D(float aValue) : x(aValue), y(aValue), z(aValue) {};
        Point3D(float aX, float aY, float aZ) : x(aX), y(aY), z(aZ) {};
        Point3D(const Point3D& aOther) : x(aOther.x), y(aOther.y), z(aOther.z) {};

        Point3D operator+ (Point3D const& other) {
            Point3D result;
            result.x = other.x + x;
            result.y = other.y + y;
            result.z = other.z + z;

            return result;
        }

        Point3D& operator+= (Point3D const& other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;

            return *this;
        }

        Point3D operator- (Point3D const& other) {
            Point3D result;
            result.x = x - other.x;
            result.y = y - other.y;
            result.z = z - other.z;

            return result;
        }

        operator DirectX::SimpleMath::Vector3() const {
            return DirectX::SimpleMath::Vector3(x, y, z);
        }
    };

    struct Point4D
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        Point4D operator+ (Point4D const& other) {
            Point4D result;
            result.x = other.x + x;
            result.y = other.y + y;
            result.z = other.z + z;
            result.w = other.w + w;

            return result;
        }

        Point4D operator+= (Point4D const& other) {
            Point4D result = other;
            result.x += x;
            result.y += y;
            result.z += z;
            result.w += w;

            return result;
        }

        Point4D operator- (Point4D const& other) {
            Point4D result;
            result.x = x - other.x;
            result.y = y - other.y;
            result.z = z - other.z;
            result.w = w - other.w;

            return result;
        }

        operator DirectX::SimpleMath::Vector4() const {
            return DirectX::SimpleMath::Vector4(x, y, z, w);
        }
    };
}

#endif // !SOGE_SIMPLE_HPP
