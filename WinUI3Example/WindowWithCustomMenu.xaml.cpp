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
    int32_t WindowWithCustomMenu::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void WindowWithCustomMenu::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void WindowWithCustomMenu::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
