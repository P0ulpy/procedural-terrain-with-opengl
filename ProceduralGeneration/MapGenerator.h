#include<vector>

#include <iostream>
#include "../Renderer/Shape.h"
#include "ProceduralAlgo/PerlinNoise.h"
#include <math.h>
#include <cmath>
#include "../Game/Matrix.h"


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

    //Parameters:
    float m_frequency = 1.0f;
    //De 0 à 10
    unsigned int m_redistribution = 2;

    MapGenerator(unsigned int width, unsigned int height) {};

    void setSeed(unsigned int seed)
    {
		m_perlin.setSeed(seed);
	}

    template<typename T>
    void Render(const Mat4<T>& viewProjection)
    {
        m_triangle.Render(viewProjection);
    }

    void Generate();
};