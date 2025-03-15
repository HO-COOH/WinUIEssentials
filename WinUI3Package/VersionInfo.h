#pragma once

#include "VersionInfo.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct VersionInfo : VersionInfoT<VersionInfo>
    {
        VersionInfo() = default;

        static uint32_t WASDKReleaseMajor();
        static uint32_t WASDKReleaseMinor();
        static uint32_t WASDKReleasePatch();
        static uint32_t WASDKReleaseMajorMinor();
        static winrt::hstring WASDKReleaseChannel();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct VersionInfo : VersionInfoT<VersionInfo, implementation::VersionInfo>
    {
    };
}
