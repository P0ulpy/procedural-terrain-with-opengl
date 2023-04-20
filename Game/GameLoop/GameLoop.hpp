//
// Created by Flo on 14/04/2023.
//

#include <SFML/Window.hpp>
#include "Camera/Camera.hpp"

class GameLoop
{
public:
    GameLoop();
    void Run();

public:
    sf::Window window {};
    Camera camera;

private:
    void Init();
    void Clean();

    void HandleEvents();
    void Update(float dt);
    void Render();

private:
    bool m_isRunning { true };
    sf::Clock m_dtClock {};
};
