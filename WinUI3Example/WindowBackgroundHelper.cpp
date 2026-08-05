#include "pch.h"
#include "WindowBackgroundHelper.h"
#if __has_include("WindowBackgroundHelper.g.cpp")
#include "WindowBackgroundHelper.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	WindowBackgroundHelper::WindowBackgroundHelper()
	{
		ActualThemeChanged([this](auto&&...)
		{
			if (!m_window)
				return;
			setBackgroundWithType();
		});
	}

	winrt::Microsoft::UI::Xaml::Window WindowBackgroundHelper::Window()
	{
		return m_window;
	}

	void WindowBackgroundHelper::Window(winrt::Microsoft::UI::Xaml::Window const& value)
	{
		if (m_window == value)
			return;
		m_window = value;
		applyBackdrop();
	}

	void WindowBackgroundHelper::SystemBackdrop(SystemBackdropType type)
	{
		//Only rebuild when the requested type actually changed (or nothing has been applied yet).
		if (m_type == type && m_backdropApplied)
			return;
		m_type = type;
		applyBackdrop();
	}

	void WindowBackgroundHelper::applyBackdrop()
	{
		if (!m_window)
			return;

		switch (m_type)
		{
			case SystemBackdropType::Automatic:
			{
				winrt::WinUI3Package::TenMicaBackdrop tenMica;
				tenMica.BindThemeTo(*this);
				m_window.SystemBackdrop(winrt::WinUI3Package::MicaBackdropWithFallback{ tenMica /*winrt::Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop{}*/ });
				break;
			}
			case SystemBackdropType::Mica:
				m_window.SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::MicaBackdrop{});
				break;
			case SystemBackdropType::Acrylic:
				m_window.SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop{});
				break;
			case SystemBackdropType::Disabled:
				m_window.SystemBackdrop(nullptr);
				break;
		}
		m_backdropApplied = true;
		setBackgroundWithType();
	}

	void WindowBackgroundHelper::setBackground(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush const& brush)
	{
		auto parent = Parent();
		if (auto panel = parent.try_as<winrt::Microsoft::UI::Xaml::Controls::Panel>())
			panel.Background(brush);
		else if (auto control = parent.try_as<winrt::Microsoft::UI::Xaml::Controls::Control>())
			control.Background(brush);
	}

	void WindowBackgroundHelper::setBackgroundWithType()
	{
		if (m_type == SystemBackdropType::Disabled)
		{
			//no systemBackdrop, means there are no window effect. We need to change the window background
			setBackground(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{
				ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Dark ? winrt::Windows::UI::Colors::Black() : winrt::Windows::UI::Colors::White()
			});
		}
		else
			setBackground(nullptr);//if there are systemBackdrop, make background transparent
	}
}
