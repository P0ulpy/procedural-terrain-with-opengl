//
// Created by Flo on 17/04/2023.
//

#pragma once

#include "Camera/Camera.hpp"

class IRenderable
{
public:
    virtual ~IRenderable() = default;

    virtual void Load() = 0;
    virtual void Render(Camera& camera) = 0;
};
