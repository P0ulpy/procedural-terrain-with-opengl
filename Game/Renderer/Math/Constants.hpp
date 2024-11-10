#pragma once

template <typename T>
constexpr T PI = T(3.141592653589793238462643383279502884L);

template <typename T>
constexpr T DegToRad(T deg)
{
    return deg * PI<T> / T(180);
}

template <typename T>
constexpr T RadToDeg(T rad)
{
    return rad * T(180) / PI<T>;
}