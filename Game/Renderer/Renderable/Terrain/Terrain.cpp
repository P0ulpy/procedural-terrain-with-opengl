#include "Terrain.hpp"

#include "gl/glew.h"
#include "SFML/Graphics/Image.hpp"

void Terrain::Load()
{
    // TODO : Put in terrain class, chunk should not be responsible for loading shaders
    ShaderInfo shader[] = {
            { GL_VERTEX_SHADER,   "Assets/Shaders/terrain.vert" },
            { GL_FRAGMENT_SHADER, "Assets/Shaders/terrain.frag" },
            { GL_NONE, nullptr }
    };

    m_program = Shader::LoadShaders(shader);

    glUseProgram(m_program);
}

void Terrain::Cleanup()
{
    m_chunks.FreeChunks();
    //glDeleteProgram(m_program);
}

void Terrain::Render(Camera& camera)
{
    glUseProgram(m_program);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glActiveTexture(GL_TEXTURE0);
    grassTexture.Bind();

    glActiveTexture(GL_TEXTURE1);
    rockTexture.Bind();

    glActiveTexture(GL_TEXTURE2);
    sandTexture.Bind();

    glActiveTexture(GL_TEXTURE3);
    waterTexture.Bind();

    glActiveTexture(GL_TEXTURE4);
    snowTexture.Bind();

    glUniform1i(glGetUniformLocation(m_program, "grassTexture"), 0);
    glUniform1i(glGetUniformLocation(m_program, "rockTexture"), 1);
    glUniform1i(glGetUniformLocation(m_program, "sandTexture"), 2);
    glUniform1i(glGetUniformLocation(m_program, "waterTexture"), 3);
    glUniform1i(glGetUniformLocation(m_program, "snowTexture"), 4);

    float time = waterClock.getElapsedTime().asSeconds();
    GLint timeLocation = glGetUniformLocation(m_program, "time");
    glUniform1f(timeLocation, time);

    auto model = Mat4f::Identity();
    auto mvp = model * camera.GetViewProjectionMatrix();

    auto mvpLocation = glGetUniformLocation(m_program, "model");

    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.Data());

    for(auto* chunk : m_chunks.GetActiveChunks())
    {
        chunk->Render(camera);
    }

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    Texture::Unbind();
}

void Terrain::AddChunk(
        int32_t chunkX,
        int32_t chunkZ,
        const std::vector<float>& vertices,
        const std::vector<uint32_t>& indices)
{
    m_chunks(chunkX, chunkZ)
        .Generate(vertices, indices, m_program);
}

void Terrain::GenerateVertices()
{
    for(auto& [key, chunk] : m_chunks.GetData())
    {
        chunk.Load();
    }
}
