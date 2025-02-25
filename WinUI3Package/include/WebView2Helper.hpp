#pragma once
#include <optional>
#include <string>
#include <wil/registry.h>
#include <Windows.h>

class WebView2Helper
{
	//copied from https://devblogs.microsoft.com/oldnewthing/20050201-00/?p=36553
	static bool is64BitWindows()
	{
#if defined(_WIN64)
		return true;  // 64-bit programs run only on Win64
#elif defined(_WIN32)
		// 32-bit programs run on both 32-bit and 64-bit Windows
		// so must sniff
		BOOL f64 = FALSE;
		return IsWow64Process(GetCurrentProcess(), &f64) && f64;
#else
		return false; // Win64 does not support Win16
#endif
	}
public:
	static auto GetPerMachineInstalledVersion()
	{
		return wil::reg::try_get_value_string<std::wstring>(
			HKEY_LOCAL_MACHINE,
			is64BitWindows() ?
			LR"(SOFTWARE\WOW6432Node\Microsoft\EdgeUpdate\Clients\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5})" :
			LR"(SOFTWARE\Microsoft\EdgeUpdate\Clients\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5})",
			L"pv"
		);
	}

	static auto GetPerUserInstalledVersion()
	{
		return wil::reg::try_get_value_string<std::wstring>(
			HKEY_CURRENT_USER,
			LR"(Software\Microsoft\EdgeUpdate\Clients\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5})",
			L"pv"
		);
	}

	static bool IsWebView2Installed()
	{
		auto const perMachineInstalledVersion = GetPerMachineInstalledVersion();
		if (perMachineInstalledVersion && !perMachineInstalledVersion->empty())
			return true;
		auto const perUserInstalledVersion = GetPerUserInstalledVersion();
		return perUserInstalledVersion && !perUserInstalledVersion->empty();
	}
};