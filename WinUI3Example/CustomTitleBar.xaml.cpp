#include "pch.h"
#include "CustomTitleBar.xaml.h"
#if __has_include("CustomTitleBar.g.cpp")
#include "CustomTitleBar.g.cpp"
#endif
#include <winrt/Microsoft.UI.Windowing.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    CustomTitleBar::CustomTitleBar()
    {
		ExtendsContentIntoTitleBar(true);
        AppWindow().TitleBar().PreferredHeightOption(winrt::Microsoft::UI::Windowing::TitleBarHeightOption::Tall);
    }

    void CustomTitleBar::myButton_Click(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }

    void CustomTitleBar::PersonPic_PointerPressed(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
    {
        PersonPicMenu().ShowAt(sender.as<winrt::Microsoft::UI::Xaml::FrameworkElement>());
    }
}
