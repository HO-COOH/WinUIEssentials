#include "pch.h"
#include "LineGraphPage.xaml.h"
#if __has_include("LineGraphPage.g.cpp")
#include "LineGraphPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

}


void winrt::WinUI3Example::implementation::LineGraphPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	static float x = 0.01;
	x += 0.01;
	Graph().AddPoint(x, ValueSlider().Value());
}
