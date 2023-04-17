SET(PROCEDURAL_GENERATION_TARGET_NAME ProceduralGeneration)

add_library(${PROCEDURAL_GENERATION_TARGET_NAME} STATIC
        ProceduralGeneration.hpp
        ProceduralGeneration.cpp
  "MapGenerator.h" "ProceduralAlgo/PerlinNoise.h" "ProceduralAlgo/PerlinNoise.cpp" "MapGenerator.cpp")