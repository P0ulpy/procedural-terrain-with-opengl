#include "TerrainGenerator.hpp"

#include "../GameLoop/GameLoop.hpp"

TerrainGenerator::TerrainGenerator(Terrain *terrain)
    : m_terrain(terrain)
{}

void TerrainGenerator::Update(float deltaTime)
{
    auto camPos = GameLoop::Instance()->camera->GetTransform().pos;

    auto chunkIndex = ChunkContainer::GetChunkIndex(camPos.x, camPos.z);

    if (m_lastChunkIndex != chunkIndex)
    {
        //GenerateChunks if we are in a new chunk
        GenerateNewChunks(chunkIndex.first, chunkIndex.second);
        m_lastChunkIndex = chunkIndex;
    }
}

void TerrainGenerator::GenerateNewChunks(int32_t chunkX, int32_t chunkZ)
{
    m_newGeneratedChunks = 0;

    m_terrain->GetChunks().GetActiveChunks().clear();

    // Generate chunks around us
    for (int x = chunkX - m_chunksAroundUs; x <= chunkX + m_chunksAroundUs; ++x)
        for (int z = chunkZ - m_chunksAroundUs; z <= chunkZ + m_chunksAroundUs; ++z)
            SetChunkActive(x, z);

    std::cout << "Number of new chunks generated : " << m_newGeneratedChunks << std::endl;
}

void TerrainGenerator::GenerateAllChunks(int playerPosX, int playerPosZ)
{
    m_terrain->Cleanup();

    m_perlin.~PerlinNoise();
    m_perlin = PerlinNoise(m_frequency, m_amplitude, m_lacunarity, m_persistance);

    auto chunkIndex = ChunkContainer::GetChunkIndex(playerPosX, playerPosZ);

    // Generate chunks around us
    for (int x = chunkIndex.first - m_chunksAroundUs; x < chunkIndex.first + m_chunksAroundUs; ++x)
        for (int z = chunkIndex.second - m_chunksAroundUs; z < chunkIndex.second + m_chunksAroundUs; ++z)
            SetChunkActive(x, z);

    m_terrain->GenerateVertices();
}

void TerrainGenerator::SetChunkActive(int32_t chunkX, int32_t chunkZ)
{
    auto& chunks = m_terrain->GetChunks();
    auto* chunk = &chunks(chunkX, chunkZ);

    if (!chunk->IsGenerated())
    {
        ++m_newGeneratedChunks;
        GenerateChunk(chunkX, chunkZ);
    }

    chunks.GetActiveChunks().push_back(chunk);
}

void TerrainGenerator::GenerateChunk(int32_t chunkX, int32_t chunkZ)
{
    // position of up-left corner of the chunk
    int32_t chunkWorldPosX = chunkX * Chunk::SIZE - Chunk::SIZE / 2+ chunkX * - 1;
    int32_t chunkWorldPosZ = chunkZ * Chunk::SIZE - Chunk::SIZE / 2+ chunkZ * - 1;

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

    m_terrain->AddChunk(chunkX, chunkZ, vertices, indices);
}

void TerrainGenerator::SetSeed(unsigned int seed)
{
    m_perlin.setSeed(seed);
    m_seed = static_cast<int>(seed);
}

double TerrainGenerator::ComputeElevation(float x, float z) const
{
    const double nx = x / Chunk::SIZE - 0.5;
    const double nz = z / Chunk::SIZE - 0.5;

    double elevation = m_perlin.fractal(m_octaves, nx, nz);

    elevation = std::pow(std::abs(elevation), m_redistribution);

    return elevation;
}
