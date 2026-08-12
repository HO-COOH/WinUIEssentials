#include "pch.h"
#include "SliderHelperPage.xaml.h"
#if __has_include("SliderHelperPage.g.cpp")
#include "SliderHelperPage.g.cpp"
#endif
#include "PageTagRegister.h"


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<SliderHelperPage> s_tags{ L"slider", L"sliderhelper", L"acrylic", L"workaround", L"helper" };
}
