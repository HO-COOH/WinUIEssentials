#include "pch.h"
#include "TableGridLinesPage.xaml.h"
#if __has_include("TableGridLinesPage.g.cpp")
#include "TableGridLinesPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<TableGridLinesPage> s_tags{ L"table", L"gridlines", L"gridline", L"datagrid", L"control" };
}
