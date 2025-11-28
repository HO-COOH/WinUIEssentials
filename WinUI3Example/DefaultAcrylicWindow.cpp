#include "pch.h"
#include "DefaultAcrylicWindow.xaml.h"
#if __has_include("DefaultAcrylicWindow.g.cpp")
#include "DefaultAcrylicWindow.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind DefaultAcrylicWindow::ToAcrylicKind(winrt::Windows::Foundation::IInspectable const& selection)
	{
		if (!selection)
			return {};

		auto str = winrt::unbox_value<winrt::hstring>(selection);
		if (str == L"Default") return winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind::Default;
		else if (str == L"Base") return winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind::Base;
		else if (str == L"Thin") return winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind::Thin;
	}
}
