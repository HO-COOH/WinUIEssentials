#include "pch.h"
#include "ModernDialogBoxContent.h"
#include "ModernDialogBoxContent_Resource.xaml.h"
#if __has_include("ModernDialogBoxContent.g.cpp")
#include "ModernDialogBoxContent.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>

#include "include/ScopedButtonDisabler.hpp"
#include "ContentDialogWindowButtonClickEventArgs.h"

#include "ContentDialogUtils.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_TitleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Title",
			xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L"") });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_TitleTemplateProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"TitleTemplate",
			xaml_typename<Microsoft::UI::Xaml::DataTemplate>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_PrimaryButtonTextProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"PrimaryButtonText",
			xaml_typename<winrt::hstring>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L""), onButtonTextChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_SecondaryButtonTextProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"SecondaryButtonText",
			xaml_typename<winrt::hstring>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L""), onButtonTextChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_CloseButtonTextProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CloseButtonText",
			xaml_typename<winrt::hstring>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(L""), onButtonTextChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_IsPrimaryButtonEnabledProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsPrimaryButtonEnabled",
			xaml_typename<bool>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ box_value(true), nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_IsSecondaryButtonEnabledProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsSecondaryButtonEnabled",
			xaml_typename<bool>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ box_value(true), nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_DefaultButtonProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"DefaultButton",
			xaml_typename<Microsoft::UI::Xaml::Controls::ContentDialogButton>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(Microsoft::UI::Xaml::Controls::ContentDialogButton::Close), onDefaultButtonChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_PrimaryButtonStyleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"PrimaryButtonStyle",
			xaml_typename<Microsoft::UI::Xaml::Style>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_SecondaryButtonStyleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"SecondaryButtonStyle",
			xaml_typename<Microsoft::UI::Xaml::Style>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_CloseButtonStyleProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CloseButtonStyle",
			xaml_typename<Microsoft::UI::Xaml::Style>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr });

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::_HeaderImageProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"HeaderImage",
			xaml_typename<Microsoft::UI::Xaml::Media::ImageSource>(),
			xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, onHeaderImageChangedStatic });


	ModernDialogBoxContent::ModernDialogBoxContent() 
	{
		[[maybe_unused]] static bool s_resourceLoaded = [] {
			winrt::Microsoft::UI::Xaml::Application::Current().Resources().MergedDictionaries().Append(winrt::WinUI3Package::ModernDialogBoxContent_Resource());
			return true;
		}();

		IsPrimaryButtonEnabled(true);
		IsSecondaryButtonEnabled(true);

		Loaded([this](auto&, auto&) {

			determineButtonsVisibilityState();
			determineDefaultButtonState();

			if (_IsHeaderImage) {
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"CommandSpaceExpanded", false);
			}

			});

		Unloaded([this](auto&, auto&) {
			isCustomMeasureFinishedAfterLoaded = false;
			});
	}

	void ModernDialogBoxContent::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();

		m_TitleArea = GetTemplateChild(L"TitleArea").try_as<Microsoft::UI::Xaml::UIElement>();
		m_DialogSpace = GetTemplateChild(L"DialogSpace").try_as<Microsoft::UI::Xaml::Controls::Grid>();
		m_CommandSpace = GetTemplateChild(L"CommandSpace").try_as<Microsoft::UI::Xaml::Controls::Grid>();

		PrimaryButton = GetTemplateChild(L"PrimaryButton").try_as<Microsoft::UI::Xaml::Controls::Button>();
		SecondaryButton = GetTemplateChild(L"SecondaryButton").try_as<Microsoft::UI::Xaml::Controls::Button>();
		CloseButton = GetTemplateChild(L"CloseButton").try_as<Microsoft::UI::Xaml::Controls::Button>();

		m_ImageGrid = GetTemplateChild(L"ImageGrid").try_as<Microsoft::UI::Xaml::Controls::Grid>();

		if (_IsHeaderImage) {
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"CommandSpaceExpanded", false);
		}

		constexpr auto addKeyboardAccelerator = [](auto const& source, auto const& target)
			{
				for (auto const& key : source)
					target.Append(key);
			};

		addKeyboardAccelerator(PrimaryButtonKeyboardAccelerators(), PrimaryButton.KeyboardAccelerators());
		addKeyboardAccelerator(SecondaryButtonKeyboardAccelerators(), SecondaryButton.KeyboardAccelerators());
		addKeyboardAccelerator(CloseButtonKeyboardAccelerators(), CloseButton.KeyboardAccelerators());
	}

	Windows::Foundation::Size ModernDialogBoxContent::MeasureOverride(Windows::Foundation::Size availableSize)
	{

		if (isCustomMeasureFinishedAfterLoaded || (IsLoaded()))
			return base_type::MeasureOverride(customMeasure(availableSize));

		isCustomMeasureFinishedAfterLoaded = IsLoaded();
		return customMeasure(availableSize);

	}

	Windows::Foundation::Size ModernDialogBoxContent::customMeasure(Windows::Foundation::Size availableSize)
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

		Microsoft::UI::Xaml::Thickness commandSpacePadding = m_CommandSpace.Padding();
		double buttonSpacing = countButtons > 1
			? winrt::unbox_value<Microsoft::UI::Xaml::GridLength>(Microsoft::UI::Xaml::Application::Current().Resources().Lookup(box_value(L"ContentDialogButtonSpacing"))).Value
			: 0.0;
		double commandSpaceExpectedWidth = commandSpacePadding.Left + commandSpacePadding.Right
			+ countButtons * buttonLongestWidth
			+ (countButtons - 1) * buttonSpacing;

		double imageWidth = 0.0;
		if (m_ImageGrid && m_ImageGrid.Visibility() == Microsoft::UI::Xaml::Visibility::Visible && m_ImageGrid.Width() > 0)
		{
			imageWidth = m_ImageGrid.Width();
		}

		double minWidth = std::max<double>(commandSpaceExpectedWidth, imageWidth);

		double maxWidth = std::max<double>({
			unbox_value<double>(Microsoft::UI::Xaml::Application::Current().Resources().Lookup(box_value(L"ContentDialogMaxWidth"))),
			imageWidth
			});

		if (availableSize.Width > (float)maxWidth)
		{
			availableSize.Width = (float)maxWidth;
		}

		Windows::Foundation::Size desiredSize = base_type::MeasureOverride(availableSize);

		if (desiredSize.Width < (float)minWidth)
		{
			desiredSize.Width = (float)minWidth;
		}

		return desiredSize;
	}

	winrt::hstring ModernDialogBoxContent::determineButtonsVisibilityState() {

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

	winrt::hstring ModernDialogBoxContent::determineDefaultButtonState() {

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

	winrt::event_token ModernDialogBoxContent::PrimaryButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_PrimaryButtonClick.add(handler);
	}
	void ModernDialogBoxContent::PrimaryButtonClick(winrt::event_token const& token)
	{
		m_PrimaryButtonClick.remove(token);
	}

	winrt::event_token ModernDialogBoxContent::SecondaryButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_SecondaryButtonClick.add(handler);
	}
	void ModernDialogBoxContent::SecondaryButtonClick(winrt::event_token const& token)
	{
		m_SecondaryButtonClick.remove(token);
	}

	winrt::event_token ModernDialogBoxContent::CloseButtonClick(winrt::Windows::Foundation::EventHandler<WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_CloseButtonClick.add(handler);
	}
	void ModernDialogBoxContent::CloseButtonClick(winrt::event_token const& token)
	{
		m_CloseButtonClick.remove(token);
	}


	winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> ModernDialogBoxContent::PrimaryButtonKeyboardAccelerators()
	{
		return m_PrimaryButtonKeyboardAccelerators;
	}


	winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> ModernDialogBoxContent::SecondaryButtonKeyboardAccelerators()
	{
		return m_SecondaryButtonKeyboardAccelerators;
	}


	winrt::Windows::Foundation::Collections::IVector<Microsoft::UI::Xaml::Input::KeyboardAccelerator> ModernDialogBoxContent::CloseButtonKeyboardAccelerators()
	{
		return m_CloseButtonKeyboardAccelerators;
	}

	void ModernDialogBoxContent::onButtonTextChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&)
	{
		auto self = get_self<ModernDialogBoxContent>(sender.as<winrt::WinUI3Package::ModernDialogBoxContent>());

		if (self->IsLoaded())
		{
			self->determineButtonsVisibilityState();
			self->isCustomMeasureFinishedAfterLoaded = false;
		}
	}

	void ModernDialogBoxContent::onDefaultButtonChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&)
	{
		auto self = get_self<ModernDialogBoxContent>(sender.as<winrt::WinUI3Package::ModernDialogBoxContent>());

		if (self->IsLoaded())
		{
			self->determineDefaultButtonState();
		}
	}

	winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator ModernDialogBoxContent::getEscapeKey()
	{
		winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator escape;
		escape.Key(winrt::Windows::System::VirtualKey::Escape);
		return escape;
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::HeaderImageProperty()
	{
		return _HeaderImageProperty;
	}

	Microsoft::UI::Xaml::Media::ImageSource ModernDialogBoxContent::HeaderImage()
	{
		return GetValue(_HeaderImageProperty).try_as<Microsoft::UI::Xaml::Media::ImageSource>();
	}

	void ModernDialogBoxContent::HeaderImage(Microsoft::UI::Xaml::Media::ImageSource const& value)
	{
		SetValue(_HeaderImageProperty, value);
	}

	void ModernDialogBoxContent::onHeaderImageChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&)
	{
		auto self = get_self<ModernDialogBoxContent>(sender.as<winrt::WinUI3Package::ModernDialogBoxContent>());
		self->_IsHeaderImage = (self->HeaderImage() != nullptr);
		if (self->_IsHeaderImage && self->IsLoaded())
		{
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*self, L"CommandSpaceExpanded", false);
		}
	}

	Microsoft::UI::Xaml::Visibility ModernDialogBoxContent::ImageSourceToVisibility(Microsoft::UI::Xaml::Media::ImageSource const& source)
	{
		return source ? Microsoft::UI::Xaml::Visibility::Visible : Microsoft::UI::Xaml::Visibility::Collapsed;
	}

	void ModernDialogBoxContent::OnHeaderImageOpened(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
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

	winrt::fire_and_forget ModernDialogBoxContent::OnPrimaryButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		ScopedButtonDisabler disabler{ sender };

		auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

		m_PrimaryButtonClick(*this, ContentDialogArgs);

		co_await ContentDialogArgs.wait_for_deferrals();

		if (!ContentDialogArgs.Cancel() && m_closeRequestCallback)
			m_closeRequestCallback(Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary);
	}

	winrt::fire_and_forget ModernDialogBoxContent::OnSecondaryButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		ScopedButtonDisabler disabler{ sender };

		auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

		m_SecondaryButtonClick(*this, ContentDialogArgs);

		co_await ContentDialogArgs.wait_for_deferrals();

		if (!ContentDialogArgs.Cancel() && m_closeRequestCallback)
			m_closeRequestCallback(Microsoft::UI::Xaml::Controls::ContentDialogResult::Secondary);
	}

	winrt::fire_and_forget ModernDialogBoxContent::OnCloseButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		ScopedButtonDisabler disabler{ sender };

		auto ContentDialogArgs = WinUI3Package::ContentDialogWindowButtonClickEventArgs();
		m_CloseButtonClick(*this, ContentDialogArgs);

		co_await ContentDialogArgs.wait_for_deferrals();

		if (!ContentDialogArgs.Cancel() && m_closeRequestCallback)
			m_closeRequestCallback(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::TitleProperty()
	{
		return _TitleProperty;
	}

	winrt::Windows::Foundation::IInspectable ModernDialogBoxContent::Title() const
	{
		return winrt::unbox_value<winrt::Windows::Foundation::IInspectable>(GetValue(_TitleProperty));
	}

	void ModernDialogBoxContent::Title(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(_TitleProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::TitleTemplateProperty()
	{
		return _TitleTemplateProperty;
	}

	Microsoft::UI::Xaml::DataTemplate ModernDialogBoxContent::TitleTemplate() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::DataTemplate>(GetValue(_TitleTemplateProperty));
	}

	void ModernDialogBoxContent::TitleTemplate(Microsoft::UI::Xaml::DataTemplate const& value)
	{
		SetValue(_TitleTemplateProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::PrimaryButtonTextProperty()
	{
		return _PrimaryButtonTextProperty;
	}

	winrt::hstring ModernDialogBoxContent::PrimaryButtonText() const
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(_PrimaryButtonTextProperty));
	}

	void ModernDialogBoxContent::PrimaryButtonText(winrt::hstring const& value)
	{
		SetValue(_PrimaryButtonTextProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::SecondaryButtonTextProperty()
	{
		return _SecondaryButtonTextProperty;
	}

	winrt::hstring ModernDialogBoxContent::SecondaryButtonText() const
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(_SecondaryButtonTextProperty));
	}

	void ModernDialogBoxContent::SecondaryButtonText(winrt::hstring const& value)
	{
		SetValue(_SecondaryButtonTextProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::CloseButtonTextProperty()
	{
		return _CloseButtonTextProperty;
	}

	winrt::hstring ModernDialogBoxContent::CloseButtonText() const
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(_CloseButtonTextProperty));
	}

	void ModernDialogBoxContent::CloseButtonText(winrt::hstring const& value)
	{
		SetValue(_CloseButtonTextProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::IsPrimaryButtonEnabledProperty()
	{
		return _IsPrimaryButtonEnabledProperty;
	}

	bool ModernDialogBoxContent::IsPrimaryButtonEnabled() const
	{
		return winrt::unbox_value<bool>(GetValue(_IsPrimaryButtonEnabledProperty));
	}

	void ModernDialogBoxContent::IsPrimaryButtonEnabled(bool value)
	{
		SetValue(_IsPrimaryButtonEnabledProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::IsSecondaryButtonEnabledProperty()
	{
		return _IsSecondaryButtonEnabledProperty;
	}

	bool ModernDialogBoxContent::IsSecondaryButtonEnabled() const
	{
		return winrt::unbox_value<bool>(GetValue(_IsSecondaryButtonEnabledProperty));
	}

	void ModernDialogBoxContent::IsSecondaryButtonEnabled(bool value)
	{
		SetValue(_IsSecondaryButtonEnabledProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::DefaultButtonProperty()
	{
		return _DefaultButtonProperty;
	}

	Microsoft::UI::Xaml::Controls::ContentDialogButton ModernDialogBoxContent::DefaultButton() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::Controls::ContentDialogButton>(GetValue(_DefaultButtonProperty));
	}

	void ModernDialogBoxContent::DefaultButton(Microsoft::UI::Xaml::Controls::ContentDialogButton value)
	{
		SetValue(_DefaultButtonProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::PrimaryButtonStyleProperty()
	{
		return _PrimaryButtonStyleProperty;
	}

	Microsoft::UI::Xaml::Style ModernDialogBoxContent::PrimaryButtonStyle() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_PrimaryButtonStyleProperty));
	}

	void ModernDialogBoxContent::PrimaryButtonStyle(Microsoft::UI::Xaml::Style const& value)
	{
		SetValue(_PrimaryButtonStyleProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::SecondaryButtonStyleProperty()
	{
		return _SecondaryButtonStyleProperty;
	}

	Microsoft::UI::Xaml::Style ModernDialogBoxContent::SecondaryButtonStyle() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_SecondaryButtonStyleProperty));
	}

	void ModernDialogBoxContent::SecondaryButtonStyle(Microsoft::UI::Xaml::Style const& value)
	{
		SetValue(_SecondaryButtonStyleProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ModernDialogBoxContent::CloseButtonStyleProperty()
	{
		return _CloseButtonStyleProperty;
	}

	Microsoft::UI::Xaml::Style ModernDialogBoxContent::CloseButtonStyle() const
	{
		return winrt::unbox_value<Microsoft::UI::Xaml::Style>(GetValue(_CloseButtonStyleProperty));
	}

	void ModernDialogBoxContent::CloseButtonStyle(Microsoft::UI::Xaml::Style const& value)
	{
		SetValue(_CloseButtonStyleProperty, winrt::box_value(value));
	}
}
