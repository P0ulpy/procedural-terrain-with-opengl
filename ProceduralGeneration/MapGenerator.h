#include<vector>
#include "Shape.h"

class MapGenerator
{
private:
    int cols, rows;
    const int scale = 4;
    

public:

    using Trianglef = Triangle<float>;
    using Point2f = Point2d<float>;
    std::vector<std::unique_ptr<Trianglef>> triangles;

    MapGenerator(int screenW, int screenH)
    {
        cols = screenW / scale;
        rows = screenH / scale;
    };

    void Render()
    {
        for (auto& triangle : triangles)
            triangle->render();
    }

    void Generate()
    {
        Point2f p0 { -1, 1 };
        Point2f p1 { 0, 1 };
        Point2f p2 { -1, 0 };
        Point2f p3 { 0,0 };

        triangles.push_back(std::make_unique<Trianglef>(p0, p1, p2));
        triangles.push_back(std::make_unique<Trianglef>(p1, p2, p3));
    }
};