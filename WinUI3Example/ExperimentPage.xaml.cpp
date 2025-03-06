#include "pch.h"
#include "ExperimentPage.xaml.h"
#if __has_include("ExperimentPage.g.cpp")
#include "ExperimentPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	void ExperimentPage::TestWindowBtn_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::WinUI3Example::TestWindow{}.Activate();
	}

}
