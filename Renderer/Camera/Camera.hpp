//
// Created by Flo on 15/04/2023.
//

#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "../Math/Point.hpp"
#include "../Math/Constants.hpp"
#include "../Math/Mat.hpp"

struct CameraParameters
{
    float fov { 45.0f / 180.0f * PI<float> };
    float near { 0.1f };
    float far { 100.0f };
};

class Camera
{
public:
    virtual ~Camera() = default;
    Camera(sf::RenderTarget& target, const Point3df& position, const CameraParameters& parameters);

    void ComputeViewProjection();

    [[nodiscard]] sf::Vector2i GetCenter() const { return { static_cast<int>(m_target->getSize().x / 2), static_cast<int>(m_target->getSize().y / 2) }; }
    [[nodiscard]] float GetAspectRatio() const { return static_cast<float>(m_target->getSize().x) / static_cast<float>(m_target->getSize().y); }
    [[nodiscard]] Mat4f GetViewMatrix() const { return m_viewMatrix; }
    [[nodiscard]] Mat4f GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    [[nodiscard]] CameraParameters GetParameters() {
        return {
            .fov = m_fov,
            .near = m_near,
            .far = m_far,
        };
    }

    void SetFOV(float fov) { m_fov = fov / 180.0f * PI<float>; }
    void SetNear(float near) { m_near = near; }
    void SetFar(float far) { m_far = far; }

    [[nodiscard]] Point3d<float> GetPosition() const { return m_position; };
    [[nodiscard]] float GetAlpha() const { return m_alpha; };
    [[nodiscard]] float GetBeta() const { return m_beta; };

protected:
    float m_fov { 45.0f };
    float m_near { 0.1f };
    float m_far { 100.0f };

    Mat4f m_viewMatrix {};
    Mat4f m_projectionMatrix {};
    Mat4f m_viewProjectionMatrix {};

    float m_alpha { 0.0f };
    float m_beta { 0.0f };

    Point3df m_position { 0.f, 0.f, 0.f };

    sf::RenderTarget* m_target { nullptr };
};
