#include "pch.h"
#include "TestBackdropSwitch.xaml.h"
#if __has_include("TestBackdropSwitch.g.cpp")
#include "TestBackdropSwitch.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void TestBackdropSwitch::ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		auto box = sender.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
		auto index = box.SelectedIndex();
		if (index == 0)
		{
			winrt::WinUI3Package::CustomMicaBackdrop backdrop;
			backdrop.Kind(winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind::BaseAlt);
			SystemBackdrop(backdrop);
		}
		else
		{
			winrt::WinUI3Package::CustomAcrylicBackdrop backdrop;
			backdrop.Kind(winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind::Thin);
			SystemBackdrop(backdrop);
		}
	}

}
