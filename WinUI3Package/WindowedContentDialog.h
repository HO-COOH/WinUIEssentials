#pragma once

#include "WindowedContentDialog.g.h"
#include "ContentDialogWindow.xaml.h"


namespace winrt::WinUI3Package::implementation
{
	struct WindowedContentDialog : WindowedContentDialogT<WindowedContentDialog>
	{
		WindowedContentDialog();
		~WindowedContentDialog();

		double ContentMinWidth()
		{
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

		winrt::Microsoft::UI::Xaml::FlowDirection ContentFlowDirection()
		{
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
		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync(winrt::Microsoft::UI::Xaml::Window const& parent);
		WinUI3Package::ContentDialogWindow GetDialogWindow() { return m_ContentDialogWindow; };
		void SetUnderlay(WinUI3Package::ContentDialogWindow const& dialogWindow);
		void HandleSmokeLayer(WinUI3Package::ContentDialogWindow const& dialogWindow);
		void HandleSystemBackdrop(WinUI3Package::ContentDialogWindow const& dialogWindow);
		void DisableOwnerEvents(WinUI3Package::ContentDialogWindow const& dialogWindow);
		void AttachPopupLifecycle(WinUI3Package::ContentDialogWindow const& dialogWindow, Microsoft::UI::Xaml::Controls::Primitives::Popup const& popup, bool isSmokeLayer);
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

		static void OnIsPrimaryButtonEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
		{
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);
			auto self = get_self<WindowedContentDialog>(sender.as<winrt::WinUI3Package::WindowedContentDialog>());
			self->m_contentDialogWindowImpl->ContentDialogContent().IsPrimaryButtonEnabled(e.NewValue().as<bool>());
		}

		static void OnIsSecondaryButtonEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
		{
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);
			auto self = get_self<WindowedContentDialog>(sender.as<winrt::WinUI3Package::WindowedContentDialog>());
			self->m_contentDialogWindowImpl->ContentDialogContent().IsSecondaryButtonEnabled(e.NewValue().as<bool>());
		}

		// HeaderImage
		Microsoft::UI::Xaml::Media::Imaging::BitmapImage HeaderImage() const
		{
			return _HeaderImage;
		}
		void HeaderImage(const Microsoft::UI::Xaml::Media::Imaging::BitmapImage& value)
		{
			if (_HeaderImage != value)
			{
				_HeaderImage = value;
			}
		}

		// HeaderImageUri
		winrt::hstring HeaderImageUri() const
		{
			return _HeaderImageUri;
		}
		void HeaderImageUri(const winrt::hstring& value)
		{
			if (_HeaderImageUri != value)
			{
				_HeaderImageUri = value;
			}
		}

		// SmokeLayerCache
		Microsoft::UI::Xaml::Shapes::Rectangle SmokeLayerCache() const
		{
			return _SmokeLayerCache;
		}
		void SmokeLayerCache(const Microsoft::UI::Xaml::Shapes::Rectangle& value)
		{
			if (_SmokeLayerCache != value)
			{
				_SmokeLayerCache = value;
			}
		}

		// BackdropLayerCache
		Microsoft::UI::Xaml::Controls::Border BackdropLayerCache() const
		{
			return _BackdropLayerCache;
		}
		void BackdropLayerCache(const Microsoft::UI::Xaml::Controls::Border& value)
		{
			if (_BackdropLayerCache != value)
			{
				_BackdropLayerCache = value;
			}
		}

		// WindowTitle
		winrt::hstring WindowTitle() const
		{
			return _WindowTitle;
		}
		void WindowTitle(const winrt::hstring& value)
		{
			if (_WindowTitle != value)
			{
				_WindowTitle = value;
			}
		}

		// Title
		winrt::Windows::Foundation::IInspectable Title() const
		{
			return _Title;
		}
		void Title(const winrt::Windows::Foundation::IInspectable& value)
		{
			if (_Title != value)
			{
				_Title = value;
			}
		}

		// Content
		winrt::Windows::Foundation::IInspectable Content() const
		{
			return _Content;
		}
		void Content(const winrt::Windows::Foundation::IInspectable& value)
		{
			if (_Content != value)
			{
				_Content = value;
			}
		}

		// RequestedTheme
		Microsoft::UI::Xaml::ElementTheme RequestedTheme() const
		{
			return _RequestedTheme;
		}
		void RequestedTheme(const Microsoft::UI::Xaml::ElementTheme& value)
		{
			if (_RequestedTheme != value)
			{
				_RequestedTheme = value;
			}
		}

		// SystemBackdrop
		Microsoft::UI::Xaml::Media::SystemBackdrop SystemBackdrop() const
		{
			return _SystemBackdrop;
		}
		void SystemBackdrop(const Microsoft::UI::Xaml::Media::SystemBackdrop& value)
		{
			if (_SystemBackdrop != value)
			{
				_SystemBackdrop = value;
			}
		}

		// TitleTemplate
		Microsoft::UI::Xaml::DataTemplate TitleTemplate() const
		{
			return _TitleTemplate;
		}
		void TitleTemplate(const Microsoft::UI::Xaml::DataTemplate& value)
		{
			if (_TitleTemplate != value)
			{
				_TitleTemplate = value;
			}
		}

		// ContentTemplate
		Microsoft::UI::Xaml::DataTemplate ContentTemplate() const
		{
			return _ContentTemplate;
		}
		void ContentTemplate(const Microsoft::UI::Xaml::DataTemplate& value)
		{
			if (_ContentTemplate != value)
			{
				_ContentTemplate = value;
			}
		}

		// PrimaryButtonText
		winrt::hstring PrimaryButtonText() const
		{
			return _PrimaryButtonText;
		}
		void PrimaryButtonText(const winrt::hstring& value)
		{
			if (_PrimaryButtonText != value)
			{
				_PrimaryButtonText = value;
			}
		}

		// SecondaryButtonText
		winrt::hstring SecondaryButtonText() const
		{
			return _SecondaryButtonText;
		}
		void SecondaryButtonText(const winrt::hstring& value)
		{
			if (_SecondaryButtonText != value)
			{
				_SecondaryButtonText = value;
			}
		}

		// CloseButtonText
		winrt::hstring CloseButtonText() const
		{
			return _CloseButtonText;
		}
		void CloseButtonText(const winrt::hstring& value)
		{
			if (_CloseButtonText != value)
			{
				_CloseButtonText = value;
			}
		}

		// IsPrimaryButtonEnabled
		static winrt::Microsoft::UI::Xaml::DependencyProperty IsPrimaryButtonEnabledProperty()
		{
			return _IsPrimaryButtonEnabledProperty;
		}
		bool IsPrimaryButtonEnabled() const
		{
			return winrt::unbox_value<bool>(GetValue(_IsPrimaryButtonEnabledProperty));
		}
		void IsPrimaryButtonEnabled(const bool& value)
		{
			SetValue(_IsPrimaryButtonEnabledProperty, winrt::box_value(value));
		}

		// IsSecondaryButtonEnabled
		static winrt::Microsoft::UI::Xaml::DependencyProperty IsSecondaryButtonEnabledProperty()
		{
			return _IsSecondaryButtonEnabledProperty;
		}
		bool IsSecondaryButtonEnabled() const
		{
			return winrt::unbox_value<bool>(GetValue(_IsSecondaryButtonEnabledProperty));
		}
		void IsSecondaryButtonEnabled(const bool& value)
		{
			SetValue(_IsSecondaryButtonEnabledProperty, winrt::box_value(value));
		}

		// DefaultButton
		Microsoft::UI::Xaml::Controls::ContentDialogButton DefaultButton() const
		{
			return _DefaultButton;
		}
		void DefaultButton(const Microsoft::UI::Xaml::Controls::ContentDialogButton& value)
		{
			if (_DefaultButton != value)
			{
				_DefaultButton = value;
			}
		}

		// Underlay
		WinUI3Package::UnderlayMode Underlay() const
		{
			return _Underlay;
		}
		void Underlay(const WinUI3Package::UnderlayMode& value)
		{
			if (_Underlay != value)
			{
				_Underlay = value;
			}
		}

		// UnderlaySystemBackdrop
		WinUI3Package::UnderlaySystemBackdropOptions UnderlaySystemBackdrop() const
		{
			return _UnderlaySystemBackdrop;
		}
		void UnderlaySystemBackdrop(const WinUI3Package::UnderlaySystemBackdropOptions& value)
		{
			if (_UnderlaySystemBackdrop != value)
			{
				_UnderlaySystemBackdrop = value;
			}
		}

		// CenterInParent
		bool CenterInParent() const
		{
			return _CenterInParent;
		}
		void CenterInParent(const bool& value)
		{
			if (_CenterInParent != value)
			{
				_CenterInParent = value;
			}
		}

		// PrimaryButtonStyle
		Microsoft::UI::Xaml::Style PrimaryButtonStyle() const
		{
			return _PrimaryButtonStyle;
		}
		void PrimaryButtonStyle(const Microsoft::UI::Xaml::Style& value)
		{
			if (_PrimaryButtonStyle != value)
			{
				_PrimaryButtonStyle = value;
			}
		}

		// SecondaryButtonStyle
		Microsoft::UI::Xaml::Style SecondaryButtonStyle() const
		{
			return _SecondaryButtonStyle;
		}
		void SecondaryButtonStyle(const Microsoft::UI::Xaml::Style& value)
		{
			if (_SecondaryButtonStyle != value)
			{
				_SecondaryButtonStyle = value;
			}
		}

		// CloseButtonStyle
		Microsoft::UI::Xaml::Style CloseButtonStyle() const
		{
			return _CloseButtonStyle;
		}
		void CloseButtonStyle(const Microsoft::UI::Xaml::Style& value)
		{
			if (_CloseButtonStyle != value)
			{
				_CloseButtonStyle = value;
			}
		}

		// HasTitleBar
		bool HasTitleBar() const
		{
			return _HasTitleBar;
		}
		void HasTitleBar(const bool& value)
		{
			if (_HasTitleBar != value)
			{
				_HasTitleBar = value;
			}
		}

		// IsResizable
		bool IsResizable() const
		{
			return _IsResizable;
		}
		void IsResizable(const bool& value)
		{
			if (_IsResizable != value)
			{
				_IsResizable = value;
			}
		}

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
		//winrt::weak_ref<Microsoft::UI::Xaml::Window> _OwnerWindow{ nullptr };
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