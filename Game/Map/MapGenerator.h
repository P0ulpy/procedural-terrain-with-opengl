#include <vector>
#include <iostream>

#include <Terrain.h>
#include <ProceduralAlgo/PerlinNoise.h>

class MapGenerator
{
public:
    MapGenerator();

    // Parameters:
    // ELEVATION OCTAVES 
    float m_frequency = 0.1f;
    // ELEVATION REDISTRIBUTION
    float m_redistribution = 3;
    // GENERATION DISTANCE 
    int generationDistance = 50;
    // MAX HEIGHT OF MOUNTAIN
    int maxHeight = 50;
    // NUMBER OF TERRACES
    int terraces = 30;
    // SET SEED OF PERLIN NOISE
    int m_seed;

    // NUMBER OF CHUNKS AROUND US
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