#include "pch.h"
#include "VersionInfo.h"
#if __has_include("VersionInfo.g.cpp")
#include "VersionInfo.g.cpp"
#endif
#include <WindowsAppSDK-VersionInfo.h>

namespace winrt::WinUI3Package::implementation
{
	uint32_t VersionInfo::WASDKReleaseMajor()
	{
		return WINDOWSAPPSDK_RELEASE_MAJOR;
	}
	uint32_t VersionInfo::WASDKReleaseMinor()
	{
		return WINDOWSAPPSDK_RELEASE_MINOR;
	}
	uint32_t VersionInfo::WASDKReleasePatch()
	{
		return WINDOWSAPPSDK_RELEASE_PATCH;
	}
	uint32_t VersionInfo::WASDKReleaseMajorMinor()
	{
		return WINDOWSAPPSDK_RELEASE_MAJORMINOR;
	}
	winrt::hstring VersionInfo::WASDKReleaseChannel()
	{
		return WINDOWSAPPSDK_RELEASE_CHANNEL_W;
	}
}
