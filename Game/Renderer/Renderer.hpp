//
// Created by Flo on 02/04/2023.
//

#pragma once

#include <GL/glew.h>
#include <SFML/Window/Window.hpp>
#include <Renderer/Camera/Camera.hpp>

class Renderer
{
public:
    Renderer() = delete;

    static void Init();
    static void ShutDown();

    static void Begin(Camera& camera);
    static void End();

    static void WindowResize(int32_t width, int32_t height);
};
