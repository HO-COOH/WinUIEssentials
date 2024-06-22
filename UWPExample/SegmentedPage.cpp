#include "pch.h"
#include "SegmentedPage.h"
#if __has_include("SegmentedPage.g.cpp")
#include "SegmentedPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
    winrt::Windows::UI::Xaml::Controls::ListViewSelectionMode SegmentedPage::ConvertToSelectionMode(winrt::Windows::Foundation::IInspectable value)
    {
        return winrt::unbox_value<winrt::hstring>(value) == L"Single" ?
            winrt::Windows::UI::Xaml::Controls::ListViewSelectionMode::Single :
            winrt::Windows::UI::Xaml::Controls::ListViewSelectionMode::Multiple;
    }
    winrt::Windows::UI::Xaml::HorizontalAlignment SegmentedPage::ConvertToHorizontalAlignment(winrt::Windows::Foundation::IInspectable value)
    {
        if (auto strValue = winrt::unbox_value<winrt::hstring>(value); strValue == L"Left") return winrt::Windows::UI::Xaml::HorizontalAlignment::Left;
        else if (strValue == L"Center") return winrt::Windows::UI::Xaml::HorizontalAlignment::Center;
        else if (strValue == L"Right") return winrt::Windows::UI::Xaml::HorizontalAlignment::Right;
        else return winrt::Windows::UI::Xaml::HorizontalAlignment::Stretch;
    }
}
