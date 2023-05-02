#pragma once

#include <array>
#include "Texture.h"
#include <vector>
#include "Shader.h"

using Point3f = Point3D<float>;

class SkyBox {
public:
    SkyBox();

    ~SkyBox();

    void Render(const Mat4<float> &viewProjection, const Point3f &cameraPos) const;

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
