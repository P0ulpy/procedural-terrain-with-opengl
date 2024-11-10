//
// Created by Flo on 20/04/2023.
//

#pragma once

#include <gl/glew.h>

#include <Renderer/Renderable/IRenderable.hpp>

template <typename T>
class Cube : public IRenderable
{
public:
    Cube();
    ~Cube();

    void Load() override;
    void Render(Camera& camera) override;

private:
    T m_angle = 0.0f;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program;
    GLsizei m_nVertices;
};

#include "Cube.tpp"
