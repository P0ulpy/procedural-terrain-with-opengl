//
// Created by Flo on 15/04/2023.
//

#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "../Math/Matrix.hpp"
#include "../Math/Constants.hpp"
#include "../Math/Transform.hpp"

class Camera
{
public:
    virtual ~Camera() = default;
    Camera(sf::RenderTarget& target, const Transform& transform, float fov, float near, float far);

    void ComputeViewProjection();

    [[nodiscard]] sf::Vector2i GetCenter() const { return { static_cast<int>(m_target->getSize().x / 2), static_cast<int>(m_target->getSize().y / 2) }; }
    [[nodiscard]] float GetAspectRatio() const { return static_cast<float>(m_target->getSize().x) / static_cast<float>(m_target->getSize().y); }
    [[nodiscard]] Mat4f GetViewMatrix() const { return m_viewMatrix; }
    [[nodiscard]] Mat4f GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

    float _fov { 45.0f };
    float _near { 0.1f };
    float _far { 100.0f };

    [[nodiscard]] Transform& GetTransform() { return m_transform; }

protected:
    Mat4f m_viewMatrix {};
    Mat4f m_projectionMatrix {};
    Mat4f m_viewProjectionMatrix {};

    Transform m_transform {};

    sf::RenderTarget* m_target { nullptr };
};
