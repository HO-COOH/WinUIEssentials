#include "pch.h"
#include "SampleModalWindow.xaml.h"
#if __has_include("SampleModalWindow.g.cpp")
#include "SampleModalWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    SampleModalWindow::SampleModalWindow(winrt::Microsoft::UI::Xaml::Window const& parent) : 
        SampleModalWindowT{parent}
    {
    }
}
