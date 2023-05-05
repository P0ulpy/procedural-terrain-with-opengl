#pragma once

#include <array>
#include <vector>
#include <Texture/Texture.hpp>
#include <Shader/Shader.hpp>

class SkyBox {
public:
    SkyBox();

    ~SkyBox();

    void Render(const Mat4f &viewProjection, const Point3df &cameraPos) const;

    void LoadShaders();

private:
    void initSkyBox();

    GLuint m_cubemapTexture{};
    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_shaderProgram{};
    GLint m_uniformViewProjection{};
    GLint m_uniformModel{};
    std::array<Texture, 6> m_textures;
};
