#include "pch.h"
#include "TenMicaPage.xaml.h"
#if __has_include("TenMicaPage.g.cpp")
#include "TenMicaPage.g.cpp"
#endif


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    void TenMicaPage::Button_Click(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        winrt::WinUI3Example::TenMicaWindow{}.Activate();
    }
}
