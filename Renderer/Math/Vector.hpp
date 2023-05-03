#pragma once

#include "Point.hpp"

template<typename T>
struct Vector3d : public Point3df
{
    Vector3d(const T x = 0, const T y = 0, const T z = 0) : Point3df(x, y, z) {}
    Vector3d(const Vector3d& vec): Point3df(vec) {}

    Vector3d Cross(const Vector3d& other) const { return Cross(*this, other); }

    static Vector3d Cross(const Vector3d& vec1, const Vector3d& vec2)
    {
        return Vector3d(
                vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x
        );
    }

    T Dot(const Vector3d& other) const
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    static T Dot(const Vector3d& vec1, const Vector3d& vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }

    Vector3d& Normalize()
    {
        const T length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        this->x /= length;
        this->y /= length;
        this->z /= length;
        return *this;
    }

    static Vector3d Normalize(const Vector3d& vec3d)
    {
        const T length = sqrt(vec3d.x * vec3d.x + vec3d.y * vec3d.y + vec3d.z * vec3d.z);
        vec3d.x /= length;
        vec3d.y /= length;
        vec3d.z /= length;
        return vec3d;
    }
};

using Vector3df = Vector3d<float>;
using Vector3di = Vector3d<int>;
