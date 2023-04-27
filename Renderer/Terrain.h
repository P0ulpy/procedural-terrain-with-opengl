#pragma once

#include <vector>

#include "Shader.h"
#include "Texture.h"

#include "../Game/Matrix.h"

template<typename T>
class Terrain {
    using vertex_type = vertex_struct_texture_3D<T>;


public:
    Terrain();

    void Render(const Mat4<T> &viewProjection);

    void GenerateVertices(int nbrOfChunks);
    void GenerateChunks(std::vector<float> vertices, std::vector<uint32_t> indices, int32_t map_width, int32_t map_height);

    void FreeMemory();
    ~Terrain();

private:
    Texture grassTexture, rockTexture, sandTexture;

    uint32_t m_num_strips{};
    uint32_t m_num_verts_per_strip{};


    T m_angle = 0.0f;
    GLuint chunkVAO, chunkVBO, chunkEBO;

    std::vector<GLuint> terrainVAO, terrainVBO, terrainEBO;
    std::vector<std::vector<float>> m_vertices;
    std::vector<std::vector<uint32_t>> m_indices;
    std::vector<uint32_t> NUM_STRIPS;
    std::vector<uint32_t> NUM_VERTS_PER_STRIPS;

    uint32_t m_vao{};
    uint32_t m_vbo{};
    uint32_t m_program{};
};

#include "Terrain.tpp"