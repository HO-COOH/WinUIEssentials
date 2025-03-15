#include "pch.h"
#include "AboutPage.xaml.h"
#if __has_include("AboutPage.g.cpp")
#include "AboutPage.g.cpp"
#endif
#include <WindowsAppSDK-VersionInfo.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::hstring AboutPage::WASDKReleaseVersion()
	{
		return winrt::hstring{ std::format(
			L"{}.{}.{}.{}-{}",
			WINDOWSAPPSDK_RELEASE_MAJOR,
			WINDOWSAPPSDK_RELEASE_MINOR,
			WINDOWSAPPSDK_RELEASE_PATCH,
			WINDOWSAPPSDK_RELEASE_MAJORMINOR,
			WINDOWSAPPSDK_RELEASE_CHANNEL_W
		) };
	}

	winrt::hstring AboutPage::WASDKRuntimeVersion()
	{
		return WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING_W;
	}

	winrt::hstring AboutPage::FormatVersion(
		uint32_t major, 
		uint32_t minor, 
		uint32_t patch,
		uint32_t majorMinor,
		winrt::hstring const& channel)
	{
		return winrt::hstring{ std::format(
			L"{}.{}.{}.{}-{}",
			major,
			minor,
			patch,
			majorMinor,
			channel
		) };
	}
}
