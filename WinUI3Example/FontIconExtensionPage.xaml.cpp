#include "pch.h"
#include "FontIconExtensionPage.xaml.h"
#if __has_include("FontIconExtensionPage.g.cpp")
#include "FontIconExtensionPage.g.cpp"
#endif
#include "PageTagRegister.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<FontIconExtensionPage> s_tags{ L"fonticonextension", L"fonticon", L"icon", L"glyph", L"font", L"extension" };
}
