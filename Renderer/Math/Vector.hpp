//
// Created by Flo on 22/04/2023.
//

#pragma once

#include "Point.hpp"

template<typename T>
struct Vector3d : public Point3d<T>
{
    Vector3d(const T x = 0, const T y = 0, const T z = 0) : Point3d<T>(x, y, z) {}
    Vector3d(const Vector3d& vec): Point3d<T>(vec) {}

    Vector3d operator^(const Vector3d& other) const
    {
        return Vector3d(
            this->y * other.z - this->z * other.y,
            this->z * other.x - this->x * other.z,
            this->x * other.y - this->y * other.x
        );
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
