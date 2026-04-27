#pragma once
#include <chrono>

struct ScrollRequest
{
    float startY;
    float endY;
    std::chrono::steady_clock::time_point startTime;
    bool isPending = false;
};