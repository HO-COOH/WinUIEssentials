#include "pch.h"
#include "HeaderlessTablePage.xaml.h"
#if __has_include("HeaderlessTablePage.g.cpp")
#include "HeaderlessTablePage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<HeaderlessTablePage> s_tags{ L"table", L"headerless", L"header", L"datagrid", L"control" };
 
}
