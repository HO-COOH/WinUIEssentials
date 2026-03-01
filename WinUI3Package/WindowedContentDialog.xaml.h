#pragma once

#include "WindowedContentDialog.g.h"

#include <winrt/Microsoft.UI.Windowing.h>
#include "ModalWindowBase.hpp"
#include "NonMaximizableWindowWorkaround.h"
#include "WinUIAsyncEventArgs.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog>, ModalWindowBase<WindowedContentDialog>
    {
		WindowedContentDialog();

		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync();
		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync(Microsoft::UI::Xaml::Window const& parent);

		void UpdateWindowSize();

		void OnContentLoaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

		void OnClosingRequestedBySystem();

		void OnClosingRequstedByCode();

		void DetermineTitleBarButtonForegroundColor();

		Microsoft::UI::Xaml::Controls::ContentDialogResult Result() const;
		winrt::WinUI3Package::ContentDialogContent ContentDialogContent();

		WinUI3Package::UnderlayMode Underlay() const;
		void Underlay(WinUI3Package::UnderlayMode const& value);

		WinUI3Package::UnderlaySystemBackdropOptions UnderlaySystemBackdrop() const;
		void UnderlaySystemBackdrop(WinUI3Package::UnderlaySystemBackdropOptions const& value);
	private:
		void open();

		void Result(const Microsoft::UI::Xaml::Controls::ContentDialogResult& value);
		void CloseByButtonAction(Microsoft::UI::Xaml::Controls::ContentDialogResult result);

		void SetupUnderlay();
		void SetupSmokeLayer();
		void SetupSystemBackdrop();
		void CleanupUnderlay();
		void SizeToXamlRoot(Microsoft::UI::Xaml::FrameworkElement element, Microsoft::UI::Xaml::Window window);
		int GetTitleBarOffset();
		void OnOwnerWindowSizeChanged(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args);

		Microsoft::UI::Windowing::OverlappedPresenter _presenter{ nullptr };

		Microsoft::UI::Xaml::Controls::ContentDialogResult _Result;

		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Windows::Foundation::IInspectable>> m_Opened;

		winrt::event_token m_Closing;
		winrt::event_token m_Closed;
		winrt::event_token m_Activated;

		winrt::event_token m_ActualThemeChanged;

		WinUI3Package::UnderlayMode m_underlay{ WinUI3Package::UnderlayMode::SmokeLayer };
		WinUI3Package::UnderlaySystemBackdropOptions m_underlaySystemBackdrop{ nullptr };

		Microsoft::UI::Xaml::Controls::Primitives::Popup m_Popup{ nullptr };
		Microsoft::UI::Xaml::Shapes::Rectangle m_SmokeLayerCache{ nullptr };
		Microsoft::UI::Xaml::Controls::Border m_BackdropLayerCache{ nullptr };
		winrt::event_token m_OnOwnerWindowSizeChanged;

		WinUI3Package::NonMaximizableWindowWorkaround m_windowWorkaround{ nullptr };

		winrt::com_ptr<WinUIAsyncEventArgs> AsyncEventArgs = winrt::make_self<WinUIAsyncEventArgs>();
		winrt::Windows::Foundation::Deferral Deferral{ nullptr };

    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog, implementation::WindowedContentDialog>
    {
    };
}
