#include "Terrain.h"

#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>

Terrain::Terrain()
        : grassTexture("Assets/Textures/grass.png"),
          rockTexture("Assets/Textures/rock.bmp"),
          sandTexture("Assets/Textures/sand.bmp"),
          waterTexture("Assets/Textures/water.bmp"),
          snowTexture("Assets/Textures/neige.bmp")
{
    // TODO : Put in terrain class, chunk should not be responsible for loading shaders
    ShaderInfo shader[] = {
            { GL_VERTEX_SHADER,   "Assets/Shaders/terrain.vert" },
            { GL_FRAGMENT_SHADER, "Assets/Shaders/terrain.frag" },
            { GL_NONE, nullptr }
    };

    m_program = Shader::loadShaders(shader);
}

Terrain::~Terrain()
{
    FreeMemory();
}

void Terrain::FreeMemory()
{
    /* TODO : Vérifier si c'est nécessaire
    glDeleteVertexArrays(1, &chunkVAO);
    glDeleteBuffers(1, &chunkVBO);
    glDeleteBuffers(1, &chunkEBO);
    */

    m_chunks.FreeChunks();

    glDeleteProgram(m_program);
}

void Terrain::Render(const Mat4f &viewProjection)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    grassTexture.bind();

    glActiveTexture(GL_TEXTURE1);
    rockTexture.bind();

    glActiveTexture(GL_TEXTURE2);
    sandTexture.bind();

    glActiveTexture(GL_TEXTURE3);
    waterTexture.bind();

    glActiveTexture(GL_TEXTURE4);
    snowTexture.bind();

    glUniform1i(glGetUniformLocation(m_program, "grassTexture"), 0);
    glUniform1i(glGetUniformLocation(m_program, "rockTexture"), 1);
    glUniform1i(glGetUniformLocation(m_program, "sandTexture"), 2);
    glUniform1i(glGetUniformLocation(m_program, "waterTexture"), 3);
    glUniform1i(glGetUniformLocation(m_program, "snowTexture"), 4);

    float time = waterClock.getElapsedTime().asSeconds();
    GLint timeLocation = glGetUniformLocation(m_program, "time");
    glUniform1f(timeLocation, time);

    Mat4f model = Mat4f::Identity();
    // TODO : Use the Transformable utility tool instead
    //Mat4f model = Mat4f::RotationY(0) * Mat4f::Translation(0.f, 0.f, 0.f);

    // TODO : Use camera viewProjection instead of computing it by hand each times
    Mat4f mvp = viewProjection * model;

    auto mvpLocation = glGetUniformLocation(m_program, "model");

    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.Data());

    for(auto* chunk : m_chunks.m_activeChunks)
    {
        chunk->Render();
    }

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    grassTexture.unbind();
    rockTexture.unbind();
    sandTexture.unbind();
    waterTexture.unbind();
    snowTexture.unbind();
}

void Terrain::AddChunk(
        int32_t chunkX,
        int32_t chunkZ,
        const std::vector<float>& vertices,
        const std::vector<uint32_t>& indices)
{
    m_chunks(chunkX, chunkZ)
        .Generate(vertices, indices, m_program, &grassTexture, &rockTexture, &sandTexture, &waterTexture, &snowTexture);
}

void Terrain::GenerateVertices()
{
    for (auto& [key, chunk] : m_chunks.GetData())
    {
        chunk.GenerateVertices();
    }
}

