//
// Created by Flo on 29/04/2023.
//

#include <gl/glew.h>

#include "Chunk.hpp"
#include "Shader.h"
#include "Math/Matrix.hpp"

Chunk::Chunk()
{
    // TODO : Put in terrain class, chunk should not be responsible for loading shaders
    ShaderInfo shader[] = {
            { GL_VERTEX_SHADER,   "Assets/Shaders/terrain.vert" },
            { GL_FRAGMENT_SHADER, "Assets/Shaders/terrain.frag" },
            { GL_NONE, nullptr }
    };

    m_program = Shader::loadShaders(shader);
}

Chunk::~Chunk()
{
    Cleanup();
}

void Chunk::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Chunk::Generate(const std::vector<float> &vertices,
                     const std::vector<uint32_t> &indices,
                     GLuint program, Texture* grassTexture, Texture* rockTexture, Texture* sandTexture, Texture* waterTexture, Texture* snowTexture
                     )
{
    m_vertices = vertices;
    m_indices = indices;
    m_program = program;
    this->grassTexture = grassTexture;
    this->rockTexture = rockTexture;
    this->sandTexture = sandTexture;
    this->waterTexture = waterTexture;
    this->snowTexture = snowTexture;
}

void Chunk::GenerateVertices()
{
    glUseProgram(m_program);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(float),       // size of vertices buffer
                 &m_vertices[0],                          // pointer to first element
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);

    // Texture coordinates attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(unsigned int), // size of indices buffer
                 &m_indices[0],                           // pointer to first element
                 GL_STATIC_DRAW);

    glBindVertexArray(VAO);
}

void Chunk::Render(const Mat4f& viewProjection)
{
    glEnable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    grassTexture->bind();

    glActiveTexture(GL_TEXTURE1);
    rockTexture->bind();

    glActiveTexture(GL_TEXTURE2);
    sandTexture->bind();

    glActiveTexture(GL_TEXTURE3);
    waterTexture->bind();

    glActiveTexture(GL_TEXTURE4);
    snowTexture->bind();

    glUniform1i(glGetUniformLocation(m_program, "grassTexture"), 0);
    glUniform1i(glGetUniformLocation(m_program, "rockTexture"), 1);
    glUniform1i(glGetUniformLocation(m_program, "sandTexture"), 2);
    glUniform1i(glGetUniformLocation(m_program, "waterTexture"), 3);
    glUniform1i(glGetUniformLocation(m_program, "snowTexture"), 4);

    Mat4f model = Mat4f::Identity();
    // TODO : Use the Transformable utility tool instead
    //Mat4f model = Mat4f::RotationY(0) * Mat4f::Translation(0.f, 0.f, 0.f);

    // TODO : Use camera viewProjection instead of computing it by hand each times
    Mat4f mvp = viewProjection * model;

    auto mvpLocation = glGetUniformLocation(m_program, "model");

    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.Data());
    // render the mesh triangle strip by triangle strip - each row at a time
    for (unsigned int strip = 0; strip < Chunk::SIZE - 1; ++strip) {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                       Chunk::SIZE * 2, // number of indices to render
                       GL_UNSIGNED_INT,     // index data type
                       (void *) (sizeof(int)
                                 * (Chunk::SIZE * 2)
                                 * strip)); // offset to starting index
    }

    glDisable(GL_DEPTH_TEST);

    grassTexture->unbind();
    rockTexture->unbind();
    sandTexture->unbind();
    waterTexture->unbind();
    snowTexture->unbind();
}
