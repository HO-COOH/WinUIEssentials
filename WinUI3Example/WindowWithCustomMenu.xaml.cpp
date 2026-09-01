#include "pch.h"
#include "WindowWithCustomMenu.xaml.h"
#if __has_include("WindowWithCustomMenu.g.cpp")
#include "WindowWithCustomMenu.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    void WindowWithCustomMenu::myButton_Click(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>().Content(winrt::box_value(L"Clicked"));
    }
}
