SET(GAME_TARGET_NAME Game)

SET(GAME_SOURCES
        main.cpp
        GameLoop/GameLoop.cpp
        GameLoop/GameLoop.hpp
        GameLoop/Scene.cpp
        GameLoop/Scene.hpp
        Objects/IUpdatable.hpp
        Scenes/TerrainScene.cpp
        Scenes/TerrainScene.hpp
        Scenes/InterfaceTestsScene.cpp
        Scenes/InterfaceTestsScene.hpp
        Objects/GameCamera.cpp
        Objects/GameCamera.hpp
)

add_executable(${GAME_TARGET_NAME} ${GAME_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/Renderer)
include_directories(${CMAKE_SOURCE_DIR}/ProceduralGeneration)

target_link_libraries(${GAME_TARGET_NAME}
        Renderer
        ProceduralGeneration
)

file(COPY ./Assets DESTINATION ./)

#add_custom_command(
#        TARGET ${GAME_TARGET_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_CONFIG_DIRECTORY}
#        ${CMAKE_RUNTIME_CONFIG_DIRECTORY}
#)