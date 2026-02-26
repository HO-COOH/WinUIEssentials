#pragma once

#include "WindowedContentDialog.g.h"
#include "ContentDialogWindow.xaml.h"


namespace winrt::WinUI3Package::implementation
{
	struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog>
	{
		WindowedContentDialog();
		~WindowedContentDialog();

		double ContentMinWidth();
		void ContentMinWidth(double value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty ContentMinWidthProperty();

		winrt::Microsoft::UI::Xaml::FlowDirection ContentFlowDirection();
		void ContentFlowDirection(winrt::Microsoft::UI::Xaml::FlowDirection const& value);
		static winrt::Microsoft::UI::Xaml::DependencyProperty ContentFlowDirectionProperty();

		void Close();
		void InitializeContentDialogWindow();
		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync();
		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync(winrt::Microsoft::UI::Xaml::Window const& parent);
		WinUI3Package::ContentDialogWindow GetDialogWindow();
		void SetUnderlay(WinUI3Package::ContentDialogWindow const& dialogWindow);
		void HandleSmokeLayer(WinUI3Package::ContentDialogWindow const& dialogWindow);
		void HandleSystemBackdrop(WinUI3Package::ContentDialogWindow const& dialogWindow);
		void DisableOwnerEvents(WinUI3Package::ContentDialogWindow const& dialogWindow);
		void SizeToXamlRoot(Microsoft::UI::Xaml::FrameworkElement element, Microsoft::UI::Xaml::Window window);
		void DialogWindow_Opened(WinUI3Package::ContentDialogWindow const& sender, winrt::Windows::Foundation::IInspectable const& e);
		void DialogWindow_Closed(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& e);
		void DialogWindow_ClosedPopup(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& e);
		void OnOwnerWindowSizeChanged(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args);
		void OnContentRightTapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs const& e);
		int GetTitleBarOffset();

		winrt::event_token Opened(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Windows::Foundation::IInspectable> const& handler);
		void Opened(winrt::event_token const& token);
		winrt::event_token Closed(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Microsoft::UI::Xaml::WindowEventArgs> const& handler);
		void Closed(winrt::event_token const& token);
		winrt::event_token ContentRightTapped(Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs> const& handler);
		void ContentRightTapped(winrt::event_token const& token);
		winrt::event_token PrimaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void PrimaryButtonClick(winrt::event_token const& token);
		winrt::event_token SecondaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void SecondaryButtonClick(winrt::event_token const& token);
		winrt::event_token CloseButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void CloseButtonClick(winrt::event_token const& token);

		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> PrimaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> SecondaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> CloseButtonKeyboardAccelerators();

		static void OnIsPrimaryButtonEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e);
		static void OnIsSecondaryButtonEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e);

		Microsoft::UI::Xaml::Media::Imaging::BitmapImage HeaderImage() const;
		void HeaderImage(const Microsoft::UI::Xaml::Media::Imaging::BitmapImage& value);

		winrt::hstring HeaderImageUri() const;
		void HeaderImageUri(const winrt::hstring& value);

		Microsoft::UI::Xaml::Shapes::Rectangle SmokeLayerCache() const;
		void SmokeLayerCache(const Microsoft::UI::Xaml::Shapes::Rectangle& value);

		Microsoft::UI::Xaml::Controls::Border BackdropLayerCache() const;
		void BackdropLayerCache(const Microsoft::UI::Xaml::Controls::Border& value);

		winrt::hstring WindowTitle() const;
		void WindowTitle(const winrt::hstring& value);

		winrt::Windows::Foundation::IInspectable Title() const;
		void Title(const winrt::Windows::Foundation::IInspectable& value);

		winrt::Windows::Foundation::IInspectable Content() const;
		void Content(const winrt::Windows::Foundation::IInspectable& value);

		Microsoft::UI::Xaml::ElementTheme RequestedTheme() const;
		void RequestedTheme(const Microsoft::UI::Xaml::ElementTheme& value);

		Microsoft::UI::Xaml::Media::SystemBackdrop SystemBackdrop() const;
		void SystemBackdrop(const Microsoft::UI::Xaml::Media::SystemBackdrop& value);

		Microsoft::UI::Xaml::DataTemplate TitleTemplate() const;
		void TitleTemplate(const Microsoft::UI::Xaml::DataTemplate& value);

		Microsoft::UI::Xaml::DataTemplate ContentTemplate() const;
		void ContentTemplate(const Microsoft::UI::Xaml::DataTemplate& value);

		winrt::hstring PrimaryButtonText() const;
		void PrimaryButtonText(const winrt::hstring& value);

		winrt::hstring SecondaryButtonText() const;
		void SecondaryButtonText(const winrt::hstring& value);

		winrt::hstring CloseButtonText() const;
		void CloseButtonText(const winrt::hstring& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty IsPrimaryButtonEnabledProperty();
		bool IsPrimaryButtonEnabled() const;
		void IsPrimaryButtonEnabled(const bool& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty IsSecondaryButtonEnabledProperty();
		bool IsSecondaryButtonEnabled() const;
		void IsSecondaryButtonEnabled(const bool& value);

		Microsoft::UI::Xaml::Controls::ContentDialogButton DefaultButton() const;
		void DefaultButton(const Microsoft::UI::Xaml::Controls::ContentDialogButton& value);

		WinUI3Package::UnderlayMode Underlay() const;
		void Underlay(const WinUI3Package::UnderlayMode& value);

		WinUI3Package::UnderlaySystemBackdropOptions UnderlaySystemBackdrop() const;
		void UnderlaySystemBackdrop(const WinUI3Package::UnderlaySystemBackdropOptions& value);

		bool CenterInParent() const;
		void CenterInParent(const bool& value);

		Microsoft::UI::Xaml::Style PrimaryButtonStyle() const;
		void PrimaryButtonStyle(const Microsoft::UI::Xaml::Style& value);

		Microsoft::UI::Xaml::Style SecondaryButtonStyle() const;
		void SecondaryButtonStyle(const Microsoft::UI::Xaml::Style& value);

		Microsoft::UI::Xaml::Style CloseButtonStyle() const;
		void CloseButtonStyle(const Microsoft::UI::Xaml::Style& value);

		bool HasTitleBar() const;
		void HasTitleBar(const bool& value);

		bool IsResizable() const;
		void IsResizable(const bool& value);

	private:
		winrt::Microsoft::UI::Xaml::Window ownerWindow();

		static winrt::Microsoft::UI::Xaml::DependencyProperty _ContentFlowDirectionProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _ContentMinWidthProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _IsPrimaryButtonEnabledProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _IsSecondaryButtonEnabledProperty;

		WinUI3Package::ContentDialogWindow m_ContentDialogWindow;
		ContentDialogWindow* m_contentDialogWindowImpl = winrt::get_self<ContentDialogWindow>(m_ContentDialogWindow);
		Microsoft::UI::Xaml::Controls::Primitives::Popup m_Popup{ nullptr };

		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Windows::Foundation::IInspectable>> m_Loaded;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Microsoft::UI::Xaml::WindowEventArgs>> m_Closed;
		winrt::event<Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs>> m_ContentRightTapped;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_PrimaryButtonClick;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_SecondaryButtonClick;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_CloseButtonClick;

		winrt::event_token m_DialogWindow_Opened;
		winrt::event_token m_DialogWindow_Closed;
		winrt::event_token m_onPopupLoaded;
		winrt::event_token m_onPopupOpened;
		winrt::event_token m_onPopupClosed;
		winrt::event_token m_OnOwnerWindowSizeChanged;

		winrt::handle m_DialogEvent;

		Microsoft::UI::Xaml::Media::Imaging::BitmapImage _HeaderImage{ nullptr };
		winrt::hstring _HeaderImageUri;
		Microsoft::UI::Xaml::Shapes::Rectangle _SmokeLayerCache{ nullptr };
		Microsoft::UI::Xaml::Controls::Border _BackdropLayerCache{ nullptr };
		winrt::hstring _WindowTitle;
		winrt::Windows::Foundation::IInspectable _Title{ nullptr };
		winrt::Windows::Foundation::IInspectable _Content{ nullptr };
		Microsoft::UI::Xaml::ElementTheme _RequestedTheme;
		Microsoft::UI::Xaml::Media::SystemBackdrop _SystemBackdrop{ nullptr };
		Microsoft::UI::Xaml::DataTemplate _TitleTemplate{ nullptr };
		Microsoft::UI::Xaml::DataTemplate _ContentTemplate{ nullptr };
		winrt::hstring _PrimaryButtonText;
		winrt::hstring _SecondaryButtonText;
		winrt::hstring _CloseButtonText;
		Microsoft::UI::Xaml::Controls::ContentDialogButton _DefaultButton;
		WinUI3Package::UnderlayMode _Underlay;
		WinUI3Package::UnderlaySystemBackdropOptions _UnderlaySystemBackdrop{ nullptr };
		bool _CenterInParent;
		Microsoft::UI::Xaml::Style _PrimaryButtonStyle{ nullptr };
		Microsoft::UI::Xaml::Style _SecondaryButtonStyle{ nullptr };
		Microsoft::UI::Xaml::Style _CloseButtonStyle{ nullptr };
		bool _HasTitleBar;
		bool _IsResizable;
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
	struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog, implementation::WindowedContentDialog>
	{
	};
}