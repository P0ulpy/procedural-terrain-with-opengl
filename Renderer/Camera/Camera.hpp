//
// Created by Flo on 15/04/2023.
//

#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include "../Math/Point.hpp"
#include "../Math/Constants.hpp"
#include "../Math/Mat.hpp"
#include "../Math/Transformable.hpp"

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
    Camera(sf::RenderTarget& target, const Transformable& transform, const CameraParameters& parameters);

    void ComputeViewProjection();

    [[nodiscard]] sf::Vector2i GetCenter() const { return { static_cast<int>(m_target->getSize().x / 2), static_cast<int>(m_target->getSize().y / 2) }; }
    [[nodiscard]] float GetAspectRatio() const { return static_cast<float>(m_target->getSize().x) / static_cast<float>(m_target->getSize().y); }
    [[nodiscard]] Mat4f GetViewMatrix() const { return m_viewMatrix; }
    [[nodiscard]] Mat4f GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    [[nodiscard]] CameraParameters GetParameters() {
        return {
            .fov = fov,
            .near = near,
            .far = far,
        };
    }

    float fov { 45.0f };
    float near { 0.1f };
    float far { 100.0f };

    [[nodiscard]] Transformable& GetTransform() { return m_transform; }

protected:

    Mat4f m_viewMatrix {};
    Mat4f m_projectionMatrix {};
    Mat4f m_viewProjectionMatrix {};

    Transformable m_transform {};

    sf::RenderTarget* m_target { nullptr };
};
