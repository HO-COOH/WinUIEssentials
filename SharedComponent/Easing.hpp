#pragma once

constexpr inline double EasedProgress(double progress, int exponent)
{
	auto result = 1.0 - progress;
	for (int i = 0; i < exponent; ++i)
	{
		result *= result;
	}
	return 1.0 - result;
}