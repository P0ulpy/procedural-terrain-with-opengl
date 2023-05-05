#pragma once

#include <vector>
#include <GL/glew.h>

#include "Texture.h"

class Chunk {
public:
    constexpr static int32_t SIZE = 64;

    Chunk();

    ~Chunk();

    void Cleanup();

    // un chunk n'est pas renderable tel quel c'est terrain qui construit un 'super mesh', mais Chunk génère les vertices qui le compose

    void Generate(const std::vector<float> &vertices, const std::vector<uint32_t> &indices, GLuint program);

    void GenerateVertices();

    void Render() const;

    bool getGenerated() const { return m_generated; }

    size_t GetVerticesCount() const;

private:
    GLuint VAO{}, VBO{}, EBO{};
    std::vector<float> m_vertices{};
    std::vector<uint32_t> m_indices{};

    GLsizei NUM_VERTS_PER_STRIPS = 0;
    GLsizei NUM_STRIPS = 0;

    GLuint m_program{};

    Texture *grassTexture{};
    Texture *rockTexture{};
    Texture *sandTexture{};
    Texture *waterTexture{};
    Texture *snowTexture{};

    bool m_generated = false;
};
