//
// Created by Flo on 20/04/2023.
//

#include "TerrainScene.hpp"

#include <Renderable/Terrain/Terrain.hpp>
#include <Renderable/SkyBox.hpp>

#include "../Map/TerrainGenerator.hpp"
#include "../UISystem/UiWindow.hpp"

void TerrainScene::Init()
{
    AddObject<SkyBox>(new SkyBox());

    auto terrain = new Terrain();
    auto terrainGenerator = new TerrainGenerator(terrain);
    AddObject<TerrainGenerator>(terrainGenerator);
    AddObject<Terrain>(terrain);

    terrainGenerator->SetSeed(121);
    terrainGenerator->GenerateAllChunks(0, 0);

    AddObject<UIWindow>(new UIWindow(
            "Test",
            ImVec2(300, 40),
            ImGuiCond_Always,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing
    ));
}