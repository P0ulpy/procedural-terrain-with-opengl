#pragma once

#include <array>
#include <vector>

#include <Renderer/Texture/Texture.hpp>
#include <Renderer/Shader/Shader.hpp>
#include <Renderer/Renderable/IRenderable.hpp>

class SkyBox : public IRenderable
{
public:
    ~SkyBox() override;

    void Load() override;
    void Render(Camera& camera) override;

    void LoadShaders();

private:
    void initSkyBox();

    GLuint m_cubemapTexture{};
    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_shaderProgram{};
    GLint m_uniformViewProjection{};
    GLint m_uniformModel{};

    std::array<Texture, 6> m_textures
    {
        Texture("Assets/Textures/SkyBox/right.jpg"),
        Texture("Assets/Textures/SkyBox/left.jpg"),
        Texture("Assets/Textures/SkyBox/top.jpg"),
        Texture("Assets/Textures/SkyBox/bottom.jpg"),
        Texture("Assets/Textures/SkyBox/front.jpg"),
        Texture("Assets/Textures/SkyBox/back.jpg")
    };
};
