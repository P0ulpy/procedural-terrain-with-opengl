#include "MapGenerator.h"

#include <math.h>

MapGenerator::MapGenerator(unsigned int width, unsigned int height)
        : m_width(static_cast<int>(width)), m_height(static_cast<int>(height)) {}

void MapGenerator::Generate() {
    std::cout << "Redistribution : " << m_redistribution << std::endl;
    vertices.clear();
    indices.clear();

    for (float i = 0; i < m_height; i++)
    {
        for (float j = 0; j < m_width; j++)
        {
            double nx = i / m_width - 0.5;
            double ny = j / m_height - 0.5;

            float e = m_frequency * PerlinNoise::noise(m_frequency * nx, m_frequency * ny) +
                (m_frequency / 2) * PerlinNoise::noise(m_frequency * 2 * nx, m_frequency * 2 * ny) +
                (m_frequency / 4) * PerlinNoise::noise(m_frequency * 4 * nx, m_frequency * 4 * ny) +
                (m_frequency / 8) * PerlinNoise::noise(m_frequency * 8 * nx, m_frequency * 8 * ny) +
                (m_frequency / 16) * PerlinNoise::noise(m_frequency * 16 * nx, m_frequency * 16 * ny) + 
                (m_frequency / 32) * PerlinNoise::noise(m_frequency * 32 * nx, m_frequency * 32 * ny)
                ;
            e = e / (m_frequency + (m_frequency / 2) + (m_frequency / 4) + (m_frequency / 8) + (m_frequency / 16) + (m_frequency / 32));

            float elevation = std::pow(std::abs(e), m_redistribution);

            vertices.push_back(i);
            vertices.push_back(elevation * m_height / 4);
            vertices.push_back(j);

            vertices.push_back(i / (m_width - 1));
            vertices.push_back(j / (m_height - 1));
        }

    }


    for (unsigned int i = 0; i < m_height - 1; i++)       // for each row a.k.a. each strip
    {
        for (unsigned int j = 0; j < m_width; j++)      // for each column
        {
            for (unsigned int k = 0; k < 2; k++)      // for each side of the strip
            {
                indices.push_back(j + m_width * (i + k));
            }
        }
    }

    m_triangle.GenerateVertices(vertices, indices, m_width, m_height);
}

void MapGenerator::setSeed(unsigned int seed) {
    m_perlin.setSeed(seed);
}

