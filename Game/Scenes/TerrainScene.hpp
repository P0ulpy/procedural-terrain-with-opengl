//
// Created by Flo on 20/04/2023.
//

#pragma once

#include "../GameLoop/Scene.hpp"

class TerrainScene : public Scene
{
public:
    void Init() override;

    uint32_t verticesMode = 0;
};
