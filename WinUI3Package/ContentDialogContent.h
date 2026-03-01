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

		Windows::Foundation::Size CustomMeasure(Windows::Foundation::Size availableSize);

		void AfterGotFocus();

		void AfterLostFocus();

		winrt::hstring DetermineButtonsVisibilityState();
		winrt::hstring DetermineDefaultButtonState();

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

		static void OnButtonTextChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e);
		static void OnDefaultButtonChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e);

		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> PrimaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> SecondaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> CloseButtonKeyboardAccelerators();

		Microsoft::UI::Xaml::Media::ImageSource HeaderImage();
		void HeaderImage(Microsoft::UI::Xaml::Media::ImageSource const& value);

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

		winrt::hstring buttonsVisibilityState;
		winrt::hstring defaultButtonState;

		winrt::event_token m_OnUnloaded;

		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_PrimaryButtonKeyboardAccelerators{ nullptr };
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_SecondaryButtonKeyboardAccelerators{ nullptr };
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_CloseButtonKeyboardAccelerators{ nullptr };

		bool _IsHeaderImage{};

		Microsoft::UI::Xaml::Media::ImageSource m_HeaderImage{ nullptr };

		Microsoft::UI::Xaml::Controls::Grid m_ImageGrid{ nullptr };
		Microsoft::UI::Xaml::Controls::Image m_HeaderImageElement{ nullptr };
		winrt::event_token m_ImageOpened;

		// Dependency property fields
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

		void ApplyHeaderImage();
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
	struct ContentDialogContent : ContentDialogContentT<ContentDialogContent, implementation::ContentDialogContent>
	{
	};
}