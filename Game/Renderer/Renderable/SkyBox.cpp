#include "SkyBox.hpp"

void SkyBox::Load()
{
    LoadShaders();
    initSkyBox();
}

SkyBox::~SkyBox() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void SkyBox::Render(Camera& camera)
{
    glUseProgram(m_shaderProgram);
    glDepthMask(GL_FALSE);
    glBindVertexArray(m_vao);

    glUniformMatrix4fv(m_uniformViewProjection, 1, GL_FALSE, camera.GetViewProjectionMatrix().Data());
    Mat4<float> modelMatrix = Mat4<float>::Translation(camera.GetTransform().pos);
    glUniformMatrix4fv(m_uniformModel, 1, GL_FALSE, modelMatrix.Data());

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture);
    int skyboxUniLoc = glGetUniformLocation(m_shaderProgram, "skybox");
    glUniform1i(skyboxUniLoc, 0);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}

void SkyBox::initSkyBox() {
    constexpr float skyboxVertices[] = {
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);


    glGenTextures(1, &m_cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture);

    for (int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
                     static_cast<GLsizei>(m_textures[i].GetImage().getSize().x),
                     static_cast<GLsizei>(m_textures[i].GetImage().getSize().y), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     m_textures[i].GetImage().getPixelsPtr());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void SkyBox::LoadShaders()
{
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "Assets/Shaders/skybox.vert"},
            {GL_FRAGMENT_SHADER, "Assets/Shaders/skybox.frag"},
            {GL_NONE,            nullptr}
    };

    m_shaderProgram = Shader::LoadShaders(shaders);
    m_uniformViewProjection = glGetUniformLocation(m_shaderProgram, "viewProjection");
    m_uniformModel = glGetUniformLocation(m_shaderProgram, "model");
}