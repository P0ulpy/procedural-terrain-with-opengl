#pragma once

#include <array>
#include <cmath>

#include <Renderer/Math/Point.hpp>

template<typename Type>
struct Mat4
{
    Mat4() { for(int i = 0; i < 16 ; ++i) m_data[i] = 0; }

    Type& operator() (const int i, const int j) { return m_data[j * 4 + i]; }
    const Type& operator() (const int i, const int j) const { return m_data[j * 4 + i]; }

    const Type* Data() const { return m_data.data(); }

    static Mat4<Type> Identity()
    {
        Mat4<Type> result;
        for (int i = 0; i < 4; ++i)
        {
            result(i, i) = 1;
        }
        return result;
    }

    static Mat4<Type> RotationX(const Type& angle)
    {
        return RotationAxisAligned<1, 2>(angle);
    }

    static Mat4<Type> RotationY(const Type& angle)
    {
        return RotationAxisAligned<0, 2>(angle);
    }

    static Mat4<Type> RotationZ(const Type& angle)
    {
        return RotationAxisAligned<0, 1>(angle);
    }

    static Mat4<Type> Translation(const Type& x, const Type& y, const Type& z)
    {
        Mat4<Type> result = Identity();
        result(0, 3) = x;
        result(1, 3) = y;
        result(2, 3) = z;
        return result;
    }

    static Mat4<Type> Translation(const Point3d<Type>& pt)
    {
        return Translation(pt.x, pt.y, pt.z);
    }

    static Mat4<Type> Projection(const Type& aspect, const Type& fov, const Type& farPlane, const Type& nearPlane)
    {
        Mat4<Type> result;
        result(0, 0) = 1 / (aspect * std::tan(fov / 2));
        result(1, 1) = 1 / std::tan(fov / 2);
        result(2, 2) = -(farPlane + nearPlane) / (farPlane - nearPlane);
        result(2, 3) = -2 * farPlane * nearPlane / (farPlane - nearPlane);
        result(3, 2) = -1;
        return result;
    }

private:
    template <size_t a1, size_t a2>
    static Mat4<Type> RotationAxisAligned(const Type& angle)
    {
        Mat4<Type> result = Identity();
        result(a1, a1) = std::cos(angle);
        result(a1, a2) = std::sin(angle);
        result(a2, a1) = -std::sin(angle);
        result(a2, a2) = std::cos(angle);
        return result;
    }

    std::array<Type, 16> m_data;
};

template<typename T>
Mat4<T> operator*(const Mat4<T>& lhs, const Mat4<T>& rhs)
{
    Mat4<T> result;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                result(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
    return result;
}

using Mat4f = Mat4<float>;