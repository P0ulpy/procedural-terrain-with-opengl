//
// Created by Flo on 02/04/2023.
//

#include <Renderer/Renderer.hpp>

#include <stdexcept>

void Renderer::Init()
{
    glewExperimental = GL_TRUE;

    if (glewInit())
        throw std::runtime_error("Error init glew");
}

void Renderer::ShutDown()
{

}

void Renderer::Begin(Camera& camera)
{
    // effacement les tampons de couleur/profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::End()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glFlush();
}

void Renderer::WindowResize(int32_t width, int32_t height)
{
    // on ajuste le viewport lorsque la fenêtre est redimensionnée
    glViewport(0, 0, width, height);
}
