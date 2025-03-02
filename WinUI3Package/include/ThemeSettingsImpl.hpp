#pragma once

#include <wil/registry.h>
#include <iterator>

class ThemeSettingsImpl
{
	constexpr static auto PersonalizeSubKey = LR"(Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)";
	constexpr static auto DWMSubKey = LR"(Software\Microsoft\Windows\DWM)";
public:
	static bool AppsUseLightTheme()
	{
		return wil::reg::get_value_dword(
			HKEY_CURRENT_USER,
			PersonalizeSubKey,
			L"AppsUseLightTheme"
		);
	}

	static bool ColorPrevalence()
	{
		return wil::reg::get_value_dword(
			HKEY_CURRENT_USER,
			PersonalizeSubKey,
			L"ColorPrevalence"
		);
	}

	static bool EnableTransparency()
	{
		return wil::reg::get_value_dword(
			HKEY_CURRENT_USER,
			PersonalizeSubKey,
			L"EnableTransparency"
		);
	}

	static bool SystemUsesLightTheme()
	{
		return wil::reg::get_value_dword(
			HKEY_CURRENT_USER,
			PersonalizeSubKey,
			L"SystemUsesLightTheme"
		);
	}

	static DWORD AccentColor()
	{
		return wil::reg::get_value_dword(
			HKEY_CURRENT_USER,
			DWMSubKey,
			L"AccentColor"
		);
	}

	static DWORD ColorizationColor()
	{
		return wil::reg::get_value_dword(
			HKEY_CURRENT_USER,
			DWMSubKey,
			L"ColorizationColor"
		);
	}

	class ColorHistoryCollection
	{
		constexpr static auto SubKey = LR"(Software\Microsoft\Windows\CurrentVersion\Themes\History\Colors)";
	public:
		DWORD operator[](int i)
		{
			return wil::reg::get_value_dword(
				HKEY_CURRENT_USER,
				SubKey,
				std::format(L"ColorHistory{}", i).data()
			);
		}

		auto size() const
		{
			auto key = wil::reg::open_unique_key(
				HKEY_CURRENT_USER, 
					SubKey
			);
			return std::distance(
				wil::reg::value_iterator{ key.get() },
				wil::reg::value_iterator{}
			);
		}
	};

	constexpr static ColorHistoryCollection ColorHistory()
	{
		return {};
	}
};