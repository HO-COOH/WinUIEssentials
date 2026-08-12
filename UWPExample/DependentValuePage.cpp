#include "pch.h"
#include "DependentValuePage.h"
#if __has_include("DependentValuePage.g.cpp")
#include "DependentValuePage.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Media.Animation.h>
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
    static PageTagRegister<DependentValuePage> s_tags{ L"dependencyproperty", L"dependencyproperties", L"animation", L"storyboard", L"value" };

    void DependentValuePage::ClickHandler(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        DoubleValueAnimation().Begin();
    }
}
