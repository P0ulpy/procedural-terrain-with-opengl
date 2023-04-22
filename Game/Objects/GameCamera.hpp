//
// Created by Flo on 20/04/2023.
//

#pragma once


#include <Camera/Camera.hpp>
#include "IUpdatable.hpp"
#include "Math/Point.hpp"

class GameCamera : public Camera, public IUpdatable
{
public:
    ~GameCamera() override = default;
    GameCamera(sf::RenderTarget& target);

    void Update(float dt) override;

    void HandleKeyboard(float dt);
    void HandleMouse(float dt);

    float camSpeed = 2.f;
};
