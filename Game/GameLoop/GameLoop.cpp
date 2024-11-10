//
// Created by Flo on 14/04/2023.
//

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Window/ContextSettings.hpp>

#include <GameLoop/GameLoop.hpp>
#include <Renderer/Renderer.hpp>

GameLoop* GameLoop::s_instance = nullptr;

const sf::ContextSettings contextSettings = sf::ContextSettings(24, 8, 4, 4, 6);

GameLoop::GameLoop()
    : window(sf::VideoMode(1700, 1000), "Game", sf::Style::Default, contextSettings)
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

    window.setActive(true);
    Renderer::Init();

    ImGui::SFML::Init(window);

    // Can't be used because of our dumb version of imgui & OpenGL
    // ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    auto& io = ImGui::GetIO();

    io.ConfigWindowsMoveFromTitleBarOnly = false;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

    m_scene->AddObject<GameCamera>(camera);
    m_scene->Init();
}

void GameLoop::Clean()
{
    Renderer::ShutDown();
    window.close();
    ImGui::SFML::Shutdown();
}

void GameLoop::Run()
{
    Init();

    while (m_isRunning)
    {
        m_dt = m_dtClock.restart();

        HandleEvents();
        if(!m_isRunning) break;

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
        ImGui::SFML::ProcessEvent(event);

        switch(event.type)
        {
            case sf::Event::Closed:
                m_isRunning = false;
                window.close();
                ImGui::SFML::Shutdown();
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

    Renderer::Begin(*camera);
    m_scene->Render(*camera);
    Renderer::End();

    ImGui::SFML::Update(window, m_dt);
    m_scene->OnGui();
    ImGui::SFML::Render(window);

    window.display();
}