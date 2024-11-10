SET(PROCEDURAL_GENERATION_TARGET_NAME ProceduralGeneration)

add_library(${PROCEDURAL_GENERATION_TARGET_NAME} STATIC
    PerlinNoise.hpp
    PerlinNoise.cpp
)