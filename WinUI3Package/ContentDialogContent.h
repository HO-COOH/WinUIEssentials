#pragma once

#include "ContentDialogContent.g.h"
#include <functional>

namespace winrt::WinUI3Package::implementation
{
	struct WindowedContentDialog;

	struct ContentDialogContent : ContentDialogContentT<ContentDialogContent>
	{
		friend struct WindowedContentDialog;
		ContentDialogContent();
		~ContentDialogContent();

		void OnApplyTemplate();

		Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size availableSize);

		void TitleArea(Microsoft::UI::Xaml::UIElement const& Element);
		Microsoft::UI::Xaml::UIElement TitleArea();

		void DialogSpace(Microsoft::UI::Xaml::Controls::Grid const& grid);
		Microsoft::UI::Xaml::Controls::Grid DialogSpace();

		void CommandSpace(Microsoft::UI::Xaml::Controls::Grid const& grid);
		Microsoft::UI::Xaml::Controls::Grid CommandSpace();

		winrt::event_token PrimaryButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void PrimaryButtonClick(winrt::event_token const& token);

		winrt::event_token SecondaryButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void SecondaryButtonClick(winrt::event_token const& token);

		winrt::event_token CloseButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler);
		void CloseButtonClick(winrt::event_token const& token);

		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> PrimaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> SecondaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> CloseButtonKeyboardAccelerators();

		Microsoft::UI::Xaml::Media::ImageSource HeaderImage();
		void HeaderImage(Microsoft::UI::Xaml::Media::ImageSource const& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty HeaderImageProperty();
		static Microsoft::UI::Xaml::Visibility ImageSourceToVisibility(Microsoft::UI::Xaml::Media::ImageSource const& source);

		winrt::fire_and_forget OnPrimaryButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
		winrt::fire_and_forget OnSecondaryButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
		winrt::fire_and_forget OnCloseButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
		void OnHeaderImageOpened(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

		static winrt::Microsoft::UI::Xaml::DependencyProperty TitleProperty();
		winrt::Windows::Foundation::IInspectable Title() const;
		void Title(const winrt::Windows::Foundation::IInspectable& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty TitleTemplateProperty();
		Microsoft::UI::Xaml::DataTemplate TitleTemplate() const;
		void TitleTemplate(const Microsoft::UI::Xaml::DataTemplate& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty PrimaryButtonTextProperty();
		winrt::hstring PrimaryButtonText() const;
		void PrimaryButtonText(const winrt::hstring& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty SecondaryButtonTextProperty();
		winrt::hstring SecondaryButtonText() const;
		void SecondaryButtonText(const winrt::hstring& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty CloseButtonTextProperty();
		winrt::hstring CloseButtonText() const;
		void CloseButtonText(const winrt::hstring& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty IsPrimaryButtonEnabledProperty();
		bool IsPrimaryButtonEnabled() const;
		void IsPrimaryButtonEnabled(const bool& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty IsSecondaryButtonEnabledProperty();
		bool IsSecondaryButtonEnabled() const;
		void IsSecondaryButtonEnabled(const bool& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty DefaultButtonProperty();
		Microsoft::UI::Xaml::Controls::ContentDialogButton DefaultButton() const;
		void DefaultButton(const Microsoft::UI::Xaml::Controls::ContentDialogButton& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty PrimaryButtonStyleProperty();
		Microsoft::UI::Xaml::Style PrimaryButtonStyle() const;
		void PrimaryButtonStyle(const Microsoft::UI::Xaml::Style& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty SecondaryButtonStyleProperty();
		Microsoft::UI::Xaml::Style SecondaryButtonStyle() const;
		void SecondaryButtonStyle(const Microsoft::UI::Xaml::Style& value);

		static winrt::Microsoft::UI::Xaml::DependencyProperty CloseButtonStyleProperty();
		Microsoft::UI::Xaml::Style CloseButtonStyle() const;
		void CloseButtonStyle(const Microsoft::UI::Xaml::Style& value);

	private:
		bool isCustomMeasureFinishedAfterLoaded;

		Microsoft::UI::Xaml::Controls::Button PrimaryButton{ nullptr };
		Microsoft::UI::Xaml::Controls::Button SecondaryButton{ nullptr };
		Microsoft::UI::Xaml::Controls::Button CloseButton{ nullptr };

		winrt::event<Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_PrimaryButtonClick;
		winrt::event<Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_SecondaryButtonClick;
		winrt::event<Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_CloseButtonClick;

		Microsoft::UI::Xaml::UIElement m_TitleArea{ nullptr };
		Microsoft::UI::Xaml::Controls::Grid m_DialogSpace{ nullptr };
		Microsoft::UI::Xaml::Controls::Grid m_CommandSpace{ nullptr };

		winrt::event_token m_OnUnloaded;

		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_PrimaryButtonKeyboardAccelerators = winrt::single_threaded_vector<Microsoft::UI::Xaml::Input::KeyboardAccelerator>();
		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_SecondaryButtonKeyboardAccelerators = winrt::single_threaded_vector<Microsoft::UI::Xaml::Input::KeyboardAccelerator>();
		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_CloseButtonKeyboardAccelerators = winrt::single_threaded_vector(
			std::vector{ getEscapeKey() }
		);

		bool _IsHeaderImage{};

		Microsoft::UI::Xaml::Controls::Grid m_ImageGrid{ nullptr };

		// Dependency property fields
		static winrt::Microsoft::UI::Xaml::DependencyProperty _HeaderImageProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _TitleProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _TitleTemplateProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _PrimaryButtonTextProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _SecondaryButtonTextProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _CloseButtonTextProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _IsPrimaryButtonEnabledProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _IsSecondaryButtonEnabledProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _DefaultButtonProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _PrimaryButtonStyleProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _SecondaryButtonStyleProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty _CloseButtonStyleProperty;

		std::function<void(Microsoft::UI::Xaml::Controls::ContentDialogResult)> m_closeRequestCallback;
		std::function<void()> m_imageSizeChangedCallback;

		Windows::Foundation::Size customMeasure(Windows::Foundation::Size availableSize);

		winrt::hstring determineButtonsVisibilityState();
		winrt::hstring determineDefaultButtonState();

		static void OnHeaderImageChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e);
		static void OnButtonTextChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e);
		static void OnDefaultButtonChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e);
		static winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator getEscapeKey();

	};
}

namespace winrt::WinUI3Package::factory_implementation
{
	struct ContentDialogContent : ContentDialogContentT<ContentDialogContent, implementation::ContentDialogContent>
	{
	};
}