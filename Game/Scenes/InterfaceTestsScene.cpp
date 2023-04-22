//
// Created by Flo on 20/04/2023.
//

#include "InterfaceTestsScene.hpp"
#include "Renderable/Cube.hpp"

void InterfaceTestsScene::Init()
{
    AddObject<Cube<float>>(new Cube<float>());
}
