#pragma once

#include <Renderer/Camera/Camera.hpp>

class IRenderable
{
public:
    virtual ~IRenderable() = default;

    virtual void Load() = 0;
    virtual void Render(Camera& camera) = 0;
    virtual void Cleanup() {}
};
