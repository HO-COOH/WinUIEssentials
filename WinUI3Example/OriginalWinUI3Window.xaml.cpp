#include "pch.h"
#include "OriginalWinUI3Window.xaml.h"
#if __has_include("OriginalWinUI3Window.g.cpp")
#include "OriginalWinUI3Window.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    int32_t OriginalWinUI3Window::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void OriginalWinUI3Window::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
