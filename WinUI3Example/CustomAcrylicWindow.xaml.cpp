#include "pch.h"
#include "CustomAcrylicWindow.xaml.h"
#if __has_include("CustomAcrylicWindow.g.cpp")
#include "CustomAcrylicWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind CustomAcrylicWindow::ToAcrylicKind(winrt::Windows::Foundation::IInspectable const& selection)
	{
		if (!selection)
			return {};

		auto str = winrt::unbox_value<winrt::hstring>(selection);
		if (str == L"Default") return winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind::Default;
		else if (str == L"Base") return winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind::Base;
		else if (str == L"Thin") return winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind::Thin;
	}
	float CustomAcrylicWindow::DoubleToSingle(double value)
	{
		return static_cast<float>(value);
	}
}
