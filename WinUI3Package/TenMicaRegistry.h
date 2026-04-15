#pragma once
#include <string>
#include <optional>
#include <boost/container/small_vector.hpp>

namespace TenMicaRegistry
{
	constexpr static auto MonitorCountEstimate = 4;

	std::wstring Wallpaper();
	boost::container::small_vector<std::vector<uint8_t>, MonitorCountEstimate> TranscodedImageCaches();
	COLORREF Background();
	std::wstring BackgroundValue();
}