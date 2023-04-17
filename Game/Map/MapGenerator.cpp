#include "MapGenerator.h"

#include <cmath>

MapGenerator::MapGenerator(unsigned int width, unsigned int height)
        : m_width(width)
        , m_height(height)
{}

void MapGenerator::Generate()
{
    vertices.clear();
    indices.clear();

    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            double nx = (float)i / (float)m_width - 0.5;
            double ny = j / m_height - 0.5;

            float e = m_frequency * PerlinNoise::noise(m_frequency * nx, m_frequency * ny) +
                (m_frequency / 2) * PerlinNoise::noise(m_frequency * 2 * nx, m_frequency * 2 * ny) +
                (m_frequency / 4) * PerlinNoise::noise(m_frequency * 4 * nx, m_frequency * 4 * ny) +
                (m_frequency / 8) * PerlinNoise::noise(m_frequency * 8 * nx, m_frequency * 8 * ny) +
                (m_frequency / 16) * PerlinNoise::noise(m_frequency * 16 * nx, m_frequency * 16 * ny)
                ;
            e = e / (m_frequency + (m_frequency / 2) + (m_frequency / 4) + (m_frequency / 8) + (m_frequency / 16));

            float elevation;
            if (std::signbit(e) == 1)
            {
                elevation = pow(e * 0.8, -m_redistribution);
            }
            else
            {
                elevation = pow(e * 0.8, m_redistribution);
            }


            vertices.push_back(i);
            vertices.push_back(elevation * (float)m_height / 4);
            vertices.push_back(j);
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

void MapGenerator::setSeed(unsigned int seed)
{
    m_perlin.setSeed(seed);
}
