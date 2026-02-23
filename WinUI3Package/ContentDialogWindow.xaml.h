#pragma once

#include "ContentDialogWindow.g.h"

#include <winrt/Microsoft.UI.Windowing.h>
#include "ModalWindowBase.hpp"

namespace winrt::WinUI3Package::implementation
{
	struct ContentDialogWindow : ContentDialogWindowT<ContentDialogWindow>, ModalWindowBase<ContentDialogWindow>
	{
		ContentDialogWindow();

		winrt::WinUI3Package::ContentDialogContent ContentDialogContent() {

			return this->ContentDialogContentControl();
		}


		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync();

		void UpdateWindowSize();


		//void UpdateWindowSize1();

		void OnContentLoaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

		void OnActivated(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowActivatedEventArgs args);

		void Open();

		void Hide();

		void OnClosingRequestedBySystem();

		void OnClosingRequstedByCode();

		void OnParentClosed(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs args);

		winrt::Windows::Foundation::IAsyncAction OnPrimaryButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& e);
		winrt::Windows::Foundation::IAsyncAction OnSecondaryButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& e);
		winrt::Windows::Foundation::IAsyncAction OnCloseButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& e);

		void OnContentRightTapped(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs const& e);


		winrt::event_token ContentRightTapped(Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs> const& handler);
		void ContentRightTapped(winrt::event_token const& token);


		void UpdateDragRegion(std::list<Microsoft::UI::Xaml::FrameworkElement> const& ElementsList);

		void DetermineTitleBarButtonForegroundColor();
		void AfterCommandSpaceButtonClick(WinUI3Package::ContentDialogWindowButtonClickEventArgs const& args);
		void SetParent(Microsoft::UI::Xaml::Window const& parent, bool modal, bool center);

		winrt::event_token Loaded(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, Windows::Foundation::IInspectable> const& handler);
		void Loaded(winrt::event_token const& token);

		winrt::event_token Opened(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, Windows::Foundation::IInspectable> const& handler);
		void Opened(winrt::event_token const& token);

		winrt::event_token PrimaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void PrimaryButtonClick(winrt::event_token const& token);

		winrt::event_token SecondaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void SecondaryButtonClick(winrt::event_token const& token);

		winrt::event_token CloseButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void CloseButtonClick(winrt::event_token const& token);

		void Foreground(Microsoft::UI::Xaml::Media::Brush const& brush);
		Microsoft::UI::Xaml::Media::Brush Foreground();

		void Background(Microsoft::UI::Xaml::Media::Brush const& brush);
		Microsoft::UI::Xaml::Media::Brush Background();

		void BorderBrush(Microsoft::UI::Xaml::Media::Brush const& brush);
		Microsoft::UI::Xaml::Media::Brush BorderBrush();

		void BorderThickness(Microsoft::UI::Xaml::Thickness const& thickness);
		Microsoft::UI::Xaml::Thickness BorderThickness();

		void FlowDirection(Microsoft::UI::Xaml::FlowDirection const& direction);
		Microsoft::UI::Xaml::FlowDirection FlowDirection();

		void TitleTemplate(Microsoft::UI::Xaml::DataTemplate const& dataTemplate);
		Microsoft::UI::Xaml::DataTemplate TitleTemplate();

		void ContentTemplate(Microsoft::UI::Xaml::DataTemplate const& dataTemplate);
		Microsoft::UI::Xaml::DataTemplate ContentTemplate();

		void PrimaryButtonText(winrt::hstring const& text);
		winrt::hstring PrimaryButtonText();

		void SecondaryButtonText(winrt::hstring const& text);
		winrt::hstring SecondaryButtonText();

		void CloseButtonText(winrt::hstring const& text);
		winrt::hstring CloseButtonText();

		void IsPrimaryButtonEnabled(bool enabled);
		bool IsPrimaryButtonEnabled();

		void IsSecondaryButtonEnabled(bool enabled);
		bool IsSecondaryButtonEnabled();

		void DefaultButton(Microsoft::UI::Xaml::Controls::ContentDialogButton button);
		Microsoft::UI::Xaml::Controls::ContentDialogButton DefaultButton();

		void PrimaryButtonStyle(Microsoft::UI::Xaml::Style const& style);
		Microsoft::UI::Xaml::Style PrimaryButtonStyle();

		void SecondaryButtonStyle(Microsoft::UI::Xaml::Style const& style);
		Microsoft::UI::Xaml::Style SecondaryButtonStyle();

		void CloseButtonStyle(Microsoft::UI::Xaml::Style const& style);
		Microsoft::UI::Xaml::Style CloseButtonStyle();

		void DialogTitle(winrt::Windows::Foundation::IInspectable const& title);
		winrt::Windows::Foundation::IInspectable DialogTitle();

		void DialogContent(winrt::Windows::Foundation::IInspectable const& content);
		winrt::Windows::Foundation::IInspectable DialogContent();

		void HasTitleBar(bool hasTitleBar);
		bool HasTitleBar();

		void IsResizable(bool isResizable);
		bool IsResizable();

		void RequestedTheme(Microsoft::UI::Xaml::ElementTheme theme);
		Microsoft::UI::Xaml::ElementTheme RequestedTheme();

		winrt::hstring HeaderImageUri();
		void HeaderImageUri(winrt::hstring const& Value);

		Microsoft::UI::Xaml::Media::Imaging::BitmapImage HeaderImage();
		void HeaderImage(Microsoft::UI::Xaml::Media::Imaging::BitmapImage const& Value);

		Microsoft::UI::Xaml::Controls::ContentDialogResult Result() const {

			return _Result;
		}

		void Result(const Microsoft::UI::Xaml::Controls::ContentDialogResult& value) {
			if (_Result != value) {
				_Result = value;
			}

		}

		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> PrimaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> SecondaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> CloseButtonKeyboardAccelerators();



	private:
		bool m_hasTitleBar = true;
		bool m_isResizable;

		winrt::hstring m_HeaderImageUri;

		Microsoft::UI::Xaml::Media::Imaging::BitmapImage m_HeaderImage{ nullptr };

		//WinUI3Package::ContentDialogContent content{ nullptr };;

		//winrt::Windows::Foundation::IInspectable m_DialogContent{ nullptr };

		Microsoft::UI::Windowing::OverlappedPresenter _presenter{ nullptr };

		bool _center;


		Microsoft::UI::Xaml::Controls::ContentDialogResult _Result;

		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, Windows::Foundation::IInspectable>> m_Loaded;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, Windows::Foundation::IInspectable>> m_Opened;

		winrt::event<Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs>> m_ContentRightTapped;


		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_PrimaryButtonClick;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_SecondaryButtonClick;
		winrt::event<Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_CloseButtonClick;


		//public event TypedEventHandler<ContentDialogWindow, ContentDialogWindowButtonClickEventArgs>? PrimaryButtonClick;

		winrt::event_token m_OnParentClosed;

		winrt::event_token m_OnPrimaryButtonClick;
		winrt::event_token m_OnSecondaryButtonClick;
		winrt::event_token m_OnCloseButtonClick;


		//winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_PrimaryButtonKeyboardAccelerators{ nullptr };
		//winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_SecondaryButtonKeyboardAccelerators{ nullptr };
		//winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_CloseButtonKeyboardAccelerators{ nullptr };
		winrt::event_token m_Closing;
		winrt::event_token m_Closed;
		winrt::event_token m_Activated;
		winrt::event_token m_ImageOpened;

		winrt::event_token m_ActualThemeChanged;

		WinUI3Package::WinUIAsyncEventArgs AsyncEventArgs;
		winrt::Windows::Foundation::Deferral Deferral{ nullptr };
		//TypedEventHandler<ContentDialogWindow, EventArgs> Loaded;
		//TypedEventHandler<ContentDialogWindow, EventArgs> Opened;
		//winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ContentDialogWindow : ContentDialogWindowT<ContentDialogWindow, implementation::ContentDialogWindow>
    {
    };
}
