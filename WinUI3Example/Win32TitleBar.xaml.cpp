#include "pch.h"
#include "Win32TitleBar.xaml.h"
#if __has_include("Win32TitleBar.g.cpp")
#include "Win32TitleBar.g.cpp"
#endif
using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    int32_t Win32TitleBar::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Win32TitleBar::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void Win32TitleBar::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        //myButton().Content(box_value(L"Clicked"));
    }
}
