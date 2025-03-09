#include "pch.h"
#include "EssentialWindowWithMenu.xaml.h"
#if __has_include("EssentialWindowWithMenu.g.cpp")
#include "EssentialWindowWithMenu.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    void EssentialWindowWithMenu::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
