//
// Created by Flo on 14/04/2023.
//

#include "GameLoop.hpp"

#include <SFML/Window/ContextSettings.hpp>

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

    //ImGui::SFML::Init(window);

    //ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //auto& io = ImGui::GetIO();

    //io.ConfigWindowsMoveFromTitleBarOnly = false;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

    Renderer::Init();

    m_scene->AddObject<GameCamera>(camera);
    m_scene->Init();

    window.setActive(true);
}

void GameLoop::Clean()
{
    //ImGui::SFML::Shutdown();
    Renderer::ShutDown();
    window.close();
}

void GameLoop::Run()
{
    Init();

    while (m_isRunning)
    {
        m_dt = m_dtClock.restart();

        HandleEvents();

        Update(m_dt.asSeconds());

        Render();
    }

    Clean();
}

void GameLoop::HandleEvents()
{
    sf::Event event {};
    while (window.pollEvent(event))
    {
        //ImGui::SFML::ProcessEvent(event);

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
    m_scene->Update(dt);
}

void GameLoop::Render()
{
    camera->ComputeViewProjection();

    //ImGui::SFML::Update(window, m_dt);

    Renderer::Begin(*camera);
    m_scene->Render(*camera);
    Renderer::End();

    //ImGui::SFML::Render(window);
    window.display();
}