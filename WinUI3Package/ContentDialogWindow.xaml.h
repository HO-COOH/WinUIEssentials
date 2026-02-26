#pragma once

#include "ContentDialogWindow.g.h"

#include <winrt/Microsoft.UI.Windowing.h>
#include "ModalWindowBase.hpp"
#include "NonMaximizableWindowWorkaround.h"
#include "WinUIAsyncEventArgs.hpp"

namespace winrt::WinUI3Package::implementation
{
	struct WindowedContentDialog;

	struct ContentDialogWindow : ContentDialogWindowT<ContentDialogWindow>, ModalWindowBase<ContentDialogWindow>
	{
		friend struct WindowedContentDialog;

		ContentDialogWindow();

		winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ShowAsync();

		void UpdateWindowSize();

		void OnContentLoaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

		void Open();

		void Hide();

		void OnClosingRequestedBySystem();

		void OnClosingRequstedByCode();

		winrt::Windows::Foundation::IAsyncAction OnPrimaryButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& e);
		winrt::Windows::Foundation::IAsyncAction OnSecondaryButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& e);
		winrt::Windows::Foundation::IAsyncAction OnCloseButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& e);

		void OnContentRightTapped(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs const& e);


		winrt::event_token ContentRightTapped(Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs> const& handler);
		void ContentRightTapped(winrt::event_token const& token);

		void DetermineTitleBarButtonForegroundColor();
		void AfterCommandSpaceButtonClick(WinUI3Package::ContentDialogWindowButtonClickEventArgs const& args);
		void SetParent(Microsoft::UI::Xaml::Window const& parent, bool center);

		winrt::event_token Loaded(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, Windows::Foundation::IInspectable> const& handler);
		void Loaded(winrt::event_token const& token);

		winrt::event_token Opened(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, Windows::Foundation::IInspectable> const& handler);
		void Opened(winrt::event_token const& token);

		void HasTitleBar(bool hasTitleBar);
		bool HasTitleBar();

		void IsResizable(bool isResizable);
		bool IsResizable();

		winrt::hstring HeaderImageUri();
		void HeaderImageUri(winrt::hstring const& Value);

		Microsoft::UI::Xaml::Media::Imaging::BitmapImage HeaderImage();
		void HeaderImage(Microsoft::UI::Xaml::Media::Imaging::BitmapImage const& Value);

		Microsoft::UI::Xaml::Controls::ContentDialogResult Result() const;
		winrt::WinUI3Package::ContentDialogContent ContentDialogContent();
	private:

		void Result(const Microsoft::UI::Xaml::Controls::ContentDialogResult& value);

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

		winrt::event_token m_Closing;
		winrt::event_token m_Closed;
		winrt::event_token m_Activated;
		winrt::event_token m_ImageOpened;

		winrt::event_token m_ActualThemeChanged;

		WinUI3Package::NonMaximizableWindowWorkaround m_windowWorkaround{ nullptr };

		winrt::com_ptr<WinUIAsyncEventArgs> AsyncEventArgs = winrt::make_self<WinUIAsyncEventArgs>();
		winrt::Windows::Foundation::Deferral Deferral{ nullptr };

	};
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ContentDialogWindow : ContentDialogWindowT<ContentDialogWindow, implementation::ContentDialogWindow>
    {
    };
}
