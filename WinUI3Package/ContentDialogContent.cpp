#include "pch.h"
#include "ContentDialogContent.h"
#if __has_include("ContentDialogContent.g.cpp")
#include "ContentDialogContent.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>

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

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::_HeaderImageProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"HeaderImage",
			xaml_typename<Microsoft::UI::Xaml::Media::ImageSource>(),
			xaml_typename<WinUI3Package::ContentDialogContent>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, OnHeaderImageChangedStatic });
	

	ContentDialogContent::ContentDialogContent() {

		DefaultStyleKey(box_value(winrt::xaml_typename<winrt::WinUI3Package::ContentDialogContent>()));

		isCustomMeasureFinishedAfterLoaded = false;

		PrimaryButtonStyle(ContentDialogUtils::DefaultButtonStyle());
		SecondaryButtonStyle(ContentDialogUtils::DefaultButtonStyle());
		CloseButtonStyle(ContentDialogUtils::DefaultButtonStyle());

		IsPrimaryButtonEnabled(true);
		IsSecondaryButtonEnabled(true);

		Loaded([this](auto&, auto&) {

			determineButtonsVisibilityState();
			determineDefaultButtonState();

			if (_IsHeaderImage) {
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"CommandSpaceExpanded", false);
			}

		});

		m_OnUnloaded = Unloaded([this](auto&, auto&) {


			isCustomMeasureFinishedAfterLoaded = false;

		});
	}

	ContentDialogContent::~ContentDialogContent() {

		Unloaded(m_OnUnloaded);
	}

	void ContentDialogContent::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();

		TitleArea(GetTemplateChild(L"TitleArea").try_as<Microsoft::UI::Xaml::UIElement>());
		DialogSpace(GetTemplateChild(L"DialogSpace").try_as<Microsoft::UI::Xaml::Controls::Grid>());
		CommandSpace(GetTemplateChild(L"CommandSpace").try_as<Microsoft::UI::Xaml::Controls::Grid>());

		PrimaryButton = GetTemplateChild(L"PrimaryButton").try_as<Microsoft::UI::Xaml::Controls::Button>();
		SecondaryButton = GetTemplateChild(L"SecondaryButton").try_as<Microsoft::UI::Xaml::Controls::Button>();
		CloseButton = GetTemplateChild(L"CloseButton").try_as<Microsoft::UI::Xaml::Controls::Button>();

		m_ImageGrid = GetTemplateChild(L"ImageGrid").try_as<Microsoft::UI::Xaml::Controls::Grid>();

		if (_IsHeaderImage) {
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"CommandSpaceExpanded", false);
		}

		for (const auto& keyboardAccelerator : PrimaryButtonKeyboardAccelerators()) {

			PrimaryButton.KeyboardAccelerators().Append(keyboardAccelerator);
		}

		for (const auto& keyboardAccelerator : SecondaryButtonKeyboardAccelerators()) {

			SecondaryButton.KeyboardAccelerators().Append(keyboardAccelerator);
		}

		for (const auto& keyboardAccelerator : CloseButtonKeyboardAccelerators()) {

			CloseButton.KeyboardAccelerators().Append(keyboardAccelerator);
		}


	}

	Windows::Foundation::Size ContentDialogContent::MeasureOverride(Windows::Foundation::Size availableSize)
	{

		if (isCustomMeasureFinishedAfterLoaded || (IsLoaded()))
			return base_type::MeasureOverride(customMeasure(availableSize));

		isCustomMeasureFinishedAfterLoaded = IsLoaded();
		return customMeasure(availableSize);

	}

	Windows::Foundation::Size ContentDialogContent::customMeasure(Windows::Foundation::Size availableSize)
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

		double imageWidth = 0.0;
		if (m_ImageGrid && m_ImageGrid.Visibility() == Microsoft::UI::Xaml::Visibility::Visible && m_ImageGrid.Width() > 0)
		{
			imageWidth = m_ImageGrid.Width();
		}

		double minWidth = std::max<double>({
			unbox_value<double>(Microsoft::UI::Xaml::Application::Current().Resources().Lookup(box_value(L"ContentDialogMinWidth"))),
			commandSpaceExpectedWidth,
			imageWidth
		});

		double maxWidth = std::max<double>({
			unbox_value<double>(Microsoft::UI::Xaml::Application::Current().Resources().Lookup(box_value(L"ContentDialogMaxWidth"))),
			commandSpaceExpectedWidth,
			imageWidth
		});

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

	winrt::hstring ContentDialogContent::determineButtonsVisibilityState() {

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

	winrt::hstring ContentDialogContent::determineDefaultButtonState() {

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

	void ContentDialogContent::OnButtonTextChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		UNREFERENCED_PARAMETER(sender);
		UNREFERENCED_PARAMETER(e);

		auto self = get_self<ContentDialogContent>(sender.as<winrt::WinUI3Package::ContentDialogContent>());

		if (self->IsLoaded())
		{
			self->determineButtonsVisibilityState();
			self->isCustomMeasureFinishedAfterLoaded = false;
		}
	}

	void ContentDialogContent::OnDefaultButtonChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		UNREFERENCED_PARAMETER(sender);
		UNREFERENCED_PARAMETER(e);

		auto self = get_self<ContentDialogContent>(sender.as<winrt::WinUI3Package::ContentDialogContent>());

		if (self->IsLoaded())
		{
			self->determineDefaultButtonState();
		}
	}

	winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator ContentDialogContent::getEscapeKey()
	{
		winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator escape;
		escape.Key(winrt::Windows::System::VirtualKey::Escape);
		return escape;
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::HeaderImageProperty()
	{
		return _HeaderImageProperty;
	}

	Microsoft::UI::Xaml::Media::ImageSource ContentDialogContent::HeaderImage()
	{
		return GetValue(_HeaderImageProperty).try_as<Microsoft::UI::Xaml::Media::ImageSource>();
	}

	void ContentDialogContent::HeaderImage(Microsoft::UI::Xaml::Media::ImageSource const& value)
	{
		SetValue(_HeaderImageProperty, value);
	}

	void ContentDialogContent::OnHeaderImageChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		UNREFERENCED_PARAMETER(e);
		auto self = get_self<ContentDialogContent>(sender.as<winrt::WinUI3Package::ContentDialogContent>());
		self->_IsHeaderImage = (self->HeaderImage() != nullptr);
		if (self->_IsHeaderImage && self->IsLoaded())
		{
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*self, L"CommandSpaceExpanded", false);
		}
	}

	Microsoft::UI::Xaml::Visibility ContentDialogContent::ImageSourceToVisibility(Microsoft::UI::Xaml::Media::ImageSource const& source)
	{
		return source ? Microsoft::UI::Xaml::Visibility::Visible : Microsoft::UI::Xaml::Visibility::Collapsed;
	}

	void ContentDialogContent::OnHeaderImageOpened(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		auto image = sender.try_as<Microsoft::UI::Xaml::Controls::Image>();
		if (image)
		{
			auto bitmapImage = image.Source().try_as<Microsoft::UI::Xaml::Media::Imaging::BitmapImage>();
			if (bitmapImage && m_ImageGrid)
			{
				m_ImageGrid.Width(bitmapImage.PixelWidth());
				m_ImageGrid.Height(bitmapImage.PixelHeight());

				InvalidateMeasure();
				UpdateLayout();

				if (m_imageSizeChangedCallback)
					m_imageSizeChangedCallback();
			}
		}
	}

	winrt::fire_and_forget ContentDialogContent::OnPrimaryButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		ScopedButtonDisabler disabler{ sender, true };

		auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

		m_PrimaryButtonClick(*this, ContentDialogArgs);

		co_await ContentDialogArgs.wait_for_deferrals();

		if (!ContentDialogArgs.Cancel() && m_closeRequestCallback)
			m_closeRequestCallback(Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary);
	}

	winrt::fire_and_forget ContentDialogContent::OnSecondaryButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		ScopedButtonDisabler disabler{ sender, true };

		auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

		m_SecondaryButtonClick(*this, ContentDialogArgs);

		co_await ContentDialogArgs.wait_for_deferrals();

		if (!ContentDialogArgs.Cancel() && m_closeRequestCallback)
			m_closeRequestCallback(Microsoft::UI::Xaml::Controls::ContentDialogResult::Secondary);
	}

	winrt::fire_and_forget ContentDialogContent::OnCloseButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		ScopedButtonDisabler disabler{ sender, true };

		auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();
		m_CloseButtonClick(*this, ContentDialogArgs);

		co_await ContentDialogArgs.wait_for_deferrals();

		if (!ContentDialogArgs.Cancel() && m_closeRequestCallback)
			m_closeRequestCallback(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::TitleProperty()
	{
		return _TitleProperty;
	}

	winrt::Windows::Foundation::IInspectable ContentDialogContent::Title() const
	{
		return winrt::unbox_value<winrt::Windows::Foundation::IInspectable>(GetValue(_TitleProperty));
	}

	void ContentDialogContent::Title(const winrt::Windows::Foundation::IInspectable& value)
	{
		SetValue(_TitleProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::TitleTemplateProperty()
	{
		return _TitleTemplateProperty;
	}

	Microsoft::UI::Xaml::DataTemplate ContentDialogContent::TitleTemplate() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::DataTemplate>(GetValue(_TitleTemplateProperty));
	}

	void ContentDialogContent::TitleTemplate(const Microsoft::UI::Xaml::DataTemplate& value)
	{
		SetValue(_TitleTemplateProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::PrimaryButtonTextProperty()
	{
		return _PrimaryButtonTextProperty;
	}

	winrt::hstring ContentDialogContent::PrimaryButtonText() const
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(_PrimaryButtonTextProperty));
	}

	void ContentDialogContent::PrimaryButtonText(const winrt::hstring& value)
	{
		SetValue(_PrimaryButtonTextProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::SecondaryButtonTextProperty()
	{
		return _SecondaryButtonTextProperty;
	}

	winrt::hstring ContentDialogContent::SecondaryButtonText() const
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(_SecondaryButtonTextProperty));
	}

	void ContentDialogContent::SecondaryButtonText(const winrt::hstring& value)
	{
		SetValue(_SecondaryButtonTextProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::CloseButtonTextProperty()
	{
		return _CloseButtonTextProperty;
	}

	winrt::hstring ContentDialogContent::CloseButtonText() const
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(_CloseButtonTextProperty));
	}

	void ContentDialogContent::CloseButtonText(const winrt::hstring& value)
	{
		SetValue(_CloseButtonTextProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::IsPrimaryButtonEnabledProperty()
	{
		return _IsPrimaryButtonEnabledProperty;
	}

	bool ContentDialogContent::IsPrimaryButtonEnabled() const
	{
		return winrt::unbox_value<bool>(GetValue(_IsPrimaryButtonEnabledProperty));
	}

	void ContentDialogContent::IsPrimaryButtonEnabled(const bool& value)
	{
		SetValue(_IsPrimaryButtonEnabledProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::IsSecondaryButtonEnabledProperty()
	{
		return _IsSecondaryButtonEnabledProperty;
	}

	bool ContentDialogContent::IsSecondaryButtonEnabled() const
	{
		return winrt::unbox_value<bool>(GetValue(_IsSecondaryButtonEnabledProperty));
	}

	void ContentDialogContent::IsSecondaryButtonEnabled(const bool& value)
	{
		SetValue(_IsSecondaryButtonEnabledProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::DefaultButtonProperty()
	{
		return _DefaultButtonProperty;
	}

	Microsoft::UI::Xaml::Controls::ContentDialogButton ContentDialogContent::DefaultButton() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::Controls::ContentDialogButton>(GetValue(_DefaultButtonProperty));
	}

	void ContentDialogContent::DefaultButton(const Microsoft::UI::Xaml::Controls::ContentDialogButton& value)
	{
		SetValue(_DefaultButtonProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::PrimaryButtonStyleProperty()
	{
		return _PrimaryButtonStyleProperty;
	}

	Microsoft::UI::Xaml::Style ContentDialogContent::PrimaryButtonStyle() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_PrimaryButtonStyleProperty));
	}

	void ContentDialogContent::PrimaryButtonStyle(const Microsoft::UI::Xaml::Style& value)
	{
		SetValue(_PrimaryButtonStyleProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::SecondaryButtonStyleProperty()
	{
		return _SecondaryButtonStyleProperty;
	}

	Microsoft::UI::Xaml::Style ContentDialogContent::SecondaryButtonStyle() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_SecondaryButtonStyleProperty));
	}

	void ContentDialogContent::SecondaryButtonStyle(const Microsoft::UI::Xaml::Style& value)
	{
		SetValue(_SecondaryButtonStyleProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ContentDialogContent::CloseButtonStyleProperty()
	{
		return _CloseButtonStyleProperty;
	}

	Microsoft::UI::Xaml::Style ContentDialogContent::CloseButtonStyle() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_CloseButtonStyleProperty));
	}

	void ContentDialogContent::CloseButtonStyle(const Microsoft::UI::Xaml::Style& value)
	{
		SetValue(_CloseButtonStyleProperty, winrt::box_value(value));
	}

}
