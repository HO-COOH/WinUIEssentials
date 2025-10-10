#include "pch.h"
#include "DefaultWindowCaptionButtonWorkaround.xaml.h"
#if __has_include("DefaultWindowCaptionButtonWorkaround.g.cpp")
#include "DefaultWindowCaptionButtonWorkaround.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    int32_t DefaultWindowCaptionButtonWorkaround::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void DefaultWindowCaptionButtonWorkaround::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
