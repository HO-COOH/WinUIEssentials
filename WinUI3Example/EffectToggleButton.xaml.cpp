#include "pch.h"
#include "EffectToggleButton.xaml.h"
#if __has_include("EffectToggleButton.g.cpp")
#include "EffectToggleButton.g.cpp"
#endif
#include "SystemBackdropType.h"
#include "WindowBackgroundHelper.h"

constexpr static wchar_t const* ButtonText[]
{
	L"Auto",
	L"Mica",
	L"Acrylic",
	L"Disabled"
};

namespace winrt::WinUI3Example::implementation
{
	winrt::WinUI3Example::WindowBackgroundHelper EffectToggleButton::Window()
	{
		return m_window;
	}

	void EffectToggleButton::Window(winrt::WinUI3Example::WindowBackgroundHelper const& value)
	{
		m_window = value;
		m_windowImpl = winrt::get_self<WindowBackgroundHelper>(m_window);
	}

	void EffectToggleButton::Button_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		m_effectIndex = (m_effectIndex + 1) % 4;
		m_windowImpl->SystemBackdrop(static_cast<SystemBackdropType>(m_effectIndex));
		
		EffectText().Text(ButtonText[m_effectIndex]);
	}

}
