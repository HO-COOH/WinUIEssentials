#pragma once

#include "ContentDialogContent.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct ContentDialogContent : ContentDialogContentT<ContentDialogContent>
	{
		using Super = ContentDialogContentT<ContentDialogContent>;

		ContentDialogContent();
		~ContentDialogContent();

		void OnApplyTemplate();

		Windows::Foundation::Size MeasureOverride(Windows::Foundation::Size availableSize);

		Windows::Foundation::Size CustomMeasure(Windows::Foundation::Size availableSize);

		void AfterGotFocus();

		void AfterLostFocus();

		winrt::hstring DetermineButtonsVisibilityState();
		winrt::hstring DetermineDefaultButtonState();

		void DetermineWidthLimit();
		void RemoveSizeLimit();

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

		winrt::event_token ContentRightTapped(Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs> const& handler);
		void ContentRightTapped(winrt::event_token const& token);

		static void OnButtonTextChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
		{
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);

			auto self = get_self<ContentDialogContent>(sender.as<winrt::WinUI3Package::ContentDialogContent>());

			if (self->IsLoaded())
			{
				self->buttonsVisibilityState = self->DetermineButtonsVisibilityState();
				self->isCustomMeasureFinishedAfterLoaded = false;
			}
		}

		static void OnDefaultButtonChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
		{
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);

			auto self = get_self<ContentDialogContent>(sender.as<winrt::WinUI3Package::ContentDialogContent>());

			if (self->IsLoaded())
			{
				self->defaultButtonState = self->DetermineDefaultButtonState();
			}
		}

		static winrt::Windows::UI::Xaml::Style DefaultButtonStyle()
		{
			static auto style = Microsoft::UI::Xaml::Application::Current().Resources().TryLookup(
				winrt::box_value(L"DefaultButtonStyle")
			).as<Windows::UI::Xaml::Style>();

			return style;
		}

		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> PrimaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> SecondaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> CloseButtonKeyboardAccelerators();

		// IsHeaderImage property
		bool IsHeaderImage() const
		{
			return _IsHeaderImage;
		}
		void IsHeaderImage(const bool& value)
		{
			if (_IsHeaderImage != value)
			{
				_IsHeaderImage = value;
			}
		}

		// Title dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty TitleProperty()
		{
			return _TitleProperty;
		}
		winrt::Windows::Foundation::IInspectable Title() const
		{
			return winrt::unbox_value<winrt::Windows::Foundation::IInspectable>(GetValue(_TitleProperty));
		}
		void Title(const winrt::Windows::Foundation::IInspectable& value)
		{
			SetValue(_TitleProperty, winrt::box_value(value));
		}

		// TitleTemplate dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty TitleTemplateProperty()
		{
			return _TitleTemplateProperty;
		}
		Microsoft::UI::Xaml::DataTemplate TitleTemplate() const
		{
			return winrt::unbox_value<Microsoft::UI::Xaml::DataTemplate>(GetValue(_TitleTemplateProperty));
		}
		void TitleTemplate(const Microsoft::UI::Xaml::DataTemplate& value)
		{
			SetValue(_TitleTemplateProperty, winrt::box_value(value));
		}

		// PrimaryButtonText dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty PrimaryButtonTextProperty()
		{
			return _PrimaryButtonTextProperty;
		}
		winrt::hstring PrimaryButtonText() const
		{
			return winrt::unbox_value<winrt::hstring>(GetValue(_PrimaryButtonTextProperty));
		}
		void PrimaryButtonText(const winrt::hstring& value)
		{
			SetValue(_PrimaryButtonTextProperty, winrt::box_value(value));
		}

		// SecondaryButtonText dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty SecondaryButtonTextProperty()
		{
			return _SecondaryButtonTextProperty;
		}
		winrt::hstring SecondaryButtonText() const
		{
			return winrt::unbox_value<winrt::hstring>(GetValue(_SecondaryButtonTextProperty));
		}
		void SecondaryButtonText(const winrt::hstring& value)
		{
			SetValue(_SecondaryButtonTextProperty, winrt::box_value(value));
		}

		// CloseButtonText dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty CloseButtonTextProperty()
		{
			return _CloseButtonTextProperty;
		}
		winrt::hstring CloseButtonText() const
		{
			return winrt::unbox_value<winrt::hstring>(GetValue(_CloseButtonTextProperty));
		}
		void CloseButtonText(const winrt::hstring& value)
		{
			SetValue(_CloseButtonTextProperty, winrt::box_value(value));
		}

		// IsPrimaryButtonEnabled dependency property
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

		// IsSecondaryButtonEnabled dependency property
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

		// DefaultButton dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty DefaultButtonProperty()
		{
			return _DefaultButtonProperty;
		}
		Microsoft::UI::Xaml::Controls::ContentDialogButton DefaultButton() const
		{
			return winrt::unbox_value<Microsoft::UI::Xaml::Controls::ContentDialogButton>(GetValue(_DefaultButtonProperty));
		}
		void DefaultButton(const Microsoft::UI::Xaml::Controls::ContentDialogButton& value)
		{
			SetValue(_DefaultButtonProperty, winrt::box_value(value));
		}

		// PrimaryButtonStyle dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty PrimaryButtonStyleProperty()
		{
			return _PrimaryButtonStyleProperty;
		}
		Microsoft::UI::Xaml::Style PrimaryButtonStyle() const
		{
			return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_PrimaryButtonStyleProperty));
		}
		void PrimaryButtonStyle(const Microsoft::UI::Xaml::Style& value)
		{
			SetValue(_PrimaryButtonStyleProperty, winrt::box_value(value));
		}

		// SecondaryButtonStyle dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty SecondaryButtonStyleProperty()
		{
			return _SecondaryButtonStyleProperty;
		}
		Microsoft::UI::Xaml::Style SecondaryButtonStyle() const
		{
			return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_SecondaryButtonStyleProperty));
		}
		void SecondaryButtonStyle(const Microsoft::UI::Xaml::Style& value)
		{
			SetValue(_SecondaryButtonStyleProperty, winrt::box_value(value));
		}

		// CloseButtonStyle dependency property
		static winrt::Microsoft::UI::Xaml::DependencyProperty CloseButtonStyleProperty()
		{
			return _CloseButtonStyleProperty;
		}
		Microsoft::UI::Xaml::Style CloseButtonStyle() const
		{
			return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_CloseButtonStyleProperty));
		}
		void CloseButtonStyle(const Microsoft::UI::Xaml::Style& value)
		{
			SetValue(_CloseButtonStyleProperty, winrt::box_value(value));
		}

	private:
		bool isCustomMeasureFinishedAfterLoaded;

		Microsoft::UI::Xaml::Controls::Button PrimaryButton{ nullptr };
		Microsoft::UI::Xaml::Controls::Button SecondaryButton{ nullptr };
		Microsoft::UI::Xaml::Controls::Button CloseButton{ nullptr };

		winrt::event<Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_PrimaryButtonClick;
		winrt::event<Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_SecondaryButtonClick;
		winrt::event<Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs>> m_CloseButtonClick;

		winrt::event<Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs>> m_ContentRightTapped;

		Microsoft::UI::Xaml::UIElement m_TitleArea{ nullptr };
		Microsoft::UI::Xaml::Controls::Grid m_DialogSpace{ nullptr };
		Microsoft::UI::Xaml::Controls::Grid m_CommandSpace{ nullptr };

		winrt::hstring buttonsVisibilityState;
		winrt::hstring defaultButtonState;

		winrt::event_token m_OnUnloaded;

		winrt::event_token m_OnPrimaryButtonClick;
		winrt::event_token m_OnSecondaryButtonClick;
		winrt::event_token m_OnCloseButtonClick;

		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_PrimaryButtonKeyboardAccelerators{ nullptr };
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_SecondaryButtonKeyboardAccelerators{ nullptr };
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> m_CloseButtonKeyboardAccelerators{ nullptr };

		// IsHeaderImage property field
		bool _IsHeaderImage;

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
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
	struct ContentDialogContent : ContentDialogContentT<ContentDialogContent, implementation::ContentDialogContent>
	{
	};
}