#pragma once

#include <vector>
#include <SFML/System/Clock.hpp>

#include <Renderer/Renderable/IRenderable.hpp>
#include <Renderer/Renderable/Terrain/Chunk.hpp>
#include <Renderer/Shader/Shader.hpp>
#include <Renderer/Texture/Texture.hpp>
#include <Renderer/Math/Matrix.hpp>
#include <Objects/Map/ChunkContainer.hpp>

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

    [[nodiscard]] ChunkContainer& GetChunks() { return m_chunks; }
    [[nodiscard]] size_t GetTotalVertices() const;

private:
    sf::Clock waterClock;
    uint32_t m_program {};

    Texture grassTexture = Texture ("Assets/Textures/grass.png" );
    Texture rockTexture = Texture ("Assets/Textures/rock.bmp" );
    Texture sandTexture = Texture ("Assets/Textures/sand.bmp" );
    Texture waterTexture = Texture ("Assets/Textures/water.bmp" );
    Texture snowTexture = Texture ("Assets/Textures/neige.bmp" );

    ChunkContainer m_chunks;
};