//
// Created by Flo on 20/04/2023.
//

#include "InterfaceTestsScene.hpp"
#include "Renderable/Cube.hpp"
#include "../UISystem/UiWindow.hpp"

void InterfaceTestsScene::Init()
{
    AddObject<Cube<float>>(new Cube<float>());

    //AddObject<UIWindow>(new UIWindow("Test", ImVec2(200.f, 200.f)));
}
