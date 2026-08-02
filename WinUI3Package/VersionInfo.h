#pragma once

#include "VersionInfo.g.h"
#include <WindowsAppSDK-VersionInfo.h>

namespace winrt::WinUI3Package::implementation
{
    struct VersionInfo : VersionInfoT<VersionInfo>
    {
        constexpr static uint32_t WASDKReleaseMajor()
        {
            return WINDOWSAPPSDK_RELEASE_MAJOR;
        }

        constexpr static uint32_t WASDKReleaseMinor()
        {
            return WINDOWSAPPSDK_RELEASE_MINOR;
        }

        constexpr static uint32_t WASDKReleasePatch()
        {
            return WINDOWSAPPSDK_RELEASE_PATCH;
        }
        constexpr static uint32_t WASDKReleaseMajorMinor()
        {
            return WINDOWSAPPSDK_RELEASE_MAJORMINOR;
        }

        static winrt::hstring WASDKReleaseChannel();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct VersionInfo : VersionInfoT<VersionInfo, implementation::VersionInfo>
    {
    };
}
