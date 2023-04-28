//
// Created by Flo on 15/04/2023.
//

#include "Camera.hpp"

Camera::Camera(sf::RenderTarget &target, const Transformable &transform, const CameraParameters &parameters)
        : m_target(&target)
        , m_transform(transform)
        , near(parameters.near)
        , far(parameters.far)
        , fov(parameters.fov)
{}

void Camera::ComputeViewProjection()
{
    float aspect = GetAspectRatio();

    m_viewMatrix = Mat4f::RotationX(-m_transform.rot.yawn)
                   * Mat4f::RotationY(-m_transform.rot.pitch)
                   * Mat4f::Translation(-m_transform.pos.x, -m_transform.pos.y, -m_transform.pos.z);

    m_projectionMatrix = Mat4f::Projection(aspect, fov, far, near);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}
