#include "pch.h"
#include "TimePickerHelperPage.xaml.h"
#if __has_include("TimePickerHelperPage.g.cpp")
#include "TimePickerHelperPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	static PageTagRegister<TimePickerHelperPage> s_tags{ L"timepicker", L"timepickerhelper", L"acrylic", L"workaround", L"helper" };

	winrt::Windows::Foundation::TimeSpan TimePickerHelperPage::CurrentTime()
	{
		SYSTEMTIME st;
		::GetLocalTime(&st);
		return std::chrono::hours(st.wHour) + std::chrono::minutes(st.wMinute) + std::chrono::seconds(st.wSecond);
	}
}
