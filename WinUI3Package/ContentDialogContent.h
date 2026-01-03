#pragma once

#include "ContentDialogContent.g.h"

#include "include/cppwinrt_utils.h"

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

		//void DetermineButtonsVisibilityState();
		//void DetermineDefaultButtonStates();
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

			//winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, IsEnabled() ? NormalState : DisabledState, true);

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

			//winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, IsEnabled() ? NormalState : DisabledState, true);

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
		//static void OnIsClickEnabledPropertyChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs args)
		//{
		//	UNREFERENCED_PARAMETER(sender);
		//	UNREFERENCED_PARAMETER(args);
		//	get_self<ContentDialogContent>(sender.as<winrt::WinUI3Package::ContentDialogContent>())->OnIsClickEnabledPropertyChanged(args.OldValue().as<bool>(), args.NewValue().as<bool>());

		//}

		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> PrimaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> SecondaryButtonKeyboardAccelerators();
		winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> CloseButtonKeyboardAccelerators();


		DEFINE_PROPERTY(bool, IsHeaderImage);

		DEPENDENCY_PROPERTY(winrt::Windows::Foundation::IInspectable, Title);
		DEPENDENCY_PROPERTY(Microsoft::UI::Xaml::DataTemplate, TitleTemplate);
		DEPENDENCY_PROPERTY(winrt::hstring, PrimaryButtonText);
		DEPENDENCY_PROPERTY(winrt::hstring, SecondaryButtonText);
		DEPENDENCY_PROPERTY(winrt::hstring, CloseButtonText);

		DEPENDENCY_PROPERTY(bool, IsPrimaryButtonEnabled);
		DEPENDENCY_PROPERTY(bool, IsSecondaryButtonEnabled);

		DEPENDENCY_PROPERTY(Microsoft::UI::Xaml::Controls::ContentDialogButton, DefaultButton);

		DEPENDENCY_PROPERTY(Microsoft::UI::Xaml::Style, PrimaryButtonStyle);
		DEPENDENCY_PROPERTY(Microsoft::UI::Xaml::Style, SecondaryButtonStyle);
		DEPENDENCY_PROPERTY(Microsoft::UI::Xaml::Style, CloseButtonStyle);

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

    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ContentDialogContent : ContentDialogContentT<ContentDialogContent, implementation::ContentDialogContent>
    {
    };
}
