#pragma once

class ResizeRequest
{
	bool m_isResizingColumn{};
public:
	int m_resizeColumnIndex = -1;
	float m_resizeStartX{};
	float m_resizeStartWidth{};
	
	constexpr operator bool() const
	{
		return m_isResizingColumn;
	}

	constexpr ResizeRequest& operator=(bool value)
	{
		m_isResizingColumn = value;
		return *this;
	}
};