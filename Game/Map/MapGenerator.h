#include <vector>
#include <iostream>

#include <Terrain.h>
#include <ProceduralAlgo/PerlinNoise.h>

class MapGenerator
{
public:
    MapGenerator();

    float m_frequency = 0.4f, m_amplitude = 1.f, m_lacunarity = 2.f, m_persistance = 0.5f, m_redistribution = 2.f;
    int m_octaves = 8;

    int generationDistance = 50;
    int maxHeight = 50;
    int terraces = 30;
    int m_seed;

    int m_chunksAroundUs = 2;

public:
    template<typename T>
    void Render(const Mat4<T>& viewProjection);

    [[nodiscard]] double ComputeElevation(float x, float z) const;

    void GenerateAllChunks(int playerPosX, int playerPosZ);

    [[nodiscard]] int GetSeed() const { return m_seed; };
    void SetSeed(unsigned int seed);

private:
    void GenerateChunk(int32_t chunkX, int32_t chunkZ);

private:
    Terrain m_terrain;
    PerlinNoise m_perlin;

    float m_textureRepeat = 10.0f;
};

#include "MapGenerator.tpp"