#include "pch.h"
#include "ScrollRequest.h"
#include "TableConstants.hpp"

void ScrollRequest::Set(float startY, float endY) noexcept
{
	m_startY = startY;
	m_endY = endY;
	m_startTime = std::chrono::steady_clock::now();
	isPending.store(true, std::memory_order_release);
}

double ScrollRequest::Progress() const noexcept
{
    auto const elapsed = std::chrono::steady_clock::now() - m_startTime;
    return std::clamp(
        std::chrono::duration<double>(elapsed).count() / std::chrono::duration<double>(TableConstants::SmoothScrollDuration).count(),
        0.0, 1.0
    );
}

