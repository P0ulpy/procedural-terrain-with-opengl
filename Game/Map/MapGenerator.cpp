#include "MapGenerator.h"

#include <math.h>

MapGenerator::MapGenerator(unsigned int width, unsigned int height)
        : m_width(static_cast<int>(width)), m_height(static_cast<int>(height)) {}

void MapGenerator::Generate(int playerPosX, int playerPosZ) {
    vertices.clear();
    indices.clear();



    for (float i = playerPosZ - renderDistance; i < playerPosZ + renderDistance; i++)
    {

        for (float j = playerPosX - renderDistance; j < playerPosX + renderDistance; j++)
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

            vertices.push_back(i);
            vertices.push_back(elevation * 20);
            vertices.push_back(j);

            vertices.push_back(i / ((renderDistance * 2) - 1));
            vertices.push_back(j / ((renderDistance * 2) - 1));
        }

    }

    for (unsigned int i = 0; i < renderDistance * 2 - 1; i++)       // for each row a.k.a. each strip
    {
        for (unsigned int j = 0; j < renderDistance * 2; j++)      // for each column
        {
            for (int k = 0; k < 2; k++)      // for each side of the strip
            {
                indices.push_back(j + (renderDistance * 2) * (i + k));
            }
        }
    }

    m_triangle.GenerateVertices(vertices, indices, (renderDistance * 2), (renderDistance * 2));
}

void MapGenerator::setSeed(unsigned int seed) {
    m_perlin.setSeed(seed);
}

