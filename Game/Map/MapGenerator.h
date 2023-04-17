#include <vector>
#include <iostream>

#include <Triangle.h>
#include <ProceduralAlgo/PerlinNoise.h>

class MapGenerator
{
private:
    std::vector<unsigned int> indices;
    std::vector<float> vertices;
    int m_width, m_height;
    
    using Point2f = Point2D<float>;
    using Point3f = Point3D<float>;

    Triangle<float> m_triangle;
    PerlinNoise m_perlin;

public:
    // Parameters:
    float m_frequency = 1.0f;
    // From 0 to 10
    unsigned int m_redistribution = 2;

    MapGenerator(unsigned int width, unsigned int height);

    void setSeed(unsigned int seed);

    template<typename T>
    void Render(const Mat4<T>& viewProjection);

    void Generate();
};

#include "MapGenerator.tpp"