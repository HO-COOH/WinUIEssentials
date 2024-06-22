#include "pch.h"
#include "DependentValuePage.h"
#if __has_include("DependentValuePage.g.cpp")
#include "DependentValuePage.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Media.Animation.h>
using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
    void DependentValuePage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        DoubleValueAnimation().Begin();
    }
}
