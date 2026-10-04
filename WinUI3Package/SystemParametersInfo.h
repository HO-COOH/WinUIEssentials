#pragma once
#include <minwindef.h>

#undef SystemParametersInfo
namespace SystemParametersInfo
{
	namespace Accessibility
	{
		ULONG MessageDuration();
	}

	namespace Input
	{
		UINT MouseHoverTime();
	}
}