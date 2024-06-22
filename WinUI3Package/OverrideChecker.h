#pragma once
#ifdef _DEBUG
#include <exception>
#include <format>
#endif

class OverrideChecker
{
#ifdef _DEBUG
	bool m_hasOverride{};
#endif // _DEBUG

public:
	constexpr OverrideChecker& operator=(bool value)
	{
#ifdef _DEBUG
		m_hasOverride = true;
#endif
		return *this;
	}

	void ThrowIfHasOverride(const char* propertyName)
	{
#ifdef _DEBUG
		if (m_hasOverride)
		{
			throw std::exception{ std::format("Do not set TintColor/TintOpacity/FallbackColor/LuminosityOpacity while {} is set!", propertyName).data()};
		}
#endif
	}
};

