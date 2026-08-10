#include "pch.h"
#include "CodeWindowPage.h"
#if __has_include("CodeWindowPage.g.cpp")
#include "CodeWindowPage.g.cpp"
#endif

namespace winrt::UWPExample::implementation
{
    CodeWindowPage::CodeWindowPage(
        winrt::hstring const& title,
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& codeItems
    ) : m_title{ title }, m_codeItems{ codeItems }
    {
        winrt::Windows::ApplicationModel::Core::CoreApplication::GetCurrentView().TitleBar().ExtendViewIntoTitleBar(true);
        auto titleBar = winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TitleBar();
        titleBar.ButtonBackgroundColor(winrt::Windows::UI::Colors::Transparent());
        titleBar.ButtonInactiveBackgroundColor(winrt::Windows::UI::Colors::Transparent());
    }

    void CodeWindowPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        /*
            SetTitleBar needs the x:Name field, which only exists after InitializeComponent,
            i.e. after the constructor has returned.
        */
        winrt::Windows::UI::Xaml::Window::Current().SetTitleBar(TitleBarDragRegion());
    }
}
