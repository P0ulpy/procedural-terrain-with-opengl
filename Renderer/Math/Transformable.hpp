//
// Created by Flo on 27/04/2023.
//

#pragma once

#include "Point.hpp"
#include "Vector.hpp"

struct Transformable
{
    Point3df pos { 0.f, 0.f, 0.f };
    EulerRotationf rot { 0.f, 0.f, 0.f };

    Transformable() = default;
    Transformable(const Point3df& position, const EulerRotationf& rotation)
        : pos(position)
        , rot(rotation)
    {}

    Transformable(const Transformable& transformable) = default;

    [[nodiscard]] Vector3df GetForward() const
    {
        auto radRot = rot.ToDeg();

        float yawn = radRot.yawn;
        float pitch = radRot.pitch;

        Vector3df forward {
            -std::sin(pitch),
            std::sin(yawn) * std::cos(pitch),
            std::cos(yawn) * std::cos(pitch)
        };

        return forward;
    }

    void Rotate(const Point3df& p) { Rotate(p.x, p.y, p.z); }
    void Rotate(const Vector3df& v) { Rotate(v.x, v.y, v.z); }
    void Rotate(const EulerRotationf& r) { Rotate(r.yawn, r.pitch, r.roll); }
    void Rotate(float y, float p, float r) { rot.yawn += y; rot.pitch += p; rot.roll += r; }

    static Vector3df Up() { return { 0.f, 1.f, 0.f }; }
    static Vector3df Right() { return { 1.f, 0.f, 0.f }; }
    static Vector3df Forward() { return { 0.f, 0.f, 1.f }; }
};