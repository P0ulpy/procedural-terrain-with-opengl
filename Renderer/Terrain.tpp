#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <iostream>

#include <valarray>

template<typename T>
Terrain<T>::Terrain()
        : grassTexture("Assets/Textures/grass.png"),
          rockTexture("Assets/Textures/rock.bmp"), sandTexture("Assets/Textures/sand.bmp") {

}

template<typename T>
Terrain<T>::~Terrain() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

template<typename T>
void Terrain<T>::FreeMemory() {
    for(auto vao : terrainVAO)
		glDeleteVertexArrays(1, &vao);
    for (auto vbo : terrainVBO)
        glDeleteBuffers(1, &vbo);
    for (auto ebo : terrainEBO)
        glDeleteBuffers(1, &ebo);
    glDeleteProgram(m_program);

    terrainVAO.clear();
    terrainVBO.clear();
    terrainEBO.clear();

    m_vertices.clear();
    m_indices.clear();

    NUM_STRIPS.clear();
    NUM_VERTS_PER_STRIPS.clear();

}

template<typename T>
void Terrain<T>::Render(const Mat4<T> &viewProjection) {
    glEnable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    grassTexture.bind();

    glActiveTexture(GL_TEXTURE1);
    rockTexture.bind();

    glActiveTexture(GL_TEXTURE2);
    sandTexture.bind();

    glUniform1i(glGetUniformLocation(m_program, "grassTexture"), 0);
    glUniform1i(glGetUniformLocation(m_program, "rockTexture"), 1);
    glUniform1i(glGetUniformLocation(m_program, "sandTexture"), 2);

    Mat4<T> model;

    //Rotation sur l'axe Y
    model(0, 0) = std::cos(m_angle);
    model(0, 2) = std::sin(m_angle);
    model(2, 0) = -std::sin(m_angle);
    model(2, 2) = std::cos(m_angle);

    model(1, 1) = 1.0f;
    model(3, 3) = 1.0f;

    model(2, 3) = -5.0f;

    Mat4<T> mvp = viewProjection * model;

    auto mvpLocation = glGetUniformLocation(m_program, "model");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.data());
    // render the mesh triangle strip by triangle strip - each row at a time
    for (unsigned int strip = 0; strip < m_num_strips; ++strip) {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                       m_num_verts_per_strip, // number of indices to render
                       GL_UNSIGNED_INT,     // index data type
                       (void *) (sizeof(int)
                                 * m_num_verts_per_strip
                                 * strip)); // offset to starting index
    }
    glDisable(GL_DEPTH_TEST);

}

template<typename T>
void Terrain<T>::GenerateChunks(
    std::vector<float> vertices,
    std::vector<uint32_t> indices,
    int32_t map_width,
    int32_t map_height)
{
    terrainVAO.push_back(chunkVAO);
    terrainVBO.push_back(chunkVBO);
    terrainEBO.push_back(chunkEBO);

    m_vertices.push_back(vertices);
    m_indices.push_back(indices);
    NUM_STRIPS.push_back(map_width - 1);    
    NUM_VERTS_PER_STRIPS.push_back(map_height * 2);
}

template<typename T>
void Terrain<T>::GenerateVertices(int nbrOfChunks)
{

    for (int i = 0; i < nbrOfChunks; ++i)
    {
        m_num_strips = NUM_STRIPS[i];
        m_num_verts_per_strip = NUM_VERTS_PER_STRIPS[i];

        ShaderInfo shader[] = {
               {GL_VERTEX_SHADER,   "Assets/Shaders/terrain.vert"},
               {GL_FRAGMENT_SHADER, "Assets/Shaders/terrain.frag"},
               {GL_NONE,            nullptr}
        };

        auto program = Shader::loadShaders(shader);
        glUseProgram(program);
        m_program = program;

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        glGenVertexArrays(1, &terrainVAO[i]);
        glBindVertexArray(terrainVAO[i]);

        glGenBuffers(1, &terrainVBO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, terrainVBO[i]);
        glBufferData(GL_ARRAY_BUFFER,
            m_vertices[i].size() * sizeof(float),       // size of vertices buffer
            &m_vertices[i][0],                          // pointer to first element
            GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr);
        glEnableVertexAttribArray(0);

        // Texture coordinates attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &terrainEBO[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            m_indices[i].size() * sizeof(unsigned int), // size of indices buffer
            &m_indices[i][0],                           // pointer to first element
            GL_STATIC_DRAW);

        glBindVertexArray(terrainVAO[i]);

    }

}
