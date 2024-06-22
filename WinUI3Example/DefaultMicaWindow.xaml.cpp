#include "pch.h"
#include "DefaultMicaWindow.xaml.h"
#if __has_include("DefaultMicaWindow.g.cpp")
#include "DefaultMicaWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind DefaultMicaWindow::ToMicaKind(winrt::Windows::Foundation::IInspectable const& selection)
	{
		if (!selection)
			return{};

		auto str = winrt::unbox_value<winrt::hstring>(selection);
		if (str == L"Base") return winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind::Base;
		return winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind::BaseAlt;
	}
}
