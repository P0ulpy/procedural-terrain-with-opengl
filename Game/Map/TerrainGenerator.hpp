#include <vector>
#include <iostream>

#include <ProceduralAlgo/PerlinNoise.h>
#include <Renderable/Terrain/Terrain.hpp>

#include "../Objects/IUpdatable.hpp"

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

public:
    float m_frequency = 0.4f, m_amplitude = 1.f, m_lacunarity = 2.f, m_persistance = 0.5f, m_redistribution = 2.f;
    int m_octaves = 8;

    int generationDistance = 50;
    int maxHeight = 50;
    int terraces = 30;

    int m_chunksAroundUs = 2;

private:
    void GenerateChunk(int32_t chunkX, int32_t chunkZ);

private:
    Terrain* m_terrain { nullptr };
    PerlinNoise m_perlin;

    float m_textureRepeat = 10.0f;
    int m_seed = 0;
};