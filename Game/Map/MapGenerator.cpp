#include "MapGenerator.h"

MapGenerator::MapGenerator()= default;

void MapGenerator::GenerateAllChunks(int playerPosX, int playerPosZ) {

    m_terrain.FreeMemory();

    auto chunkIndex = ChunkContainer::GetChunkIndex(0, 0);

    // Generate chunks around us
    for (int x = chunkIndex.first - m_chunksAroundUs; x < chunkIndex.first + m_chunksAroundUs; ++x)
        for (int z = chunkIndex.second - m_chunksAroundUs; z < chunkIndex.second + m_chunksAroundUs; ++z)
            GenerateChunk(x, z);

    m_terrain.GenerateVertices();
}

void MapGenerator::GenerateChunk(int32_t chunkX, int32_t chunkZ)
{
    // position of up-left corner of the chunk
    int32_t chunkWorldPosX = chunkX * Chunk::SIZE;
    int32_t chunkWorldPosZ = chunkZ * Chunk::SIZE;

    // vectors size reservation
    //constexpr size_t verticesPerRow = Chunk::SIZE * Chunk::SIZE;
    //constexpr size_t verticesCount = verticesPerRow * 5; // 5 represent the count of vertices we add each time we loop
    std::vector<float> vertices;//(verticesCount);
    //constexpr size_t indicesCount = ((Chunk::SIZE - 1) * Chunk::SIZE) * 2;
    std::vector<uint32_t> indices;//(indicesCount);

    for(int x = chunkWorldPosX; x < chunkWorldPosX + Chunk::SIZE; ++x)
    {
        for(int z = chunkWorldPosZ; z < chunkWorldPosZ + Chunk::SIZE; ++z)
        {
            /*if((z + 1 == chunkWorldPosZ + Chunk::SIZE) || (x + 1 == chunkWorldPosX + Chunk::SIZE))
            {
                vertices.push_back((float)x);
                vertices.push_back(30.f);
                vertices.push_back((float)z);
                vertices.push_back((float)x / m_textureRepeat);
                vertices.push_back((float)z / m_textureRepeat);

                continue;
            }*/

            vertices.push_back((float)x);

            auto elevation = (float)ComputeElevation((float)x, (float)z);

            // TODO : Prototype a "layer" system for the terrain witch can process elevation through a list of layers without having to hardcode it here

            constexpr float water_level = 0.005f;
            if (elevation <= water_level)
                vertices.push_back(water_level);
            else
                vertices.push_back(elevation * (float)maxHeight);

            vertices.push_back((float)z);
            vertices.push_back((float)x / m_textureRepeat);
            vertices.push_back((float)z / m_textureRepeat);
        }
    }

    for (uint32_t i = 0; i < Chunk::SIZE - 1; ++i)
        for (uint32_t j = 0; j < Chunk::SIZE; ++j)
            for (uint32_t k = 0; k < 2; ++k)
                indices.push_back(j + Chunk::SIZE * (i + k));

    m_terrain.AddChunk(chunkX, chunkZ, vertices, indices);
}

void MapGenerator::SetSeed(unsigned int seed)
{
    m_perlin.setSeed(seed);
    m_seed = static_cast<int>(seed);
}

double MapGenerator::ComputeElevation(float x, float z) const
{
    double nx = x / 16 - 0.5;
    double nz = z / 16 - 0.5;

    double elevation =
        m_frequency * PerlinNoise::noise(1 * m_frequency * nx, 1 * m_frequency * nz) +
        m_frequency * 0.5 * PerlinNoise::noise(2 * m_frequency * nx, 2 * m_frequency * nz) +
        m_frequency * 0.25 * PerlinNoise::noise(4 * m_frequency * nx, 4 * m_frequency * nz) +
        m_frequency * 0.13 * PerlinNoise::noise(8 * m_frequency * nx, 8 * m_frequency * nz) +
        m_frequency * 0.06 * PerlinNoise::noise(16 * m_frequency * nx, 16 * m_frequency * nz) +
        m_frequency * 0.03 * PerlinNoise::noise(32 * m_frequency * nx, 32 * m_frequency * nz);

    elevation = elevation / (m_frequency + (m_frequency * 0.5) + (m_frequency * 0.25) + (m_frequency * 0.13) + (m_frequency * 0.06) + (m_frequency * 0.03));
    elevation = std::pow(std::abs(elevation), m_redistribution);
    return elevation;
}



