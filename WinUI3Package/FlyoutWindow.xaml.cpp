#include "pch.h"
#include "FlyoutWindow.xaml.h"
#if __has_include("FlyoutWindow.g.cpp")
#include "FlyoutWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Package::implementation
{
    int32_t FlyoutWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void FlyoutWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void FlyoutWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
