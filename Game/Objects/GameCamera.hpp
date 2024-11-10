#pragma once

#include <Renderer/Camera/Camera.hpp>
#include <Objects/IUpdatable.hpp>

class GameCamera : public Camera, public IUpdatable
{
public:
    ~GameCamera() override = default;
    GameCamera(sf::RenderTarget& target);

    void Update(float dt) override;

    void HandleKeyboard(float dt);
    void HandleMouse(float dt);

    float camSpeed = 30.f;
    float camSensitivity = 0.01f;

protected:
    bool m_lockMouse = false;
};
