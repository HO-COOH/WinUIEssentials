#include "pch.h"
#include "ScopedButtonDisablerPage.h"
#if __has_include("ScopedButtonDisablerPage.g.cpp")
#include "ScopedButtonDisablerPage.g.cpp"
#endif
#include <ScopedButtonDisabler.hpp>
#include <winrt/Windows.Storage.Pickers.h>
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
    static PageTagRegister<ScopedButtonDisablerPage> s_tags{ L"scopedbuttondisable", L"button", L"helper"};

    winrt::Windows::Foundation::IAsyncAction ScopedButtonDisablerPage::ClickHandler(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        winrt::Windows::Storage::Pickers::FileOpenPicker picker;
        picker.FileTypeFilter().Append(L"*");
        if (auto file = co_await picker.PickSingleFileAsync())
            FilePathText().Text(file.Path());
    }


    winrt::Windows::Foundation::IAsyncAction ScopedButtonDisablerPage::ButtonWithScopeDisabler_Click(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        ScopedButtonDisabler disabler{ sender };
        winrt::Windows::Storage::Pickers::FileOpenPicker picker;
        picker.FileTypeFilter().Append(L"*");
        if (auto file = co_await picker.PickSingleFileAsync())
            FilePathText().Text(file.Path());
    }

}

