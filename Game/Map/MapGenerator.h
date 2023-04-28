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
    Terrain<float> m_terrain;
    PerlinNoise m_perlin;
    using Point2f = Point2D<float>;
    using Point3f = Point3D<float>;
    
    float m_textureRepeat = 10.0f;
    int lastPlayerPosX, lastPlayerPosZ = 0;


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
    //SET SEED OF PERLIN NOISE
    int m_seed;
    //NUMBER OF CHUNKS AROUND US
    int m_chunksAroundUsX = 4;
    int m_chunksAroundUsZ = 4;

    int getSeed() {
        return m_seed;
    };
    template<typename T>
    void Render(const Mat4<T>& viewProjection);
    void Generate(int playerPosX, int playerPosZ, int genDistX, int genDistY);
    void GenerateAllChunks(int playerPosX, int playerPosZ);
    void setSeed(unsigned int seed);
    const std::vector<float> &getVertices() const;
 
    float CalculateElevation(float x, float z);
    float noise(float nx, float nz);
};

#include "MapGenerator.tpp"