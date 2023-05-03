SET(GAME_TARGET_NAME Game)

add_executable(${GAME_TARGET_NAME}
    main.cpp
    Map/MapGenerator.h
    Map/MapGenerator.cpp
    Map/MapGenerator.tpp
)

SET(ASSETS_DIRECTORY ${CMAKE_SOURCE_DIR}/Game/Assets)
SET(ASSETS_BIN_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/Assets)

file(COPY ${ASSETS_DIRECTORY}/Textures DESTINATION ${ASSETS_BIN_DIRECTORY})
file(COPY ${ASSETS_DIRECTORY}/Shaders DESTINATION ${ASSETS_BIN_DIRECTORY})
file(COPY ${ASSETS_DIRECTORY}/Font DESTINATION ${ASSETS_BIN_DIRECTORY})

# Change this to match all kind of generators / CMAKE_BUILD_TYPE
SET(ASSETS_BIN_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/Assets)

file(COPY ./Assets DESTINATION ./)

include_directories(${CMAKE_SOURCE_DIR}/Renderer)
include_directories(${CMAKE_SOURCE_DIR}/ProceduralGeneration)

target_link_libraries(${GAME_TARGET_NAME}
        Renderer
        ProceduralGeneration
)