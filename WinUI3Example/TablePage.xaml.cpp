#include "pch.h"
#include "TablePage.xaml.h"
#if __has_include("TablePage.g.cpp")
#include "TablePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    int32_t TablePage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void TablePage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
