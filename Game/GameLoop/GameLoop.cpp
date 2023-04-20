//
// Created by Flo on 14/04/2023.
//

#include <SFML/Window/ContextSettings.hpp>
#include <Renderer.hpp>

#include "GameLoop.hpp"

const sf::ContextSettings contextSettings = sf::ContextSettings(24, 8, 4, 4, 6);

GameLoop::GameLoop()
    : window(sf::VideoMode(800, 600), "Game", sf::Style::Default, contextSettings)
{

}

void GameLoop::Init()
{
    Renderer::Init();
    window.setActive(true);
}

void GameLoop::Clean()
{
    Renderer::ShutDown();
    window.close();
}

void GameLoop::Run()
{
    Init();

    while (m_isRunning)
    {
        float dt = m_dtClock.restart().asSeconds();

        HandleEvents();

        Update(dt);

        Render();
    }

    Clean();
}

void GameLoop::HandleEvents()
{
    sf::Event event {};
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_isRunning = false;
                break;

            case sf::Event::Resized:
                Renderer::WindowResize(
                    static_cast<int32_t>(event.size.width),
                    static_cast<int32_t>(event.size.height)
                );
                break;
        }
    }
}

void GameLoop::Update(float dt)
{
    // iterate over all the objects in the scene
}

void GameLoop::Render()
{
    Renderer::Begin(camera);

    // iterate over all the objects in the scene

    Renderer::End();
    window.display();
}
