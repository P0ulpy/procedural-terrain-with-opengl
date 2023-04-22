//
// Created by Flo on 15/04/2023.
//

#include "Camera.hpp"

Camera::Camera(sf::RenderTarget &target, const Point3df &position, const CameraParameters &parameters)
        : m_target(&target)
        , m_position(position)
        , m_near(parameters.near)
        , m_far(parameters.far)
{}

void Camera::ComputeViewProjection()
{
    float aspect = GetAspectRatio();

    m_viewMatrix = Mat4f::RotationX(-m_beta)
                   * Mat4f::RotationY(-m_alpha)
                   * Mat4f::Translation(-m_position.x, -m_position.y, -m_position.z);

    m_projectionMatrix = Mat4f::Projection(aspect, m_fov, m_far, m_near);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}
