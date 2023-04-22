SET(RENDERER_TARGET_NAME Renderer)

find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)

SET(RENDER_SOURCES
        Renderer.hpp
        Renderer.cpp
        Camera/Camera.cpp
        Camera/Camera.hpp
        Renderable/IRenderable.hpp
        Renderable/Cube.tpp
        Renderable/Cube.hpp
        Shader/Shader.cpp
        Shader/Shader.hpp
        Math/Mat.hpp
        Math/Point.hpp
        Math/Constants.hpp
        Color/Color.hpp Math/Vector.hpp)

add_library(${RENDERER_TARGET_NAME} STATIC ${RENDER_SOURCES})

target_link_libraries(${RENDERER_TARGET_NAME}
        PUBLIC GLEW::GLEW
        PUBLIC imgui::imgui
        PUBLIC ImGui-SFML::ImGui-SFML
        PUBLIC sfml-system sfml-network sfml-graphics sfml-window
)