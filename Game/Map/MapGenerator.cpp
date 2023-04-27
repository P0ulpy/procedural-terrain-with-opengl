#include "MapGenerator.h"

MapGenerator::MapGenerator()= default;

void MapGenerator::GenerateAllChunks(int playerPosX, int playerPosZ) {

    m_terrain.FreeMemory();
    for (int x = 1; x <= m_chunksAroundUsX; x++) {
        for (int z = 1; z <= m_chunksAroundUsZ; z++) {

			Generate(playerPosX, playerPosZ, x * generationDistance , z * generationDistance);
		}
	}
    m_terrain.GenerateVertices(m_chunksAroundUsX * m_chunksAroundUsZ);

}

void MapGenerator::Generate(int playerPosX, int playerPosZ, int genDistX, int genDistZ) {
    m_vertices.clear();
    m_indices.clear();

    for (float x = playerPosX - genDistX; x < playerPosX + genDistX; x++)
    {
        for (float z = playerPosZ - genDistZ; z < playerPosZ + genDistZ; z++)
        {

            m_vertices.push_back(x);
            m_vertices.push_back(CalculateElevation(x,z) * maxHeight);
            m_vertices.push_back(z);

            m_vertices.push_back(x / m_textureRepeat);
            m_vertices.push_back(z / m_textureRepeat);
        }
    }

    for (unsigned int i = 0; i < genDistX * 2 - 1; i++)       // for each row a.k.a. each strip
    {
        for (unsigned int j = 0; j < genDistZ * 2; j++)      // for each column
        {
            for (int k = 0; k < 2; k++)      // for each side of the strip
            {
                m_indices.push_back(j + (genDistX * 2) * (i + k));
            }
        }
    }

    m_terrain.GenerateChunks(m_vertices, m_indices, (genDistX * 2), (genDistZ * 2));
}

void MapGenerator::setSeed(unsigned int seed) {
    m_perlin.setSeed(seed);
    m_seed = seed;
}

const std::vector<float> &MapGenerator::getVertices() const {
    return m_vertices;
}


float MapGenerator::CalculateElevation(float x, float z) {
    double nx = x / 16 - 0.5;
    double nz = z / 16 - 0.5;

    float e = 
        m_frequency * noise(1 * m_frequency * nx, 1 * m_frequency * nz) +
        m_frequency * 0.5 * noise(2 * m_frequency * nx, 2 * m_frequency * nz) +
        m_frequency * 0.25 * noise(4 * m_frequency * nx, 4 * m_frequency * nz) +
        m_frequency * 0.13 * noise(8 * m_frequency * nx, 8 * m_frequency * nz) +
        m_frequency * 0.06 * noise(16 * m_frequency * nx, 16 * m_frequency * nz) +
        m_frequency * 0.03 * noise(32 * m_frequency * nx, 32 * m_frequency * nz)
        ;

    e = e / (m_frequency + (m_frequency * 0.5) + (m_frequency * 0.25) + (m_frequency * 0.13) + (m_frequency * 0.06) + (m_frequency * 0.03));
    e = std::pow(std::abs(e), m_redistribution);

    return std::round(e * terraces) / terraces;
}

inline float MapGenerator::noise(float nx, float nz)
{
    return m_perlin.noise(nx, nz)/2 + 0.5;
}


