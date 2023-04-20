#include <vector>
#include <iostream>

#include <Terrain.h>
#include <ProceduralAlgo/PerlinNoise.h>

enum BIOME {
	WATER,
	BEACH,
    FOREST,
    JUNGLE,
	SAVANNAH,
    MOUNTAIN,
	DESERT,
    SNOW
};

class MapGenerator
{
private:
    std::vector<unsigned int> m_indices;
    std::vector<float> m_vertices;
    
    using Point2f = Point2D<float>;
    using Point3f = Point3D<float>;

    Terrain<float> m_terrain;
    PerlinNoise m_perlin;

    float m_textureRepeat = 10.0f;

public:
    // Parameters:
    float m_frequency = 0.1f;
    // From 0 to 10
    float m_redistribution = 1;
    int renderDistance = 100;


    MapGenerator();

    //Temp or not?
    BIOME Biome(float e);

    template<typename T>
    void Render(const Mat4<T>& viewProjection);
    void Generate(int playerPosX, int playerPosZ);
    void setSeed(unsigned int seed);
};

#include "MapGenerator.tpp"