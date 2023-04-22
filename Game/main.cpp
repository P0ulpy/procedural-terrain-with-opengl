#include "GameLoop/GameLoop.hpp"

//#include "Scenes/TerrainScene.hpp"
#include "Scenes/InterfaceTestsScene.hpp"

int main()
{
    GameLoop gameLoop;
    gameLoop.SetScene(new InterfaceTestsScene());
    gameLoop.Run();

    return 0;
}