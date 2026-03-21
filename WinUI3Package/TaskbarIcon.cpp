#include "pch.h"
#include "TaskbarIcon.h"
#if __has_include("TaskbarIcon.g.cpp")
#include "TaskbarIcon.g.cpp"
#endif
#include "IconUtils.h"
#include "WinUIEssentialError.hpp"

namespace winrt::WinUI3Package::implementation
{
	TaskbarIcon::TaskbarIcon()
	{
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::FrameworkElement::RequestedThemeProperty(),
			[this](auto&& sender, winrt::Microsoft::UI::Xaml::DependencyProperty const& property)
			{
				MenuTheme(winrt::unbox_value<winrt::Microsoft::UI::Xaml::ElementTheme>(GetValue(property)));
			}
		);
	}

	winrt::hstring TaskbarIcon::ToolTip()
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(s_tooltipProperty));
	}

	void TaskbarIcon::ToolTip(winrt::hstring const& value)
	{
		SetValue(s_tooltipProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty TaskbarIcon::ToolTipProperty()
	{
		return s_tooltipProperty;
	}

	winrt::guid TaskbarIcon::Guid()
	{
		return winrt::unbox_value<winrt::guid>(GetValue(s_guidProperty));
	}
	void TaskbarIcon::Guid(winrt::guid value)
	{
		SetValue(s_guidProperty, winrt::box_value(value));
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
		return m_theme;
	}

	void TaskbarIcon::MenuTheme(winrt::Microsoft::UI::Xaml::ElementTheme value)
	{
		m_theme = value;
		std::visit([theme = m_theme](auto&& icon) {
			using IconType = std::remove_reference_t<decltype(icon)>;
			if constexpr (!std::is_same_v<IconType, std::monostate>)
				icon.SetTheme(theme);
		}, m_icon);
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
		m_icon.emplace<std::monostate>();
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

	void TaskbarIcon::EnsureDependencyProperties()
	{
		s_guidProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Guid",
			winrt::xaml_typename<winrt::guid>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&TaskbarIcon::onGuidChanged
			}
		);

		s_tooltipProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"ToolTip",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&TaskbarIcon::onToolTipChanged
			}
		);
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty TaskbarIcon::GuidProperty()
	{
		return s_guidProperty;
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

	void TaskbarIcon::onToolTipChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto self = winrt::get_self<TaskbarIcon>(d.as<class_type>());
		std::visit([value = winrt::unbox_value<winrt::hstring>(arg.NewValue()), self](auto&& icon)
		{
			using IconType = std::remove_reference_t<decltype(icon)>;
			if constexpr (!std::is_same_v<IconType, std::monostate>)
			{
				icon.ToolTip(value);
			}
			else
			{
				self->m_tooltip = value;
			}
		}, self->m_icon);
	}

	void TaskbarIcon::onGuidChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto self = winrt::get_self<TaskbarIcon>(d.as<class_type>());
		std::visit([value = winrt::unbox_value<winrt::guid>(arg.NewValue()), self](auto&& icon)
		{
			using IconType = std::remove_reference_t<decltype(icon)>;
			if constexpr (!std::is_same_v<IconType, std::monostate>)
			{
				icon.Guid(value);
			}
			else
			{
				self->m_guid = value;
			}
		}, self->m_icon);
	}
}
