#include "pch.h"
#include "CustomTitleBar.xaml.h"
#if __has_include("CustomTitleBar.g.cpp")
#include "CustomTitleBar.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    int32_t CustomTitleBar::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void CustomTitleBar::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void CustomTitleBar::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}

void winrt::WinUI3Example::implementation::CustomTitleBar::AppTitleBar_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    RightPaddingColumn().Width(winrt::Microsoft::UI::Xaml::GridLength{ 
        .Value = static_cast<double>(RightInset()),
        .GridUnitType = winrt::Microsoft::UI::Xaml::GridUnitType::Pixel
    });
}
