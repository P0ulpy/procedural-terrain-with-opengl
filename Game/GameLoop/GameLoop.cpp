//
// Created by Flo on 14/04/2023.
//

#include "GameLoop.hpp"

#include <SFML/Window/ContextSettings.hpp>
#include <imgui-SFML.h>

#include <Renderer.hpp>

GameLoop* GameLoop::s_instance = nullptr;

const sf::ContextSettings contextSettings = sf::ContextSettings(24, 8, 4, 4, 6);

GameLoop::GameLoop()
    : window(sf::VideoMode(800, 600), "Game", sf::Style::Default, contextSettings)
    // Dirty way to manage camera lifetime i will refactor it later
    , camera(new GameCamera(window))
{
    if(nullptr != s_instance)
        throw std::runtime_error("GameLoop already instantiated");

    s_instance = this;
}

GameLoop::~GameLoop()
{
    s_instance = nullptr;
}


void GameLoop::Init()
{
    if(nullptr == m_scene)
        throw std::runtime_error("No scene set");

    ImGui::SFML::Init(window);
    Renderer::Init();

    m_scene->Init();
    m_scene->AddObject<GameCamera>(camera);

    window.setActive(true);
}

void GameLoop::Clean()
{
    ImGui::SFML::Shutdown(window);
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
        ImGui::SFML::ProcessEvent(event);

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
    ImGui::SFML::Update(window, m_dtClock.getElapsedTime());
    m_scene->Update(dt);
}

void GameLoop::Render()
{
    camera->ComputeViewProjection();

    ImGui::SFML::Render(window);

    Renderer::Begin(*camera);

    m_scene->Render(*camera);

    Renderer::End();

    window.display();
}