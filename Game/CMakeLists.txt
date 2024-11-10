SET(GAME_TARGET_NAME Game)

# Packages
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics network CONFIG REQUIRED)

# Target
file(GLOB_RECURSE GAME_SRC_FILES "*.cpp")
add_executable(${GAME_TARGET_NAME} ${GAME_SRC_FILES})

# Includes
target_include_directories(${GAME_TARGET_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/ProceduralGeneration
    PRIVATE ${CMAKE_SOURCE_DIR}/Game
)

# Links
target_link_libraries(${GAME_TARGET_NAME}
    PRIVATE GLEW::GLEW
    PRIVATE imgui::imgui
    PRIVATE ImGui-SFML::ImGui-SFML
    PRIVATE sfml-system sfml-network sfml-graphics sfml-window
    PRIVATE ProceduralGeneration
)

# Copy assets files post build
SET(RESSOURCES_SOURCE_DIR Game/Assets)
SET(RESSOURCES_DEST_DIR Assets)

add_custom_command(
    TARGET ${GAME_TARGET_NAME}
    COMMENT "Copy Assets directory"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${RESSOURCES_SOURCE_DIR} $<TARGET_FILE_DIR:${GAME_TARGET_NAME}>/${RESSOURCES_DEST_DIR}
)