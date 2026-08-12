#include "pch.h"
#include "CalendarDatePickerWorkaroundPage.xaml.h"
#if __has_include("CalendarDatePickerWorkaroundPage.g.cpp")
#include "CalendarDatePickerWorkaroundPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<CalendarDatePickerWorkaroundPage> s_tags{ L"calendardatepicker", L"calendardatepickerhelper", L"calendar", L"datepicker", L"acrylic", L"workaround", L"helper" };

}
