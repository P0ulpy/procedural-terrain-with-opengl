SET(PROCEDURAL_GENERATION_TARGET_NAME ProceduralGeneration)

add_library(${PROCEDURAL_GENERATION_TARGET_NAME} STATIC
        ProceduralGeneration.hpp
        ProceduralGeneration.cpp
  "MapGenerator.h" "Shape.h" "ProceduralAlgo/PerlinNoise.h" "ProceduralAlgo/PerlinNoise.cpp" "ProceduralAlgo/ppm.h" "ProceduralAlgo/ppm.cpp" "ProceduralAlgo/color.h" "ProceduralAlgo/color.cpp" "ProceduralAlgo/img.h" "ProceduralAlgo/img.cpp" "ProceduralAlgo/CImg.h")