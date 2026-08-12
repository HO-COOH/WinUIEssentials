#include "pch.h"
#include "XamlTableDataPage.xaml.h"
#if __has_include("XamlTableDataPage.g.cpp")
#include "XamlTableDataPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<XamlTableDataPage> s_tags{ L"table", L"tablerow", L"xaml", L"data", L"datagrid", L"control" };
}
