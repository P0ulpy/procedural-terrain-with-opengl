#include "GameLoop/GameLoop.hpp"

#include "Scenes/InterfaceTestsScene.hpp"
#include "Scenes/TerrainScene.hpp"

int main()
{
    GameLoop gameLoop;
    gameLoop.SetScene(new TerrainScene());
    gameLoop.Run();

    return 0;
}

