#include "pch.h"
#include "DatePickerHelperPage.xaml.h"
#if __has_include("DatePickerHelperPage.g.cpp")
#include "DatePickerHelperPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<DatePickerHelperPage> s_tags{ L"datepicker", L"datepickerhelper", L"acrylic", L"workaround", L"helper" };

}
