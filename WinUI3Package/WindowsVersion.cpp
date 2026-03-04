#include "pch.h"
#include "WindowsVersion.hpp"

OSVERSIONINFOEXW const& GetWindowsVersion()
{
    static auto s_version = []
    {
        OSVERSIONINFOEXW version{};
        winrt::check_hresult(RtlGetVersion(&version));
        return version;
    }();
    return s_version;
}
