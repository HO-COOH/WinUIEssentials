#pragma once
#include <atomic>
#include <chrono>

class ScrollRequest
{
    float m_startY;
    float m_endY;
    std::chrono::steady_clock::time_point m_startTime;

public:
    std::atomic<bool> isPending{ false };

    void Set(float startY, float endY) noexcept;
    constexpr void Set(ScrollRequest const& rhs) noexcept
    {
        m_startY = rhs.m_startY;
        m_endY = rhs.m_endY;
        m_startTime = rhs.m_startTime;
    }

    constexpr float GetTarget() const noexcept
    {
        return m_endY;
    }

    double Progress() const noexcept;

    constexpr float EasedValue(float easedProgress) noexcept
    {
        return easedProgress >= 1.0 ?
            m_endY :
            m_startY + (m_endY - m_startY) * easedProgress;
    }
};