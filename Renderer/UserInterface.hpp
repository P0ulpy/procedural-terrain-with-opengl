#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics/RenderWindow.hpp"

using Point3f = Point3d<float>;

class UserInterface {
public:
    UserInterface();

    static void drawInfo(float dt, int vertices);
    static void drawTerrainParameters(int seed, MapGenerator mapGenerator, const Point3f &cameraPos);
};

#include "UserInterface.tpp"