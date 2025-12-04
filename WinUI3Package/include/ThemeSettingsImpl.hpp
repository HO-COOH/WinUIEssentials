#pragma once

#include <wil/registry.h>
#include <iterator>
#include <dwmapi.h>

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
		//return wil::reg::get_value_dword(
		//	HKEY_CURRENT_USER,
		//	DWMSubKey,
		//	L"AccentColor"
		//);

		DWORD colorization;
		BOOL opaque;
		winrt::check_hresult(DwmGetColorizationColor(&colorization, &opaque));
		return colorization;
	}

	static DWORD ColorizationColor()
	{
		return wil::reg::get_value_dword(
			HKEY_CURRENT_USER,
			DWMSubKey,
			L"ColorizationColor"
		);
	}

	static bool ShowAccentColorOnTitleBarsAndWindowBorders()
	{
		return static_cast<bool>(wil::reg::get_value_dword(
			HKEY_CURRENT_USER,
			DWMSubKey,
			L"ColorPrevalence"
		));
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

	static constexpr winrt::Windows::UI::Color ColorFromDWORDFromReg(DWORD value)
	{
		return winrt::Windows::UI::Color
		{
			.A = 0xFF,
			.R = static_cast<uint8_t>(value & 0xFF),
			.G = static_cast<uint8_t>((value >> 8) & 0xFF),
			.B = static_cast<uint8_t>((value >> 16) & 0xFF)
		};
	}

	static constexpr winrt::Windows::UI::Color ColorFromDWORDFromDwm(DWORD value)
	{
		return winrt::Windows::UI::Color
		{
			.A = 0xFF,
			.R = static_cast<uint8_t>((value >> 16) & 0xFF),
			.G = static_cast<uint8_t>((value >> 8) & 0xFF),
			.B = static_cast<uint8_t>(value & 0xFF)
		};
	}
};