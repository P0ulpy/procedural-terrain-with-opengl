#pragma once

#include <Renderer/Math/Vector.hpp>

struct Transform
{
    Point3df pos { 0.f, 0.f, 0.f };
    EulerRotationf rot { 0.f, 0.f, 0.f };

    Transform() = default;
    Transform(const Point3df& position, const EulerRotationf& rotation)
        : pos(position)
        , rot(rotation)
    {}

    Transform(const Transform& transformable) = default;

    [[nodiscard]] Vector3df GetForward() const
    {
        // Compute the rotation matrix from yaw and pitch
        Mat4f rotationMatrix = 
            Mat4f::RotationY(rot.pitch) * Mat4f::RotationX(rot.yaw);

        // Transform the Forward vector by the rotation matrix
        Vector3df forward;
        forward.x = rotationMatrix(0, 0) * Forward.x + rotationMatrix(0, 1) * Forward.y + rotationMatrix(0, 2) * Forward.z;
        forward.y = rotationMatrix(1, 0) * Forward.x + rotationMatrix(1, 1) * Forward.y + rotationMatrix(1, 2) * Forward.z;
        forward.z = rotationMatrix(2, 0) * Forward.x + rotationMatrix(2, 1) * Forward.y + rotationMatrix(2, 2) * Forward.z;

        return forward.Normalize();
    }

    [[nodiscard]] Vector3df GetLeft() const
    {
        Vector3df forward = GetForward();
        Vector3df right = Vector3df::Cross(forward, Up);
        return right.Normalize();
    }

    void Rotate(const Point3df& p) { Rotate(p.x, p.y, p.z); }
    void Rotate(const Vector3df& v) { Rotate(v.x, v.y, v.z); }
    void Rotate(const EulerRotationf& r) { Rotate(r.yaw, r.pitch, r.roll); }
    void Rotate(float y, float p, float r) { rot.yaw += y; rot.pitch += p; rot.roll += r; }

    static constexpr Vector3df Up { 0.f, 1.f, 0.f };
    static constexpr Vector3df Right { 1.f, 0.f, 0.f };
    static constexpr Vector3df Forward { 0.f, 0.f, 1.f };
};