#include <Scenes/InterfaceTestsScene.hpp>
#include <Renderer/Renderable/Cube.hpp>
#include <UISystem/UiWindow.hpp>
#include <UISystem/UiText.hpp>

void InterfaceTestsScene::Init()
{
    AddObject<Cube<float>>(new Cube<float>());

    auto infoWindow = new UIWindow(
        "Infos",
        ImVec2(300, 40),
        ImGuiCond_Always,
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing
    );

    infoWindow->AddChild(new UIText("Hello World!"));

    AddObject(infoWindow);
}
