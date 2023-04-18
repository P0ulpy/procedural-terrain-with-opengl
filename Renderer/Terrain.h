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

    void
    GenerateVertices(std::vector<float> vertices, std::vector<uint32_t> indices, int32_t map_width, int32_t map_height);

    ~Terrain();

private:
    Texture grassTexture, rockTexture, sandTexture;

    uint32_t m_num_strips{};
    uint32_t m_num_verts_per_strip{};
    T m_angle = 0.0f;

    uint32_t m_vao{};
    uint32_t m_vbo{};
    uint32_t m_program{};
};

#include "Terrain.tpp"