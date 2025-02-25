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

}


void winrt::WinUI3Example::implementation::ExperimentPage::StackPanel_Loaded(
	winrt::Windows::Foundation::IInspectable const& sender, 
	winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	auto pro = MyViewModel().MyProperty();
	auto proValue = pro.as<winrt::Windows::Foundation::IPropertyValue>();
	auto value1 = proValue.GetInt32();
	try
	{
		proValue.GetDouble();
	}
	catch (winrt::hresult_not_implemented const&)
	{
		OutputDebugString(L"Catch\n");
	}
}
