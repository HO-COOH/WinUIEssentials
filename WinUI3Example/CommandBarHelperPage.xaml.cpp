#include "pch.h"
#include "CommandBarHelperPage.xaml.h"
#if __has_include("CommandBarHelperPage.g.cpp")
#include "CommandBarHelperPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<CommandBarHelperPage> s_tags{ L"commandbar", L"commandbarhelper", L"acrylic", L"workaround", L"helper" };
}
