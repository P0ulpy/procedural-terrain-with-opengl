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
    std::vector<Trianglef*> triangles;


    MapGenerator(int screenW, int screenH) {
        cols = screenW / scale;
        rows = screenH / scale;
    };

    void Render()
    {
        for (auto triangle : triangles)
            triangle->render();
    }

    void Generate()
    {
        Point2f p0{ -1, 1 };
        Point2f p1{ 0, 1 };
        Point2f p2{ -1,0 };
        Trianglef triangle{ p0, p1, p2 };
        triangles.push_back(&triangle);
    }
};