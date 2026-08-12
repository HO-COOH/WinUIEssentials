#include "pch.h"
#include "TableAlternateRowColorsPage.xaml.h"
#if __has_include("TableAlternateRowColorsPage.g.cpp")
#include "TableAlternateRowColorsPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<TableAlternateRowColorsPage> s_tags{ L"table", L"alternaterowcolor", L"rowcolor", L"datagrid", L"control" };
}
