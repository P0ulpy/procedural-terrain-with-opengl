//
// Created by Flo on 14/04/2023.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

#include <GameLoop/Scene.hpp>
#include <Objects/GameCamera.hpp>

class GameLoop
{
public:
    static GameLoop* Instance() { return s_instance; }

private:
    static GameLoop* s_instance;

public:
    GameLoop();
    ~GameLoop();

    void SetScene(Scene* scene) { m_scene = std::unique_ptr<Scene>(scene); };
    void Run();

    [[nodiscard]] sf::Time GetDeltaTime() const { return m_dt; }

public:
    sf::RenderWindow window;
    GameCamera* camera { nullptr };

private:
    void Init();
    void Clean();

    void HandleEvents();
    void Update(float dt);
    void Render();

private:
    bool m_isRunning { true };
    sf::Clock m_dtClock {};
    sf::Time m_dt {};

    std::unique_ptr<Scene> m_scene { nullptr };
};
