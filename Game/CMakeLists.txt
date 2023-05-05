SET(GAME_TARGET_NAME Game)

SET(GAME_SOURCES
        main.cpp
        GameLoop/GameLoop.cpp
        GameLoop/GameLoop.hpp
        GameLoop/Scene.cpp
        GameLoop/Scene.hpp
        Objects/IUpdatable.hpp
        Objects/GameCamera.hpp
        Objects/GameCamera.cpp
        Scenes/TerrainScene.cpp
        Scenes/TerrainScene.hpp
        Scenes/InterfaceTestsScene.cpp
        Scenes/InterfaceTestsScene.hpp
        UISystem/Widget.cpp
        UISystem/Widget.hpp
        UISystem/UiWindow.cpp
        UISystem/UiWindow.hpp
        Map/TerrainGenerator.hpp
        Map/TerrainGenerator.cpp
        Map/ChunkContainer.hpp
        Map/ChunkContainer.cpp
        UISystem/UiText.cpp UISystem/UiText.hpp UISystem/UiButton.cpp UISystem/UiButton.hpp UISystem/UiInputInt.cpp UISystem/UiInputInt.hpp UISystem/UISliderFloat.cpp UISystem/UISliderFloat.hpp UISystem/UiSliderInt.cpp UISystem/UiSliderInt.hpp)

# Packages
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)

# Target
add_executable(${GAME_TARGET_NAME} ${GAME_SOURCES})

# Subdirectories
add_subdirectory(Renderer)

# Links
include_directories(${CMAKE_SOURCE_DIR}/ProceduralGeneration)
include_directories(${CMAKE_SOURCE_DIR}/Game/Renderer)

target_link_libraries(${GAME_TARGET_NAME}
        PUBLIC GLEW::GLEW
        PUBLIC imgui::imgui
        PUBLIC ImGui-SFML::ImGui-SFML
        PUBLIC sfml-system sfml-network sfml-graphics sfml-window
        ProceduralGeneration
)

# Copy assets files
SET(ASSETS_DIRECTORY ${CMAKE_SOURCE_DIR}/Game/Assets)
SET(ASSETS_BIN_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/Assets)

file(COPY ${ASSETS_DIRECTORY}/Textures DESTINATION ${ASSETS_BIN_DIRECTORY})
file(COPY ${ASSETS_DIRECTORY}/Shaders DESTINATION ${ASSETS_BIN_DIRECTORY})
file(COPY ${ASSETS_DIRECTORY}/Font DESTINATION ${ASSETS_BIN_DIRECTORY})

# Change this to match all kind of generators / CMAKE_BUILD_TYPE
SET(ASSETS_BIN_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/Assets)

file(COPY ./Assets DESTINATION ./)