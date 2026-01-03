#include "pch.h"
#include "ContentDialogContent.h"
#if __has_include("ContentDialogContent.g.cpp")
#include "ContentDialogContent.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Input.h>

#include "include/ScopedButtonDisabler.hpp"
#include "ContentDialogWindowButtonClickEventArgs.h"

#include "ContentDialogUtils.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_TitleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Title",
			xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L"") });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_TitleTemplateProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"TitleTemplate",
			xaml_typename<Microsoft::UI::Xaml::DataTemplate>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_PrimaryButtonTextProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"PrimaryButtonText",
			xaml_typename<winrt::hstring>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L""), OnButtonTextChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_SecondaryButtonTextProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"SecondaryButtonText",
			xaml_typename<winrt::hstring>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L""), OnButtonTextChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_CloseButtonTextProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CloseButtonText",
			xaml_typename<winrt::hstring>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L""), OnButtonTextChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_IsPrimaryButtonEnabledProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsPrimaryButtonEnabled",
			xaml_typename<bool>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ box_value(true), nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_IsSecondaryButtonEnabledProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsSecondaryButtonEnabled",
			xaml_typename<bool>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ box_value(true), nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_DefaultButtonProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"DefaultButton",
			xaml_typename<Microsoft::UI::Xaml::Controls::ContentDialogButton>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(Microsoft::UI::Xaml::Controls::ContentDialogButton::Close), OnDefaultButtonChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_PrimaryButtonStyleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"PrimaryButtonStyle",
			xaml_typename<Microsoft::UI::Xaml::Style>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_SecondaryButtonStyleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"SecondaryButtonStyle",
			xaml_typename<Microsoft::UI::Xaml::Style>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_CloseButtonStyleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CloseButtonStyle",
			xaml_typename<Microsoft::UI::Xaml::Style>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });
	

	ContentDialogContent::ContentDialogContent() {

		DefaultStyleKey(box_value(winrt::xaml_typename<winrt::WinUI3Package::ContentDialogContent>()));

		isCustomMeasureFinishedAfterLoaded = false;

		PrimaryButtonStyle(ContentDialogUtils::DefaultButtonStyle());
		SecondaryButtonStyle(ContentDialogUtils::DefaultButtonStyle());
		CloseButtonStyle(ContentDialogUtils::DefaultButtonStyle());

		IsPrimaryButtonEnabled(true);
		IsSecondaryButtonEnabled(true);

		Loaded([this](auto&, auto&) {

			buttonsVisibilityState = DetermineButtonsVisibilityState();
			defaultButtonState = DetermineDefaultButtonState();

			if (IsHeaderImage()) {
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"CommandSpaceExpanded", false);
			}

		});

		m_OnUnloaded = Unloaded([this](auto&, auto&) {


			isCustomMeasureFinishedAfterLoaded = false;

		});

		RightTapped({ this,&ContentDialogContent::m_ContentRightTapped });


		m_PrimaryButtonKeyboardAccelerators = (winrt::single_threaded_vector<Microsoft::UI::Xaml::Input::KeyboardAccelerator>());
		m_SecondaryButtonKeyboardAccelerators = (winrt::single_threaded_vector<Microsoft::UI::Xaml::Input::KeyboardAccelerator>());
		m_CloseButtonKeyboardAccelerators = (winrt::single_threaded_vector<Microsoft::UI::Xaml::Input::KeyboardAccelerator>());

		//VerticalAlignment(Microsoft::UI::Xaml::VerticalAlignment::Center);
		//HorizontalAlignment(Microsoft::UI::Xaml::HorizontalAlignment::Center);

		//m_CommandSpace = { nullptr };
		//PrimaryButton = { nullptr };
		//SecondaryButton = { nullptr };
		//CloseButton = { nullptr };
		//m_TitleArea = {nullptr};

	}

	ContentDialogContent::~ContentDialogContent() {

		Unloaded(m_OnUnloaded);

		PrimaryButton.Click(m_OnPrimaryButtonClick);
		SecondaryButton.Click(m_OnSecondaryButtonClick);
		CloseButton.Click(m_OnCloseButtonClick);
	}

	void ContentDialogContent::OnApplyTemplate()
	{
		Super::OnApplyTemplate();

		TitleArea(GetTemplateChild(L"TitleArea").try_as<Microsoft::UI::Xaml::UIElement>());
		DialogSpace(GetTemplateChild(L"DialogSpace").try_as<Microsoft::UI::Xaml::Controls::Grid>());
		CommandSpace(GetTemplateChild(L"CommandSpace").try_as<Microsoft::UI::Xaml::Controls::Grid>());

		PrimaryButton = GetTemplateChild(L"PrimaryButton").try_as<Microsoft::UI::Xaml::Controls::Button>();
		SecondaryButton = GetTemplateChild(L"SecondaryButton").try_as<Microsoft::UI::Xaml::Controls::Button>();
		CloseButton = GetTemplateChild(L"CloseButton").try_as<Microsoft::UI::Xaml::Controls::Button>();

		if (IsHeaderImage()) {
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"CommandSpaceExpanded", false);
		}

		m_OnPrimaryButtonClick = PrimaryButton.Click([&](winrt::Windows::Foundation::IInspectable const& sender, auto&)->winrt::Windows::Foundation::IAsyncAction {

			ScopedButtonDisabler disabler{ sender, true };

			auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

			m_PrimaryButtonClick(*this, ContentDialogArgs);

			co_await ContentDialogArgs.wait_for_deferrals();

		});

		m_OnSecondaryButtonClick = SecondaryButton.Click([&](auto const& sender, auto&)->winrt::Windows::Foundation::IAsyncAction {

			ScopedButtonDisabler disabler{ sender, true };

			auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

			m_SecondaryButtonClick(*this, ContentDialogArgs);

			co_await ContentDialogArgs.wait_for_deferrals();
		});

		m_OnCloseButtonClick = CloseButton.Click([&](auto const& sender, auto&)->winrt::Windows::Foundation::IAsyncAction {

			ScopedButtonDisabler disabler{ sender, true };
			auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();
			m_CloseButtonClick(*this, ContentDialogArgs);

			co_await ContentDialogArgs.wait_for_deferrals();
		});

		for (const auto& keyboardAccelerator : PrimaryButtonKeyboardAccelerators()) {

			PrimaryButton.KeyboardAccelerators().Append(keyboardAccelerator);
		}

		for (const auto& keyboardAccelerator : SecondaryButtonKeyboardAccelerators()) {

			SecondaryButton.KeyboardAccelerators().Append(keyboardAccelerator);
		}

		for (const auto& keyboardAccelerator : CloseButtonKeyboardAccelerators()) {

			CloseButton.KeyboardAccelerators().Append(keyboardAccelerator);
		}

		//Microsoft::UI::Xaml::Controls::Image Image = GetTemplateChild(L"ContentImage").try_as<Microsoft::UI::Xaml::Controls::Image>();

		//Image.ImageOpened([this](IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
		//{
		//	auto image = sender.as<Microsoft::UI::Xaml::Controls::Image>();

		//	if (image)
		//	{
		//		// 获取图片源并转换为BitmapImage
		//		auto bitmapImage = image.Source().as<Microsoft::UI::Xaml::Media::Imaging::BitmapImage>();
		//		if (bitmapImage)
		//		{
		//			// 获取图片实际宽高（像素）
		//			double width = bitmapImage.PixelWidth();
		//			double height = bitmapImage.PixelHeight();

		//			// 输出尺寸信息
		//			//std::wcout << L"图片尺寸: " << width << L" x " << height << std::endl;

		//			// 设置父容器Grid的尺寸为图片尺寸
		//			if (auto parentGrid = image.Parent().as<Microsoft::UI::Xaml::Controls::Grid>())
		//			{
		//				parentGrid.Width(width);
		//				parentGrid.Height(height);
		//			}
		//		}
		//	}
		//});


		//isCustomMeasureFinishedAfterLoaded = true;
		//winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"DialogShowingWithoutSmokeLayer", false);
		//DetermineButtonsVisibilityState();
		//DetermineDefaultButtonStates();
		//DetermineWidthLimit();

		//buttonsVisibilityState = DetermineButtonsVisibilityState();
		//defaultButtonState = DetermineDefaultButtonState();
		//isCustomMeasureFinishedAfterLoaded = IsLoaded();
	}

	Windows::Foundation::Size ContentDialogContent::MeasureOverride(Windows::Foundation::Size availableSize)
	{

		if (isCustomMeasureFinishedAfterLoaded || (IsLoaded()))
			return base_type::MeasureOverride(CustomMeasure(availableSize));

		isCustomMeasureFinishedAfterLoaded = IsLoaded();
		return CustomMeasure(availableSize);

	}

	Windows::Foundation::Size ContentDialogContent::CustomMeasure(Windows::Foundation::Size availableSize)
	{
		int countButtons = 0;
		double buttonLongestWidth = 0.0;
		double buttonMaxWidth = unbox_value<double>(Microsoft::UI::Xaml::Application::Current().Resources().Lookup(box_value(L"ContentDialogButtonMaxWidth")));

		if (PrimaryButton.Visibility() == Microsoft::UI::Xaml::Visibility::Visible)
		{
			PrimaryButton.Measure(availableSize);
			buttonLongestWidth = std::min<double>(std::max<double>(buttonLongestWidth, PrimaryButton.DesiredSize().Width), buttonMaxWidth);
			countButtons++;
		}

		if (SecondaryButton.Visibility() == Microsoft::UI::Xaml::Visibility::Visible)
		{
			SecondaryButton.Measure(availableSize);
			buttonLongestWidth = std::min<double>(std::max<double>(buttonLongestWidth, SecondaryButton.DesiredSize().Width), buttonMaxWidth);
			countButtons++;
		}

		if (CloseButton.Visibility() == Microsoft::UI::Xaml::Visibility::Visible)
		{
			CloseButton.Measure(availableSize);
			buttonLongestWidth = std::min<double>(std::max<double>(buttonLongestWidth, CloseButton.DesiredSize().Width), buttonMaxWidth);
			countButtons++;
		}

		// 假设 CommandSpace 是一个具有 Padding 属性的元素
		Microsoft::UI::Xaml::Thickness commandSpacePadding = CommandSpace().Padding();
		double commandSpaceExpectedWidth = commandSpacePadding.Left + commandSpacePadding.Right
			+ countButtons * buttonLongestWidth
			+ (countButtons - 1) * winrt::unbox_value<Microsoft::UI::Xaml::GridLength>(Microsoft::UI::Xaml::Application::Current().Resources().Lookup(box_value(L"ContentDialogButtonSpacing"))).Value;

		double minWidth = std::max<double>(
			unbox_value<double>(Microsoft::UI::Xaml::Application::Current().Resources().Lookup(box_value(L"ContentDialogMinWidth"))),
			commandSpaceExpectedWidth
		);

		double maxWidth = std::max<double>(
			unbox_value<double>(Microsoft::UI::Xaml::Application::Current().Resources().Lookup(box_value(L"ContentDialogMaxWidth"))),
			commandSpaceExpectedWidth
		);

		if (availableSize.Width > (float)maxWidth)
		{
			availableSize.Width = (float)maxWidth;
		}

		Windows::Foundation::Size desiredSize = base_type::MeasureOverride(availableSize);

		if (desiredSize.Width < minWidth)
		{
			desiredSize.Width = (float)minWidth;
		}

		return desiredSize;
	}

	winrt::hstring ContentDialogContent::DetermineButtonsVisibilityState() {

		if (!PrimaryButtonText().empty() && !SecondaryButtonText().empty() && !CloseButtonText().empty())
		{
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"AllVisible", false);

			//IsPrimaryButtonEnabled(true);
			//IsSecondaryButtonEnabled(true);

			return L"AllVisible";
		}
		else if (!PrimaryButtonText().empty())
		{

			//IsPrimaryButtonEnabled(true);

			if (!SecondaryButtonText().empty())
			{
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"PrimaryAndSecondaryVisible", false);
				IsSecondaryButtonEnabled(true);
				return L"PrimaryAndSecondaryVisible";
			}
			else if (!CloseButtonText().empty())
			{
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"PrimaryAndCloseVisible", false);
				IsSecondaryButtonEnabled(false);
				return L"PrimaryAndCloseVisible";
			}
			else
			{
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"PrimaryVisible", false);
				IsSecondaryButtonEnabled(false);
				return L"PrimaryVisible";
			}

		}
		else if (!SecondaryButtonText().empty())
		{
			//IsSecondaryButtonEnabled(true);

			if (!CloseButtonText().empty())
			{
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"SecondaryAndCloseVisible", false);
				return L"SecondaryAndCloseVisible";
			}
			else
			{
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"SecondaryVisible", false);
				return L"SecondaryAndCloseVisible";
			}

		}
		else if (!CloseButtonText().empty())
		{
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"CloseVisible", false);
			return L"CloseVisible";
		}
		else
		{
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"NoneVisible", false);
			IsPrimaryButtonEnabled(false);
			IsSecondaryButtonEnabled(false);
			return L"NoneVisible";
		}
	}

	winrt::hstring ContentDialogContent::DetermineDefaultButtonState() {

		switch (DefaultButton())
		{
			case Microsoft::UI::Xaml::Controls::ContentDialogButton::Primary: {

				Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"PrimaryAsDefaultButton", false);
				winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator keyboardAccelerator = {};
				keyboardAccelerator.Key(winrt::Windows::System::VirtualKey::Enter);
				PrimaryButton.KeyboardAccelerators().Append(keyboardAccelerator);

				PrimaryButton.Focus(Microsoft::UI::Xaml::FocusState::Programmatic);
				return L"PrimaryAsDefaultButton";

			}

			case Microsoft::UI::Xaml::Controls::ContentDialogButton::Secondary: {

				Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"SecondaryAsDefaultButton", false);

				winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator keyboardAccelerator = {};
				keyboardAccelerator.Key(winrt::Windows::System::VirtualKey::Enter);
				SecondaryButton.KeyboardAccelerators().Append(keyboardAccelerator);

				SecondaryButton.Focus(Microsoft::UI::Xaml::FocusState::Programmatic);
				return L"SecondaryAsDefaultButton";

			}
			case Microsoft::UI::Xaml::Controls::ContentDialogButton::Close: {

				Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"CloseAsDefaultButton", false);

				winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator keyboardAccelerator = {};
				keyboardAccelerator.Key(winrt::Windows::System::VirtualKey::Enter);
				CloseButton.KeyboardAccelerators().Append(keyboardAccelerator);
				CloseButton.Focus(Microsoft::UI::Xaml::FocusState::Programmatic);
				return L"CloseAsDefaultButton";

			}
			case Microsoft::UI::Xaml::Controls::ContentDialogButton::None: {
				Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"NoDefaultButton", false);
				return L"NoDefaultButton";
			}

			default: {
				Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"NoDefaultButton", false);
				return L"NoDefaultButton";
			}

		}
	}

	void ContentDialogContent::AfterGotFocus()
	{
		if (IsHeaderImage()) return;

		winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, defaultButtonState, false);
	}

	void ContentDialogContent::AfterLostFocus()
	{

		if (IsHeaderImage()) return;

		Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"NoDefaultButton", false);
	}

	void ContentDialogContent::TitleArea(Microsoft::UI::Xaml::UIElement const& Element)
	{
		m_TitleArea = Element;
	}
	winrt::Microsoft::UI::Xaml::UIElement ContentDialogContent::TitleArea()
	{
		return m_TitleArea;
	}

	void ContentDialogContent::DialogSpace(Microsoft::UI::Xaml::Controls::Grid const& grid)
	{
		m_DialogSpace = grid;
	}
	winrt::Microsoft::UI::Xaml::Controls::Grid ContentDialogContent::DialogSpace()
	{
		return m_DialogSpace;
	}

	void ContentDialogContent::CommandSpace(Microsoft::UI::Xaml::Controls::Grid const& grid)
	{
		m_CommandSpace = grid;
	}
	winrt::Microsoft::UI::Xaml::Controls::Grid ContentDialogContent::CommandSpace()
	{
		return m_CommandSpace;
	}

	winrt::event_token ContentDialogContent::PrimaryButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_PrimaryButtonClick.add(handler);
	}
	void ContentDialogContent::PrimaryButtonClick(winrt::event_token const& token)
	{
		m_PrimaryButtonClick.remove(token);
	}

	winrt::event_token ContentDialogContent::SecondaryButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_SecondaryButtonClick.add(handler);
	}
	void ContentDialogContent::SecondaryButtonClick(winrt::event_token const& token)
	{
		m_SecondaryButtonClick.remove(token);
	}

	winrt::event_token ContentDialogContent::CloseButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_CloseButtonClick.add(handler);
	}
	void ContentDialogContent::CloseButtonClick(winrt::event_token const& token)
	{
		m_CloseButtonClick.remove(token);
	}


	winrt::event_token ContentDialogContent::ContentRightTapped(Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs> const& handler)
	{
		return m_ContentRightTapped.add(handler);
	}

	void ContentDialogContent::ContentRightTapped(winrt::event_token const& token)
	{
		m_ContentRightTapped.remove(token);
	}


	winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> ContentDialogContent::PrimaryButtonKeyboardAccelerators()
	{
		return m_PrimaryButtonKeyboardAccelerators;
	}


	winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> ContentDialogContent::SecondaryButtonKeyboardAccelerators()
	{
		return m_SecondaryButtonKeyboardAccelerators;
	}


	winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> ContentDialogContent::CloseButtonKeyboardAccelerators()
	{
		return m_CloseButtonKeyboardAccelerators;
	}

}
