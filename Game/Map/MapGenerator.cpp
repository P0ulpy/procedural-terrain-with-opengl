#include "MapGenerator.h"

#include <math.h>

MapGenerator::MapGenerator(){}

void MapGenerator::Generate(int playerPosX, int playerPosZ) {

    m_vertices.clear();
    m_indices.clear();
    for (float i = playerPosX - renderDistance; i < playerPosX + renderDistance; i++)
    {

        for (float j = playerPosZ - renderDistance; j < playerPosZ + renderDistance; j++)
        {
            
            double nx = i / 16 - 0.5;
            double ny = j / 16 - 0.5;

            float e = m_frequency * m_perlin.noise(m_frequency * nx, m_frequency * ny) +
                (m_frequency / 2) * m_perlin.noise(m_frequency * 2 * nx, m_frequency * 2 * ny) +
                (m_frequency / 4) * m_perlin.noise(m_frequency * 4 * nx, m_frequency * 4 * ny) +
                (m_frequency / 8) * m_perlin.noise(m_frequency * 8 * nx, m_frequency * 8 * ny) +
                (m_frequency / 16) * m_perlin.noise(m_frequency * 16 * nx, m_frequency * 16 * ny) +
                (m_frequency / 32) * m_perlin.noise(m_frequency * 32 * nx, m_frequency * 32 * ny)
                ;
            e = e / (m_frequency + (m_frequency / 2) + (m_frequency / 4) + (m_frequency / 8) + (m_frequency / 16) + (m_frequency / 32));

            float elevation = std::pow(std::abs(e), m_redistribution);

            m_vertices.push_back(i);
            m_vertices.push_back(elevation * 20);
            m_vertices.push_back(j);

            m_vertices.push_back(i / ((renderDistance * 2) - 1));
            m_vertices.push_back(j / ((renderDistance * 2) - 1));
        }

    }

    for (unsigned int i = 0; i < renderDistance * 2 - 1; i++)       // for each row a.k.a. each strip
    {
        for (unsigned int j = 0; j < renderDistance * 2; j++)      // for each column
        {
            for (int k = 0; k < 2; k++)      // for each side of the strip
            {
                m_indices.push_back(j + (renderDistance * 2) * (i + k));
            }
        }
    }

    m_terrain.GenerateVertices(m_vertices, m_indices, (renderDistance * 2), (renderDistance * 2));
}

void MapGenerator::setSeed(unsigned int seed) {
    m_perlin.setSeed(seed);
}

