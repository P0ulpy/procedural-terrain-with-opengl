//
// Created by Flo on 20/04/2023.
//

#include "TerrainScene.hpp"

#include <Renderable/Terrain/Terrain.hpp>
#include <Renderable/SkyBox.hpp>

#include "../Map/TerrainGenerator.hpp"

void TerrainScene::Init()
{
    AddObject<SkyBox>(new SkyBox());

    auto terrain = new Terrain();
    auto terrainGenerator = new TerrainGenerator(terrain);
    AddObject<TerrainGenerator>(terrainGenerator);
    AddObject<Terrain>(terrain);

    terrainGenerator->SetSeed(121);
    terrainGenerator->GenerateAllChunks(0, 0);
}