#pragma once

#include <cstddef>  // size_t
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

 /**
  * @brief A Perlin Simplex Noise C++ Implementation (1D, 2D, 3D, 4D).
  */
class PerlinNoise {
public:
    // 1D Perlin simplex noise
    static float noise(float x);
    // 2D Perlin simplex noise
    static float noise(float x, float y);
    // 3D Perlin simplex noise
    static float noise(float x, float y, float z);

    // Fractal/Fractional Brownian Motion (fBm) noise summation
    [[nodiscard]] float fractal(size_t octaves, float x) const;
    [[nodiscard]] float fractal(size_t octaves, float x, float y) const;
    [[nodiscard]] float fractal(size_t octaves, float x, float y, float z) const;

    /**
     * Constructor of to initialize a fractal noise summation
     *
     * @param[in] frequency    Frequency ("width") of the first octave of noise (default to 1.0)
     * @param[in] amplitude    Amplitude ("height") of the first octave of noise (default to 1.0)
     * @param[in] lacunarity   Lacunarity specifies the frequency multiplier between successive octaves (default to 2.0).
     * @param[in] persistence  Persistence is the loss of amplitude between successive octaves (usually 1/lacunarity)
     */
    explicit PerlinNoise(
        float frequency = 1.0f,
        float amplitude = 1.0f,
        float lacunarity = 2.0f,
        float persistence = 0.5f) :
        mFrequency(frequency),
        mAmplitude(amplitude),
        mLacunarity(lacunarity),
        mPersistence(persistence) {

    }

    void setSeed(unsigned int seed);

    static inline uint8_t hash(int32_t i);

private:
    static std::vector<int> p;
    // Parameters of Fractional Brownian Motion (fBm) : sum of N "octaves" of noise
    float mFrequency;   ///< Frequency ("width") of the first octave of noise (default to 1.0)
    float mAmplitude;   ///< Amplitude ("height") of the first octave of noise (default to 1.0)
    float mLacunarity;  ///< Lacunarity specifies the frequency multiplier between successive octaves (default to 2.0).
    float mPersistence; ///< Persistence is the loss of amplitude between successive octaves (usually 1/lacunarity)
};