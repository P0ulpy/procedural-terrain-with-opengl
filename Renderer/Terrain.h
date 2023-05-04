#pragma once

#include <vector>
#include <SFML/System/Clock.hpp>

#include "Shader.h"
#include "Texture.h"

#include "Math/Matrix.hpp"
#include "Chunk.hpp"
#include "ChunkContainer.hpp"

class Terrain
{
public:
    Terrain();

    void Render(const Mat4f &viewProjection);

    void GenerateVertices();
    void AddChunk(int32_t chunkX, int32_t chunkZ, const std::vector<float>& vertices, const std::vector<uint32_t>& indices);

    void FreeMemory();
    ~Terrain();

private:
    ChunkContainer m_chunks;

    Texture grassTexture, rockTexture, sandTexture, waterTexture, snowTexture;

    sf::Clock waterClock;
    GLsizei m_num_strips { Chunk::SIZE - 1 };
    GLsizei m_num_verts_per_strip { Chunk::SIZE * 2 };

    GLuint chunkVAO, chunkVBO, chunkEBO;

    uint32_t m_program {};
};