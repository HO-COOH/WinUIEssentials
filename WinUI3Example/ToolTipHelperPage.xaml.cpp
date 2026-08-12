#include "pch.h"
#include "ToolTipHelperPage.xaml.h"
#if __has_include("ToolTipHelperPage.g.cpp")
#include "ToolTipHelperPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<ToolTipHelperPage> s_tags{ L"tooltip", L"tooltiphelper", L"acrylic", L"workaround", L"helper" };

}
