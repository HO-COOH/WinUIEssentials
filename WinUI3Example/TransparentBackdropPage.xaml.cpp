#include "pch.h"
#include "TransparentBackdropPage.xaml.h"
#if __has_include("TransparentBackdropPage.g.cpp")
#include "TransparentBackdropPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	static PageTagRegister<TransparentBackdropPage> s_tags{ L"transparentwindow", L"transparent", L"backdrop", L"systembackdrop", L"window" };

	void TransparentBackdropPage::CreateTransparentButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::TransparentWindowDemo{}.Activate();
	}
}
