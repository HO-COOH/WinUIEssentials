#pragma once
#include <atomic>
#include <chrono>

struct ScrollRequest
{
    float startY;
    float endY;
    std::chrono::steady_clock::time_point startTime;
    std::atomic<bool> isPending{ false };

    double Progress() const
    {
        auto const elapsed = std::chrono::steady_clock::now() - startTime;
        return std::clamp(
            std::chrono::duration<double>(elapsed).count() / std::chrono::duration<double>(TableConstants::SmoothScrollDuration).count(),
            0.0, 1.0
        );
    }
};