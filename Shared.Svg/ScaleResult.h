#pragma once
#include <cstdint>
#include <cmath>
#include <numeric>
#include <limits>

struct ScaleResult
{
    float scale = 1.0f;
    uint32_t width{};
    uint32_t height{};

    constexpr ScaleResult() = default;
    constexpr ScaleResult(double rasterWidth, double rasterHeight, float naturalWidth, float naturalHeight)
    {
        if (rasterWidth > 0.0 || rasterHeight > 0.0)
        {
            float scaleX = (rasterWidth > 0.0) ? static_cast<float>(rasterWidth) / static_cast<float>(naturalWidth) : std::numeric_limits<float>::infinity();
            float scaleY = (rasterHeight > 0.0) ? static_cast<float>(rasterHeight) / static_cast<float>(naturalHeight) : std::numeric_limits<float>::infinity();
            scale = (std::min)(scaleX, scaleY);
            width = static_cast<uint32_t>(std::ceil(naturalWidth * scale));
            height = static_cast<uint32_t>(std::ceil(naturalHeight * scale));
            return;
        }

        width = static_cast<uint32_t>(naturalWidth);
        height = static_cast<uint32_t>(naturalHeight);
    }
};