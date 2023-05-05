//
// Created by Flo on 20/04/2023.
//

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "GameCamera.hpp"
#include "../GameLoop/GameLoop.hpp"
#include "Math/Vector.hpp"

GameCamera::GameCamera(sf::RenderTarget &target)
        : Camera(target, {
            {0, 100, 0},
            { 0, 0, 0 }
            }, 45.f / 180.0f * PI<float>, 0.1f, 500.f)
{}

void GameCamera::Update(float dt)
{
    HandleKeyboard(dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
        m_lockMouse = !m_lockMouse;

    if(!m_lockMouse)
        HandleMouse(dt);
}

void GameCamera::HandleKeyboard(float dt)
{
    Vector3df forwardVector = Transform::Forward(); //m_transform.GetForward();
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
}

void GameCamera::HandleMouse(float dt)
{
    auto mousePos = sf::Mouse::getPosition(GameLoop::Instance()->window);
    auto cCenter = GetCenter();

    if(mousePos != cCenter)
    {
        auto delta = mousePos - cCenter;

        if(delta.x > 0) delta.x = 1;
        if(delta.y > 0) delta.y = 1;
        if(delta.x < 0) delta.x = -1;
        if(delta.y < 0) delta.y = -1;

        float yawDelta = static_cast<float>(delta.x) * -1.f * camSensitivity;
        float pitchDelta = static_cast<float>(delta.y) * 1.f * camSensitivity;

        m_transform.Rotate(pitchDelta, yawDelta, 0.f);

        sf::Mouse::setPosition(GetCenter(), GameLoop::Instance()->window);
    }
}
