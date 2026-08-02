#include "pch.h"
#include "VersionInfo.h"
#if __has_include("VersionInfo.g.cpp")
#include "VersionInfo.g.cpp"
#endif


namespace winrt::WinUI3Package::implementation
{
	winrt::hstring VersionInfo::WASDKReleaseChannel()
	{
		return WINDOWSAPPSDK_RELEASE_CHANNEL_W;
	}
}
