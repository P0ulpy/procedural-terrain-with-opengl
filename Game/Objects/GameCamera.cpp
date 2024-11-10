#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <Objects/GameCamera.hpp>
#include <GameLoop/GameLoop.hpp>
#include <Renderer/Math/Vector.hpp>

GameCamera::GameCamera(sf::RenderTarget &target)
        : Camera(target, {
            {0, 100, 0},
            { 0, 0, 0 }
            }, 45.f / 180.0f * PI<float>, 0.1f, 500.f)
{}

void GameCamera::Update(float dt)
{
    HandleKeyboard(dt);

    if(!m_lockMouse)
        HandleMouse(dt);
}

void GameCamera::HandleKeyboard(float dt)
{
    // Vector3df forwardVector = m_transform.GetForward();
    Vector3df forwardVector = Transform::Forward(); //m_transform.GetForward();
    // Vector3df rightVector = Vector3df::Cross(forwardVector, Transform::Up());
    Vector3df rightVector = Transform::Right(); //Vector3df::Cross(forwardVector, Transformable::Up());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        m_transform.pos -= forwardVector * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_transform.pos += forwardVector * (camSpeed * dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        m_transform.pos += Transform::Up() * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_transform.pos -= Transform::Up() * (camSpeed * dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_transform.pos += rightVector * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_transform.pos -= rightVector * (camSpeed * dt);

    static bool escapeKeyPressed = false;
    bool lockCamKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    if(lockCamKeyPressed && !escapeKeyPressed)
    {
        m_lockMouse = !m_lockMouse;
        escapeKeyPressed = true;
    }
    if (!lockCamKeyPressed)
    {
        escapeKeyPressed = false;
    }
}

void GameCamera::HandleMouse(float dt)
{
    auto mousePos = sf::Mouse::getPosition(GameLoop::Instance()->window);
    auto cCenter = GetCenter();

    if(mousePos != cCenter)
    {
        constexpr int MaxMouseDelta = 10;
        auto delta = mousePos - cCenter;

        if(delta.x > MaxMouseDelta) delta.x = 1;
        if(delta.y > MaxMouseDelta) delta.y = 1;
        if(delta.x < -MaxMouseDelta) delta.x = -1;
        if(delta.y < -MaxMouseDelta) delta.y = -1;

        float yawDelta = static_cast<float>(delta.x) * -1.f * camSensitivity;
        float pitchDelta = static_cast<float>(delta.y) * 1.f * camSensitivity;

        m_transform.Rotate(pitchDelta, yawDelta, 0.f);

        sf::Mouse::setPosition(GetCenter(), GameLoop::Instance()->window);
    }
}
