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
        : Camera(target, {}, {})
{}

void GameCamera::Update(float dt)
{
    HandleKeyboard(dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
        m_lockMouse = !m_lockMouse;

    if(!m_lockMouse)
        HandleMouse(dt);
}

void GameCamera::HandleKeyboard(float dt)
{
    // TODO : must wrap this in some kind of a Transform class & describe our world orientation (x: "right/left", y: "up/down", z: "forward/backward")

    Vector3df forwardVector = Transformable::Forward(); //m_transform.GetForward();
    Vector3df rightVector = Transformable::Right(); //Vector3df::Cross(forwardVector, Transformable::Up());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        m_transform.pos -= forwardVector * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_transform.pos += forwardVector * (camSpeed * dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        m_transform.pos += Transformable::Up() * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_transform.pos -= Transformable::Up() * (camSpeed * dt);

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
        float yawDelta = static_cast<float>(delta.x) * -1.f * dt;
        float pitchDelta = static_cast<float>(delta.y) * 1.f * dt;

        m_transform.Rotate(pitchDelta, yawDelta, 0.f);

        sf::Mouse::setPosition(GetCenter(), GameLoop::Instance()->window);
    }
}
