#include "pch.h"
#include "TenMicaRegistry.h"
#include <wil/registry.h>

static std::optional<std::vector<uint8_t>> TranscodedImageCache()
{
	return wil::reg::try_get_value_binary(
		HKEY_CURRENT_USER, 
		LR"(Control Panel\Desktop)", 
		L"TranscodedImageCache", 
		REG_BINARY
	);
}

static std::optional<std::vector<uint8_t>> TranscodedImageCache(int i)
{
	return wil::reg::try_get_value_binary(
		HKEY_CURRENT_USER, 
		LR"(Control Panel\Desktop)", 
		std::format(L"TranscodedImageCache_{:03d}", i).data(), 
		REG_BINARY
	);
}


namespace TenMicaRegistry
{
	std::wstring Wallpaper()
	{
		return wil::reg::get_value_string(HKEY_CURRENT_USER, LR"(Control Panel\Desktop)", L"Wallpaper");
	}

	std::wstring BackgroundValue()
	{
		return wil::reg::get_value_string(HKEY_CURRENT_USER, LR"(Control Panel\Colors)", L"Background");
	}


	boost::container::small_vector<std::vector<uint8_t>, MonitorCountEstimate> TranscodedImageCaches()
	{
		boost::container::small_vector<std::vector<uint8_t>, MonitorCountEstimate> result;

		auto firstValue = TranscodedImageCache();
		if (!firstValue)
			return result;

		result.push_back(std::move(*firstValue));

		for (int i = 0;; ++i)
		{
			auto value_n = TranscodedImageCache(i);
			if (!value_n)
				return result;

			result.push_back(std::move(*value_n));
		}
	}

	COLORREF Background()
	{
		auto value = BackgroundValue();
		unsigned red{};
		unsigned green{};
		unsigned blue{};

		if (swscanf_s(value.c_str(), L"%u %u %u", &red, &green, &blue) != 3)
			return RGB(0, 0, 0);

		red = (std::min)(red, 255u);
		green = (std::min)(green, 255u);
		blue = (std::min)(blue, 255u);
		return RGB(red, green, blue);
	}
}