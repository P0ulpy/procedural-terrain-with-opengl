#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>

#include <valarray>

template<typename T>
Terrain<T>::Terrain()
        : grassTexture("Assets/Textures/grass.bmp"),
          rockTexture("Assets/Textures/rock.bmp"), sandTexture("Assets/Textures/sand.bmp") {

}

template<typename T>
Terrain<T>::~Terrain() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
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
                       (void *) (sizeof(unsigned int)
                                 * m_num_verts_per_strip
                                 * strip)); // offset to starting index
    }

    grassTexture.unbind();
    rockTexture.unbind();
    sandTexture.unbind();

    glDisable(GL_DEPTH_TEST);
}

template<typename T>
void Terrain<T>::GenerateVertices(std::vector<float> vertices, std::vector<uint32_t> indices, int32_t map_width,
                                  int32_t map_height) {
    m_num_strips = map_width - 1;
    m_num_verts_per_strip = map_height * 2;

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
    /*       for (auto& triangle : triangles)
               triangle->render(viewProjection);*/
    GLuint terrainVAO, terrainVBO, terrainEBO;
    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(float),       // size of vertices buffer
                 &vertices[0],                          // pointer to first element
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    // Texture coordinates attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &terrainEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int), // size of indices buffer
                 &indices[0],                           // pointer to first element
                 GL_STATIC_DRAW);

    glBindVertexArray(terrainVAO);
}
