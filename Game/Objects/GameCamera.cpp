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
    : Camera(target, {0.f, 0.f}, {})
{}

void GameCamera::Update(float dt)
{
    HandleKeyboard(dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
        HandleMouse(dt);
}

void GameCamera::HandleKeyboard(float dt)
{
    // TODO : must wrap this in some kind of a Transform class & describe our world orientation (x: "right/left", y: "up/down", z: "forward/backward")

    Vector3df forwardVector = {
        cosf(m_alpha) * sinf(m_beta),
        -sinf(m_beta),
        cosf(m_alpha) * cosf(m_beta),
    };

    forwardVector.Normalize();

    Vector3df upVector = {
        sinf(m_alpha) * sinf(m_beta),
        cosf(m_beta),
        sinf(m_alpha) * cosf(m_beta),
    };

    Vector3df rightVector = {
        cosf(m_beta),
        0,
        -sinf(m_alpha),
    };

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        m_position -= forwardVector * (camSpeed * dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_position += forwardVector * (camSpeed * dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        m_position += upVector * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_position -= upVector * (camSpeed * dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_position += rightVector * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_position -= rightVector * (camSpeed * dt);
}

void GameCamera::HandleMouse(float dt)
{
    auto mousePos = sf::Mouse::getPosition(GameLoop::Instance()->window);
    auto cCenter = GetCenter();

    if(mousePos != cCenter)
    {
        auto delta = mousePos - cCenter;
        m_alpha += static_cast<float>(delta.x) * -1.f * dt;
        m_beta += static_cast<float>(delta.y) * 1.f * dt;

        sf::Mouse::setPosition(GetCenter(), GameLoop::Instance()->window);
    }
}
