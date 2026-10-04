#include "pch.h"
#include "SystemParametersInfo.h"
#include <Windows.h>

namespace SystemParametersInfo
{
	namespace Accessibility
	{
		ULONG MessageDuration()
		{
			ULONG duration{};
			winrt::check_bool(SystemParametersInfoW(SPI_GETMESSAGEDURATION, 0, &duration, 0));
			return duration;
		}
	}

	namespace Input
	{
		UINT MouseHoverTime()
		{
			UINT time{};
			winrt::check_bool(SystemParametersInfoW(SPI_GETMOUSEHOVERTIME, 0, &time, 0));
			return time;
		}
	}
}