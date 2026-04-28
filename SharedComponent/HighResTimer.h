#pragma once
class HighResTimer
{
	bool m_enabled{};
public:
	HighResTimer() = default;
	HighResTimer(HighResTimer const& rhs) = delete;
	HighResTimer(HighResTimer&&) = delete;
	HighResTimer& operator=(HighResTimer const&) = delete;
	HighResTimer& operator=(HighResTimer&&) noexcept = delete;
	HighResTimer& operator=(bool value);

	~HighResTimer();
};