#include <vector>
#include <iostream>

#include <PerlinNoise.hpp>
#include <Renderer/Renderable/Terrain/Terrain.hpp>

#include <Objects/IUpdatable.hpp>

class TerrainGenerator : public IUpdatable
{
public:
    TerrainGenerator() = delete;
    ~TerrainGenerator() override = default;
    explicit TerrainGenerator(Terrain* terrain);

    void Update(float deltaTime) override;

    [[nodiscard]] double ComputeElevation(float x, float z) const;

    void GenerateAllChunks(int playerPosX, int playerPosZ);

    [[nodiscard]] int GetSeed() const { return m_seed; };
    void SetSeed(unsigned int seed);

    bool IsNeedToGenerateAllChunks() const { return m_needToGenerateAllChunks; }
    void SetNeedToGenerateAllChunks() { m_needToGenerateAllChunks = true; }
public:
    int m_seed = 0;

    float m_frequency = 0.4f, m_amplitude = 1.f, m_lacunarity = 2.f, m_persistance = 0.5f, m_redistribution = 2.f;
    float m_textureRepeat = 10.0f;
    int m_octaves = 8;

    int generationDistance = 50;
    int maxHeight = 50;

    int m_chunksAroundUs = 8;

private:
    void GenerateNewChunks(int32_t chunkX, int32_t chunkZ);
    void GenerateChunk(int32_t chunkX, int32_t chunkZ);
    void SetChunkActive(int32_t chunkX, int32_t chunkZ);

private:
    Terrain* m_terrain { nullptr };
    PerlinNoise m_perlin;

    // Used for monitoring purposes
    int m_newGeneratedChunks = 0;
    ChunkContainer::Index m_lastChunkIndex { 0, 0 };

    bool m_needToGenerateAllChunks = false;
};