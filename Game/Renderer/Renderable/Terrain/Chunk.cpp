#include <gl/glew.h>

#include <Renderer/Renderable/Terrain/Chunk.hpp>

Chunk::Chunk() {}

void Chunk::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Chunk::AssignModel(const std::vector<float> &vertices,
                     const std::vector<uint32_t> &indices,
                     GLuint program)
{
    m_generated = true;
    m_vertices = std::move(vertices);
    m_indices = std::move(indices);
    m_program = program;

    Load();
}

void Chunk::Load()
{
    if(!m_generated)
        return;

    glUseProgram(m_program);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

void Chunk::Render(Camera& camera)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // render the mesh triangle strip by triangle strip - each row at a time
    for (unsigned int strip = 0; strip < Chunk::SIZE - 1; ++strip)
    {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                       Chunk::SIZE * 2,     // number of indices to render
                       GL_UNSIGNED_INT,     // index data type
                       (void *) (sizeof(int)
                                 * (Chunk::SIZE * 2)
                                 * strip)); // offset to starting index
    }
}