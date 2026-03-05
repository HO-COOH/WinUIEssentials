#pragma once

#include "ModernDialogBox.g.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include "ModalWindowBase.hpp"
#include "NonMaximizableWindowWorkaround.h"
#include "WinUIAsyncEventArgs.hpp"

namespace winrt::WinUI3Package::implementation
{
	struct ModernDialogBoxContent;

	struct ModernDialogBox : ModernDialogBoxT<ModernDialogBox>, ModalWindowBase<ModernDialogBox>
	{
		ModernDialogBox();

		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync();
		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync(Microsoft::UI::Xaml::Window const& parent);

		void OnContentLoaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

		Microsoft::UI::Xaml::Controls::ContentDialogResult Result() const;
		winrt::WinUI3Package::ModernDialogBoxContent DialogContent();

		WinUI3Package::UnderlayMode Underlay() const;
		void Underlay(WinUI3Package::UnderlayMode const& value);

		WinUI3Package::UnderlaySystemBackdropOptions UnderlaySystemBackdrop() const;
		void UnderlaySystemBackdrop(WinUI3Package::UnderlaySystemBackdropOptions const& value);

		constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/ModernDialogBox.xaml";
	private:
		void updateWindowSize();

		void onClosingRequestedBySystem();

		void onClosingRequstedByCode();

		void determineTitleBarButtonForegroundColor();

		void open();

		void Result(const Microsoft::UI::Xaml::Controls::ContentDialogResult& value);
		void closeByButtonAction(Microsoft::UI::Xaml::Controls::ContentDialogResult result);

		void setupUnderlay();
		void setupSmokeLayer();
		void setupSystemBackdrop();
		void cleanupUnderlay();
		void sizeToXamlRoot(Microsoft::UI::Xaml::FrameworkElement element, Microsoft::UI::Xaml::Window window);
		int getTitleBarOffset();
		void onOwnerWindowSizeChanged(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args);

		Microsoft::UI::Windowing::OverlappedPresenter _presenter{ nullptr };

		Microsoft::UI::Xaml::Controls::ContentDialogResult _Result;

		winrt::event_token m_Closing;
		winrt::event_token m_Closed;

		winrt::event_token m_ActualThemeChanged;

		WinUI3Package::UnderlayMode m_underlay{ WinUI3Package::UnderlayMode::SmokeLayer };
		WinUI3Package::UnderlaySystemBackdropOptions m_underlaySystemBackdrop{ nullptr };

		Microsoft::UI::Xaml::Controls::Primitives::Popup m_Popup{ nullptr };
		Microsoft::UI::Xaml::Shapes::Rectangle m_SmokeLayerCache{ nullptr };
		Microsoft::UI::Xaml::Controls::Border m_BackdropLayerCache{ nullptr };
		winrt::Microsoft::UI::Xaml::Window::SizeChanged_revoker m_onOwnerWindowSizeChanged;

		WinUI3Package::NonMaximizableWindowWorkaround m_windowWorkaround{ nullptr };

		winrt::WinUI3Package::implementation::ModernDialogBoxContent* m_contentImpl{ nullptr };

		winrt::com_ptr<WinUIAsyncEventArgs> AsyncEventArgs = winrt::make_self<WinUIAsyncEventArgs>();
		winrt::Windows::Foundation::Deferral Deferral{ nullptr };

	};
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ModernDialogBox : ModernDialogBoxT<ModernDialogBox, implementation::ModernDialogBox>
    {
    };
}
