#pragma once

constexpr inline double EasedProgress(double progress, int exponent)
{
    double const inv = 1.0 - progress;
    double result = 1.0;
    for (int i = 0; i < exponent; ++i)
        result *= inv;
    return 1.0 - result;
}