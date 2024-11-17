//
// Created by Flo on 20/04/2023.
//

#pragma once

#include <ostream>

template <typename T>
struct EulerRotation
{
    T yaw;
    T pitch;
    T roll;

    EulerRotation(const T yaw = 0, const T pitch = 0, const T roll = 0)
        : yaw(yaw), pitch(pitch), roll(roll)
    {}

    EulerRotation(const EulerRotation& angle)
            : yaw(angle.yaw), pitch(angle.pitch), roll(angle.roll)
    {}

    EulerRotation ToRad() const
    {
        return {
            DegToRad<T>(yaw),
            DegToRad<T>(pitch),
            DegToRad<T>(roll)
        };
    }

    EulerRotation ToDeg() const
    {
        return {
                RadToDeg<T>(yaw),
                RadToDeg<T>(pitch),
                RadToDeg<T>(roll)
        };
    }
};

template<typename T>
struct Point2d
{
    Point2d(const T x = 0, const T y = 0): x(x), y(y) {}
    Point2d(const Point2d& pt): x(pt.x), y(pt.y) {}

    T x;
    T y;
};

template<typename T>
struct Point3d
{
    constexpr Point3d(const T x = 0, const T y = 0, const T z = 0): x(x), y(y), z(z) {}
    Point3d(const Point3d& pt): x(pt.x), y(pt.y), z(pt.z) {}

    T x;
    T y;
    T z;

    Point3d operator+(const Point3d& rhs) const
    {
        return Point3d(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Point3d operator-(const Point3d& rhs) const
    {
        return Point3d(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Point3d operator*(const T& multiplier) const
    {
        return Point3d(x * multiplier, y * multiplier, z * multiplier);
    }

    Point3d operator*(const Point3d& rhs) const
    {
        return Point3d(x * rhs.x, y * rhs.y, z * rhs.z);
    }

    Point3d operator/(const Point3d& rhs) const
    {
        return Point3d(x / rhs.x, y / rhs.y, z / rhs.z);
    }

    Point3d& operator+=(const Point3d& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Point3d& operator-=(const Point3d& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point3d& pt)
    {
        os << "(" << pt.x << ", " << pt.y << ", " << pt.z << ")";
        return os;
    }
};

using Point2df = Point2d<float>;
using Point2di = Point2d<int>;
using Point3df = Point3d<float>;
using Point3di = Point3d<int>;
using EulerRotationf = EulerRotation<float>;
