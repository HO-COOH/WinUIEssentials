#pragma once
#include <winrt/Windows.UI.Notifications.h>
#include <winrt/Windows.Data.Xml.Dom.h>
//values: https://learn.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/badges
namespace BadgeGlyphs
{
	constexpr static auto None = L"none";
	constexpr static auto Activity = L"activity";
	constexpr static auto Alarm = L"alarm";
	constexpr static auto Alert = L"alert";
	constexpr static auto Attention = L"attention";
	constexpr static auto Available = L"available";
	constexpr static auto Away = L"away";
	constexpr static auto Busy = L"busy";
	constexpr static auto Error = L"error";
	constexpr static auto NewMessage = L"newMessage";
	constexpr static auto Paused = L"paused";
	constexpr static auto Playing = L"playing";
	constexpr static auto Unavilable = L"unavilable";

	/**
	 * @brief Make a number badge notification xml, which will show on both start menu tiles and taskbar icon
	 * @param value The number value
	 * @return The XML representation of the badge notification, which should then be used as argument to `winrt::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication().Update()` call
	*/
	inline auto MakeBadgeNotification(int value)
	{
		auto xml = winrt::Windows::UI::Notifications::BadgeUpdateManager::GetTemplateContent(
			winrt::Windows::UI::Notifications::BadgeTemplateType::BadgeNumber
		);
		xml.SelectSingleNode(L"/badge")
			.as<winrt::Windows::Data::Xml::Dom::XmlElement>()
			.SetAttribute(L"value", winrt::to_hstring(value));
		return winrt::Windows::UI::Notifications::BadgeNotification{ xml };
	}
	
	/**
	 * @brief Make a glyph badge notification xml, which will show on both start menu tiles and taskbar icon
	 * @param glyph Which should be a predefined string value from the `BadgeGlyph` namespace, like `BadgeGlyph::Alert`
	 * @return The XML representation of the badge notification, which should then be used as argument to `winrt::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication().Update()` call
	*/
	inline auto MakeBadgeNotification(wchar_t const* glyph)
	{
		auto xml = winrt::Windows::UI::Notifications::BadgeUpdateManager::GetTemplateContent(
			winrt::Windows::UI::Notifications::BadgeTemplateType::BadgeGlyph
		);
		xml.SelectSingleNode(L"/badge")
			.as<winrt::Windows::Data::Xml::Dom::XmlElement>()
			.SetAttribute(L"value", glyph);
		return winrt::Windows::UI::Notifications::BadgeNotification{ xml };
	}
}