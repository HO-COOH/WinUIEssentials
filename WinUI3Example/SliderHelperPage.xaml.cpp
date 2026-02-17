#include "pch.h"
#include "SliderHelperPage.xaml.h"
#if __has_include("SliderHelperPage.g.cpp")
#include "SliderHelperPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    int32_t SliderHelperPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SliderHelperPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
