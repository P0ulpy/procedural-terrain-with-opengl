SET(GAME_TARGET_NAME Game)

add_executable(${GAME_TARGET_NAME}
        main.cpp
        Matrix.h
        Map/MapGenerator.h
        Map/MapGenerator.cpp
        Map/MapGenerator.tpp)

SET(ASSETS_DIRECTORY ${CMAKE_SOURCE_DIR}/Game/Assets)

# Change this to match all kind of generators / CMAKE_BUILD_TYPE
SET(ASSETS_BIN_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/Assets)

file(COPY ./Assets DESTINATION ./)

include_directories(${CMAKE_SOURCE_DIR}/Renderer)
include_directories(${CMAKE_SOURCE_DIR}/ProceduralGeneration)

target_link_libraries(${GAME_TARGET_NAME}
        Renderer
        ProceduralGeneration
)