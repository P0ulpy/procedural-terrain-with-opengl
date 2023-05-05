//
// Created by Flo on 20/04/2023.
//

#pragma once

#include "../GameLoop/Scene.hpp"
#include "../UISystem/UiText.hpp"
#include "../Map/TerrainGenerator.hpp"

class TerrainScene : public Scene
{
public:
    void Init() override;

protected:
    void OnUpdate(float deltaTime) override;

private:
    void SetVerticesMode(uint32_t mode);

private:
    // Objects
    Terrain* m_terrain = nullptr;
    TerrainGenerator* m_terrainGenerator = nullptr;

    // UI
    uint32_t m_verticesMode = 0;
    uint32_t m_verticesCount = 0;

    UIText* m_fpsText = nullptr;
    UIText* m_verticesCountText = nullptr;
    UIText* m_cameraPosText = nullptr;
    UIText* m_cameraChunkText = nullptr;
};
