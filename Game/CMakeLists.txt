SET(GAME_TARGET_NAME Game)

add_executable(${GAME_TARGET_NAME}
        main.cpp
         "Matrix.h")

SET(ASSETS_DIRECTORY ${CMAKE_SOURCE_DIR}/Game/Assets)

# Change this to match all kind of generators / CMAKE_BUILD_TYPE
SET(ASSETS_BIN_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/Assets)

# file(COPY Textures DESTINATION ${CMAKE_BINARY_DIR})
# configure_file(${ASSETS_DIRECTORY}/moche2.bmp ${ASSETS_BIN_DIRECTORY}/moche2.bmp COPYONLY)
# configure_file(${ASSETS_DIRECTORY}/triangles.frag ${ASSETS_BIN_DIRECTORY}/triangles.frag COPYONLY)
# configure_file(${ASSETS_DIRECTORY}/triangles.vert ${ASSETS_BIN_DIRECTORY}/triangles.vert COPYONLY)

include_directories(${CMAKE_SOURCE_DIR}/Renderer)
include_directories(${CMAKE_SOURCE_DIR}/ProceduralGeneration)

target_link_libraries(${GAME_TARGET_NAME}
        Renderer
        ProceduralGeneration
)