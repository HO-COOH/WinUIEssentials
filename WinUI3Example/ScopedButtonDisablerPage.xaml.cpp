#include "pch.h"
#include "ScopedButtonDisablerPage.xaml.h"
#if __has_include("ScopedButtonDisablerPage.g.cpp")
#include "ScopedButtonDisablerPage.g.cpp"
#endif

#include <ScopedButtonDisabler.hpp>
#include <IInitializeWithWindowHelper.hpp>
#include "MainWindow.xaml.h"
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    winrt::Windows::Foundation::IAsyncAction ScopedButtonDisablerPage::ClickHandler(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        WinUIEssentials::Windows::Storage::Pickers::FileOpenPicker picker{ MainWindow::Hwnd };
        picker.FileTypeFilter().Append(L"*");
        if (auto file = co_await picker.PickSingleFileAsync())
            FilePathText().Text(file.Path());
    }


    winrt::Windows::Foundation::IAsyncAction ScopedButtonDisablerPage::ButtonWithScopeDisabler_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        ScopedButtonDisabler disabler{ sender };
        WinUIEssentials::Windows::Storage::Pickers::FileOpenPicker picker{ MainWindow::Hwnd };
        picker.FileTypeFilter().Append(L"*");
        if (auto file = co_await picker.PickSingleFileAsync())
            FilePathText().Text(file.Path());
    }
}
