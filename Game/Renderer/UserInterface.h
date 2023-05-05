#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics/RenderWindow.hpp"

class UserInterface {
public:
    UserInterface();

    static void drawInfo(float dt, int vertices);
};
