#pragma once

#include <vector>
#include <SFML/System/Clock.hpp>

#include <Renderable/IRenderable.hpp>
#include "../../../Map/ChunkContainer.hpp"
#include <Renderable/Terrain/Chunk.hpp>
#include <Shader/Shader.hpp>
#include <Texture/Texture.hpp>
#include <Math/Matrix.hpp>

class Terrain : public IRenderable
{
public:
    Terrain() = default;
    ~Terrain() override = default;

    void Load() override;
    void Render(Camera& camera) override;
    void Cleanup() override;

    void GenerateVertices();
    void AddChunk(int32_t chunkX, int32_t chunkZ, const std::vector<float>& vertices, const std::vector<uint32_t>& indices);

private:
    sf::Clock waterClock;
    Texture grassTexture, rockTexture, sandTexture, waterTexture, snowTexture;
    uint32_t m_program {};

    ChunkContainer m_chunks;
};