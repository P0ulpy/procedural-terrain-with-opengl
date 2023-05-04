SET(RENDERER_TARGET_NAME Renderer)

find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)

add_library(${RENDERER_TARGET_NAME} STATIC
        Renderer.hpp
        Renderer.cpp
        Shader.h
        Shader.cpp
        Texture.h
        Terrain.h
        Terrain.cpp
        UserInterface.hpp
        Math/Point.hpp
        Math/Vector.hpp
        Chunk.hpp Chunk.cpp ChunkContainer.hpp ChunkContainer.cpp
        UserInterface.tpp SkyBox.cpp SkyBox.hpp)

target_link_libraries(${RENDERER_TARGET_NAME}
        PUBLIC GLEW::GLEW
        PUBLIC imgui::imgui
        PUBLIC ImGui-SFML::ImGui-SFML
        PUBLIC sfml-system sfml-network sfml-graphics sfml-window
)