#include "pch.h"
#include "TaskbarIcon.h"
#if __has_include("TaskbarIcon.g.cpp")
#include "TaskbarIcon.g.cpp"
#endif
#include "IconUtils.h"
#include "WinUIEssentialError.hpp"

namespace winrt::WinUI3Package::implementation
{
	winrt::hstring TaskbarIcon::ToolTip()
	{
		throw GetterNotImplemented{ L"TaskbarIcon.ToolTip" };
	}
	void TaskbarIcon::ToolTip(winrt::hstring const& value)
	{
		std::visit([value, this](auto&& icon) {
			using IconType = std::remove_reference_t<decltype(icon)>;
			if constexpr (!std::is_same_v<IconType, std::monostate>)
			{
				icon.ToolTip(value);
			}
			else
			{
				m_tooltip = value;
			}
		}, m_icon);
	}

	winrt::guid TaskbarIcon::Guid()
	{
		return m_guid;
	}
	void TaskbarIcon::Guid(winrt::guid value)
	{
		std::visit([value, this](auto&& icon) {
			using IconType = std::remove_reference_t<decltype(icon)>;
			if constexpr (!std::is_same_v<IconType, std::monostate>)
			{
				icon.Guid(value);
			}
			else
			{
				m_guid = value;
			}
			}, m_icon);
	}
	WinUI3Package::GeneratedIconSource TaskbarIcon::IconSource()
	{
		return m_iconSource;
	}
	void TaskbarIcon::IconSource(WinUI3Package::GeneratedIconSource value)
	{
		m_iconSource = value;
	}
	void TaskbarIcon::Icon(winrt::Windows::Foundation::Uri value)
	{
		setIconFromUri(value, [this](std::wstring_view path) {getNormalIcon().Icon(Utils::GetHIcon(path));  });
	}
	winrt::hstring TaskbarIcon::IconFile()
	{
		throw GetterNotImplemented{ L"TaskbarIcon.IconFile" };
	}
	void TaskbarIcon::IconFile(winrt::hstring const& value)
	{
		getNormalIcon().Icon(Utils::GetHIcon(value));
	}
	WinUI3Package::GeneratedIconSource TaskbarIcon::LightThemeIconSource()
	{
		return WinUI3Package::GeneratedIconSource();
	}
	void TaskbarIcon::LightThemeIconSource(WinUI3Package::GeneratedIconSource value)
	{
	}
	winrt::Windows::Foundation::Uri TaskbarIcon::LightThemeIcon()
	{
		throw GetterNotImplemented{ L"TaskbarIcon.LightThemeIcon" };
	}
	void TaskbarIcon::LightThemeIcon(winrt::Windows::Foundation::Uri value)
	{
		setIconFromUri(value, [this](std::wstring_view path) {getThemeAdaptiveIcon().IconLight(Utils::GetHIcon(path)); });
	}
	winrt::hstring TaskbarIcon::LightThemeIconFile()
	{
		throw GetterNotImplemented{ L"TaskbarIcon.LightThemeIconFile" };
	}
	void TaskbarIcon::LightThemeIconFile(winrt::hstring const& value)
	{
		getThemeAdaptiveIcon().IconLight(Utils::GetHIcon(value));
	}
	WinUI3Package::GeneratedIconSource TaskbarIcon::DarkThemeIconSource()
	{
		return WinUI3Package::GeneratedIconSource();
	}
	void TaskbarIcon::DarkThemeIconSource(WinUI3Package::GeneratedIconSource value)
	{
	}
	winrt::Windows::Foundation::Uri TaskbarIcon::DarkThemeIcon()
	{
		throw GetterNotImplemented{ L"TaskbarIcon.DarkThemeIcon" };
	}
	void TaskbarIcon::DarkThemeIcon(winrt::Windows::Foundation::Uri value)
	{
		setIconFromUri(value, [this](std::wstring_view path) {getThemeAdaptiveIcon().IconDark(Utils::GetHIcon(path)); });
	}

	winrt::hstring TaskbarIcon::DarkThemeIconFile()
	{
		throw GetterNotImplemented{ L"TaskbarIcon.DarkThemeIconFile" };
	}

	void TaskbarIcon::DarkThemeIconFile(winrt::hstring const& value)
	{
		getThemeAdaptiveIcon().IconDark(Utils::GetHIcon(value));
	}

	void TaskbarIcon::RightClickMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& value)
	{
		m_xamlMenuFlyout = value;
	}

	winrt::Microsoft::UI::Xaml::ElementTheme TaskbarIcon::MenuTheme()
	{
		return winrt::Microsoft::UI::Xaml::ElementTheme();
	}

	void TaskbarIcon::MenuTheme(winrt::Microsoft::UI::Xaml::ElementTheme value)
	{
		m_theme = value;
	}

	void TaskbarIcon::Show()
	{
		m_showCalled = true;
		std::visit([this](auto&& icon)
		{
			using IconType = std::remove_reference_t<decltype(icon)>;
			if constexpr (!std::is_same_v<IconType, std::monostate>)
			{
				icon.ToolTip(m_tooltip);
				if (m_guid != winrt::guid{})
					icon.Guid(m_guid);
				icon.Show();
				icon.SetMenu(m_xamlMenuFlyout);
				icon.SetTheme(m_theme);
			}
		}, m_icon);
	}

	void TaskbarIcon::Remove()
	{
		m_showCalled = false;
		std::visit([this](auto&& icon)
		{
			using IconType = std::remove_reference_t<decltype(icon)>;
			if constexpr (!std::is_same_v<IconType, std::monostate>)
			{
				icon.Remove();
			}
		}, m_icon);
	}
	winrt::event_token TaskbarIcon::LeftPressed(WinUI3Package::SignalDelegate const& handler)
	{
		return m_events.m_leftPressed.add(handler);
	}
	winrt::event_token TaskbarIcon::LeftDoublePressed(WinUI3Package::SignalDelegate const& handler)
	{
		return m_events.m_leftDoublePressed.add(handler);
	}
	winrt::event_token TaskbarIcon::RightPressed(WinUI3Package::SignalDelegate const& handler)
	{
		return m_events.m_rightPressed.add(handler);
	}

	winrt::event_token TaskbarIcon::PointerHover(WinUI3Package::SignalDelegate const& handler)
	{
		return m_events.m_pointerHover.add(handler);
	}
	void TaskbarIcon::LeftPressed(winrt::event_token const& token)
	{
		m_events.m_leftPressed.remove(token);
	}
	void TaskbarIcon::LeftDoublePressed(winrt::event_token const& token)
	{
		m_events.m_leftDoublePressed.remove(token);
	}
	void TaskbarIcon::RightPressed(winrt::event_token const& token)
	{
		m_events.m_rightPressed.remove(token);
	}
	void TaskbarIcon::PointerHover(winrt::event_token const& handler)
	{
		m_events.m_pointerHover.remove(handler);
	}
	winrt::Microsoft::UI::Xaml::UIElement TaskbarIcon::PopupContent()
	{
		return winrt::Microsoft::UI::Xaml::UIElement{ nullptr };
	}
	void TaskbarIcon::PopupContent(winrt::Microsoft::UI::Xaml::UIElement value)
	{
	}
	ThemeAdaptiveIcon& TaskbarIcon::getThemeAdaptiveIcon()
	{
		if (m_icon.index() == 0)
			m_icon.emplace<1>().SetEvents(m_events);
		return std::get<1>(m_icon);
	}
	NormalTaskbarIcon& TaskbarIcon::getNormalIcon()
	{
		if (m_icon.index() == 0)
			m_icon.emplace<2>().SetEvents(m_events);
		return std::get<2>(m_icon);
	}
}
