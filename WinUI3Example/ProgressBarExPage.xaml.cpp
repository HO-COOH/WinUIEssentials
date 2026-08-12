#include "pch.h"
#include "ProgressBarExPage.xaml.h"
#if __has_include("ProgressBarExPage.g.cpp")
#include "ProgressBarExPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<ProgressBarExPage> s_tags{ L"progressbarex", L"progressbar", L"progress", L"percent", L"control" };
}
