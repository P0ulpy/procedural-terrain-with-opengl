#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <Objects/GameCamera.hpp>
#include <GameLoop/GameLoop.hpp>
#include <Renderer/Math/Vector.hpp>
#include <Utils/SFMLInputsHelper.hpp>

GameCamera::GameCamera(sf::RenderTarget &target)
        : Camera(
            target, 
            {
                { 0, 50, 0 },
                { 0, 0, 0 }
            }, 
            45.f / 180.0f * PI<float>, 
            0.1f, 
            2000.f)
{}

void GameCamera::Update(float dt)
{
    if(sf::KeyboardUtils::isKeyHasPressed(sf::Keyboard::Escape))
    {
        m_disableMovements = !m_disableMovements;
    }
 
    if(!m_disableMovements)
    {
        HandleMouse(dt);
        HandleKeyboard(dt);
    }
}

void GameCamera::HandleKeyboard(float dt)
{
    Vector3df forwardVector = m_transform.GetForward();
    Vector3df leftVector = m_transform.GetLeft();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        m_transform.pos -= forwardVector * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_transform.pos += forwardVector * (camSpeed * dt);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        m_transform.pos += Transform::Up * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        m_transform.pos -= Transform::Up * (camSpeed * dt);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_transform.pos += leftVector * (camSpeed * dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_transform.pos -= leftVector * (camSpeed * dt);
}

void GameCamera::HandleMouse(float dt)
{
    auto mousePos = sf::Mouse::getPosition(GameLoop::Instance()->window);
    auto cCenter = GetCenter();

    if(mousePos != cCenter)
    {
        constexpr int MaxMouseDelta = 10;
        auto delta = mousePos - cCenter;

        float pitchDelta = static_cast<float>(-delta.x) * camSensitivity;
        float yawDelta = static_cast<float>(delta.y) * camSensitivity;

        m_transform.Rotate(yawDelta, pitchDelta, 0.f);

        sf::Mouse::setPosition(GetCenter(), GameLoop::Instance()->window);
    }
}
