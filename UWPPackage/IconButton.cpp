#include "pch.h"
#include "IconButton.h"
#if __has_include("IconButton.g.cpp")
#include "IconButton.g.cpp"
#endif


namespace winrt::UWPPackage::implementation
{
	winrt::Windows::UI::Xaml::DependencyProperty IconButton::m_iconProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"Icon",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	winrt::Windows::UI::Xaml::DependencyProperty IconButton::m_isExpandedProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"IsExpanded",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(false), &IconButton::isExpandedPropertyChanged }
	);


	IconButton::IconButton()
	{
		DefaultStyleKey(winrt::box_value(winrt::xaml_typename<class_type>()));

		RegisterPropertyChangedCallback(winrt::Windows::UI::Xaml::Controls::ContentControl::ContentProperty(),
			[this](auto...)
			{
				m_firstWidth.reset();
				if (m_loaded)
				{
					m_contentPresenter.Width(NAN);
				}
				if (!m_contentPresenter)
					m_contentPresenter = {};
				m_contentPresenter.Content(Content());
			});

		RegisterPropertyChangedCallback(winrt::Windows::UI::Xaml::Controls::Control::FontSizeProperty(),
			[this](auto...)
			{
				if (!m_contentPresenter)
					m_contentPresenter = {};
				if (!m_iconContent)
					m_iconContent = {};
				m_contentPresenter.FontSize(FontSize());
				m_iconContent.FontSize(FontSize());
			});
	}

	void IconButton::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();

		if (!m_container)
			m_container = winrt::Windows::UI::Xaml::Controls::Button{};
		if (!m_iconContent)
			m_iconContent = {};
		if (!m_contentPresenter)
			m_contentPresenter = {};

		auto rootButton = m_container;
		winrt::Windows::UI::Xaml::Controls::StackPanel buttonContent;
		buttonContent.Orientation(winrt::Windows::UI::Xaml::Controls::Orientation::Horizontal);
		buttonContent.Children().Append(m_iconContent);
		buttonContent.Children().Append(m_contentPresenter);

		rootButton.Content(buttonContent);

		auto rootPanel = GetTemplateChild(L"RootGrid").as<winrt::Windows::UI::Xaml::Controls::Grid>();
		rootPanel.Children().Append(rootButton);


		rootButton.PointerEntered([this](auto...) {Expand(); });
		rootButton.PointerExited([this](auto...) {Collapse(); });


		m_contentPresenter.Loaded([this](auto...) { m_loaded = true; });
		m_contentPresenter.SizeChanged([this](auto, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& args)
			{
				if (!m_widthAnimation)
				{
					m_widthAnimation = {};
					winrt::Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(m_widthAnimation, m_contentPresenter);
					winrt::Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(
						m_widthAnimation,
						L"(ContentPresenter.Width)"
					);
					m_widthAnimation.EnableDependentAnimation(true);
					m_widthAnimation.From(0.0);

					winrt::Windows::UI::Xaml::Media::Animation::ExponentialEase easing;
					easing.Exponent(7.);
					easing.EasingMode(winrt::Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut);
					m_widthAnimation.EasingFunction(easing);
				}


				if (!m_firstWidth)
				{
					m_contentPresenter.Width(0);
				}
				else
				{
					return;
				}

				if (m_storyboard && m_storyboard.GetCurrentState() == winrt::Windows::UI::Xaml::Media::Animation::ClockState::Active)
					return;
				m_widthAnimation.To(args.NewSize().Width);
				m_firstWidth = args.NewSize().Width;
				m_widthAnimation.Duration({ duration, winrt::Windows::UI::Xaml::DurationType::TimeSpan });
			});
	}

	winrt::Windows::Foundation::IInspectable IconButton::Icon()
	{
		return GetValue(m_iconProperty);
	}

	void IconButton::Icon(winrt::Windows::Foundation::IInspectable value)
	{
		if (!m_iconContent)
			m_iconContent = {};
		m_iconContent.Content(value);
		SetValue(m_iconProperty, value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty IconButton::IconProperty()
	{
		return m_iconProperty;
	}

	void IconButton::Collapse()
	{
		//winrt::Windows::UI::Xaml::VisualStateManager::GoToState(*this, L"PointerExit", true);
		if (!m_storyboard)
			return;

		m_storyboard.AutoReverse(true);
		m_storyboard.Begin();
		//m_storyboard.Resume();
		m_storyboard.Seek(duration);
	}
	void IconButton::Expand()
	{
		if (!m_storyboard)
		{
			m_storyboard = {};
			m_storyboard.Duration({ duration, winrt::Windows::UI::Xaml::DurationType::TimeSpan });
			m_storyboard.Children().Append(m_widthAnimation);

			winrt::Windows::UI::Xaml::Media::Animation::DoubleAnimation opacityAnimation;
			opacityAnimation.From(0.0);
			opacityAnimation.To(1.0);
			opacityAnimation.Duration({ duration, winrt::Windows::UI::Xaml::DurationType::TimeSpan });
			winrt::Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(opacityAnimation, m_contentPresenter);
			winrt::Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(
				opacityAnimation,
				L"Opacity"
			);
			m_storyboard.Children().Append(opacityAnimation);
		}
		m_storyboard.AutoReverse(false);
		m_contentPresenter.Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
		m_storyboard.Begin();
	}
	bool IconButton::IsExpanded()
	{
		return winrt::unbox_value<bool>(GetValue(m_isExpandedProperty));
	}
	void IconButton::IsExpanded(bool value)
	{
		SetValue(m_isExpandedProperty, winrt::box_value(value));
	}
	winrt::Windows::UI::Xaml::DependencyProperty IconButton::IsExpandedProperty()
	{
		return winrt::Windows::UI::Xaml::DependencyProperty{ nullptr };
	}
	winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase IconButton::Container()
	{
		return m_container;
	}
	void IconButton::Container(winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase value)
	{
		m_container = value;
	}
	void IconButton::isExpandedPropertyChanged(winrt::Windows::UI::Xaml::DependencyObject d, winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs args)
	{
		auto newValue = winrt::unbox_value<bool>(args.NewValue());
		auto const oldValue = !newValue;
		if (newValue)
		{
			d.as<class_type>().Expand();
		}
		else
		{
			d.as<class_type>().Collapse();
		}
	}
}
