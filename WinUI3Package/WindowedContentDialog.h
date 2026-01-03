#pragma once

#include "WindowedContentDialog.g.h"

#include "include/cppwinrt_utils.h"

namespace winrt::WinUI3Package::implementation
{
	struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog>
	{
		WindowedContentDialog();
		~WindowedContentDialog();


		double ContentMinWidth() {

			return winrt::unbox_value<double>(GetValue(ContentMinWidthProperty()));

		}

		void ContentMinWidth(double value)
		{
			SetValue(ContentMinWidthProperty(), winrt::box_value(value));
		}

		static winrt::Microsoft::UI::Xaml::DependencyProperty ContentMinWidthProperty()
		{
			return _ContentMinWidthProperty;
		}

		winrt::Microsoft::UI::Xaml::FlowDirection ContentFlowDirection() {

			return winrt::unbox_value<winrt::Microsoft::UI::Xaml::FlowDirection>(GetValue(ContentFlowDirectionProperty()));

		}

		void ContentFlowDirection(winrt::Microsoft::UI::Xaml::FlowDirection const& value)
		{
			SetValue(ContentFlowDirectionProperty(), winrt::box_value(value));
		}

		static winrt::Microsoft::UI::Xaml::DependencyProperty ContentFlowDirectionProperty()
		{
			return _ContentFlowDirectionProperty;
		}

		void Close();

		void InitializeContentDialogWindow();

		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync();

		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync(bool isModal);

		WinUI3Package::ContentDialogWindow GetDialogWindow() { return m_ContentDialogWindow; };

		void UpdateWindowSize();

		void SetUnderlay(WinUI3Package::ContentDialogWindow const& dialogWindow);

		void HandleSmokeLayer(WinUI3Package::ContentDialogWindow const& dialogWindow);

		void HandleSystemBackdrop(WinUI3Package::ContentDialogWindow const& dialogWindow);

		void DisableOwnerEvents(WinUI3Package::ContentDialogWindow const& dialogWindow);

		void AttachPopupLifecycle(WinUI3Package::ContentDialogWindow const& dialogWindow, Microsoft::UI::Xaml::Controls::Primitives::Popup const& popup, bool isSmokeLayer);

		void SizeToXamlRoot(Microsoft::UI::Xaml::FrameworkElement element, Microsoft::UI::Xaml::Window window);

		void DialogWindow_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);

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

		winrt::event_token ContentRightTapped(Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable,  winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs> const& handler);
		void ContentRightTapped(winrt::event_token const& token);

		winrt::event_token PrimaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void PrimaryButtonClick(winrt::event_token const& token);

		winrt::event_token SecondaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void SecondaryButtonClick(winrt::event_token const& token);

		winrt::event_token CloseButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void CloseButtonClick(winrt::event_token const& token);

		winrt::Windows::Foundation::Collections::IVector< winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> PrimaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector< winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> SecondaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector< winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> CloseButtonKeyboardAccelerators();


		static void OnIsPrimaryButtonEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
		{
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);

			//winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, IsEnabled() ? NormalState : DisabledState, true);

			auto self = get_self<WindowedContentDialog>(sender.as<winrt::WinUI3Package::WindowedContentDialog>());

			self->m_ContentDialogWindow.IsPrimaryButtonEnabled(e.NewValue().as<bool>());

		}


		static void OnIsSecondaryButtonEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
		{
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);

			//winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, IsEnabled() ? NormalState : DisabledState, true);

			auto self = get_self<WindowedContentDialog>(sender.as<winrt::WinUI3Package::WindowedContentDialog>());

			self->m_ContentDialogWindow.IsSecondaryButtonEnabled(e.NewValue().as<bool>());

		}


		DEFINE_PROPERTY2(Microsoft::UI::Xaml::Media::Imaging::BitmapImage, HeaderImage);
		DEFINE_PROPERTY(winrt::hstring, HeaderImageUri);

		DEFINE_PROPERTY2(Microsoft::UI::Xaml::Shapes::Rectangle, SmokeLayerCache);
		DEFINE_PROPERTY2(Microsoft::UI::Xaml::Controls::Border, BackdropLayerCache);

		DEFINE_PROPERTY(winrt::hstring, WindowTitle);
		DEFINE_PROPERTY2(winrt::Windows::Foundation::IInspectable, Title);
		DEFINE_PROPERTY2(winrt::Windows::Foundation::IInspectable, Content);

		DEFINE_PROPERTY(Microsoft::UI::Xaml::ElementTheme, RequestedTheme);

		DEFINE_PROPERTY2(Microsoft::UI::Xaml::Media::SystemBackdrop, SystemBackdrop);

		// DEFINE_PROPERTY2(Microsoft::UI::Xaml::Media::Brush, Foreground);
		// DEFINE_PROPERTY2(Microsoft::UI::Xaml::Media::Brush, Background);
	   //  DEFINE_PROPERTY2(Microsoft::UI::Xaml::Media::Brush, BorderBrush);

		// DEFINE_PROPERTY(Microsoft::UI::Xaml::Thickness, BorderThickness);
		// DEFINE_PROPERTY(Microsoft::UI::Xaml::FlowDirection, FlowDirection);
		DEFINE_PROPERTY2(Microsoft::UI::Xaml::DataTemplate, TitleTemplate);
		DEFINE_PROPERTY2(Microsoft::UI::Xaml::DataTemplate, ContentTemplate);

		DEFINE_PROPERTY(winrt::hstring, PrimaryButtonText);
		DEFINE_PROPERTY(winrt::hstring, SecondaryButtonText);
		DEFINE_PROPERTY(winrt::hstring, CloseButtonText);

		//DEFINE_PROPERTY(bool, IsPrimaryButtonEnabled);
		//DEFINE_PROPERTY(bool, IsSecondaryButtonEnabled);

		DEPENDENCY_PROPERTY(bool, IsPrimaryButtonEnabled);
		DEPENDENCY_PROPERTY(bool, IsSecondaryButtonEnabled);

		DEFINE_PROPERTY(Microsoft::UI::Xaml::Controls::ContentDialogButton, DefaultButton);

		DEFINE_PROPERTY(WinUI3Package::UnderlayMode, Underlay);

		DEFINE_PROPERTY2(WinUI3Package::UnderlaySystemBackdropOptions, UnderlaySystemBackdrop);
		//DEFINE_PROPERTY2(WinUI3Package::UnderlaySmokeLayerOptions, UnderlaySmokeLayer);

		DEFINE_PROPERTY(bool, CenterInParent);


		DEFINE_PROPERTY2(Microsoft::UI::Xaml::Style, PrimaryButtonStyle);
		DEFINE_PROPERTY2(Microsoft::UI::Xaml::Style, SecondaryButtonStyle);
		DEFINE_PROPERTY2(Microsoft::UI::Xaml::Style, CloseButtonStyle);


		DEFINE_PROPERTY2(Microsoft::UI::Xaml::Window, OwnerWindow);

		DEFINE_PROPERTY(bool, HasTitleBar);
		DEFINE_PROPERTY(bool, IsResizable);


		//DEFINE_PROPERTY2(winrt::Windows::Foundation::Collections::IVector< winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator>, PrimaryButtonKeyboardAccelerators);
		//DEFINE_PROPERTY2(winrt::Windows::Foundation::Collections::IVector< winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator>, SecondaryButtonKeyboardAccelerators);
	   // DEFINE_PROPERTY2(winrt::Windows::Foundation::Collections::IVector< winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator>, CloseButtonKeyboardAccelerators);


	private:

		static winrt::Microsoft::UI::Xaml::DependencyProperty _ContentFlowDirectionProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _ContentMinWidthProperty;

		WinUI3Package::ContentDialogWindow m_ContentDialogWindow{ nullptr };

		Microsoft::UI::Xaml::Controls::Primitives::Popup m_Popup{ nullptr };


		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Windows::Foundation::IInspectable>> m_Loaded;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Microsoft::UI::Xaml::WindowEventArgs>> m_Closed;

		winrt::event<Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable,  winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs>> m_ContentRightTapped;


		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_PrimaryButtonClick;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_SecondaryButtonClick;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_CloseButtonClick;


		winrt::event_token m_DialogWindow_Opened;
		winrt::event_token m_DialogWindow_Closed;

		winrt::event_token m_onPopupLoaded;
		winrt::event_token m_onPopupOpened;
		winrt::event_token m_onPopupClosed;
		// winrt::event_token m_DialogWindow_Loaded;
		 //winrt::event_token m_DialogWindow_ClosedPopup;

		winrt::event_token m_OnOwnerWindowSizeChanged;

		winrt::event_token m_OnOwnerWindowSizeChanged_Loaded;


		winrt::handle m_DialogEvent;

	};
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog, implementation::WindowedContentDialog>
    {
    };
}
