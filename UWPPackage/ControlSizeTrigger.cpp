#include "pch.h"
#include "ControlSizeTrigger.h"
#if __has_include("ControlSizeTrigger.g.cpp")
#include "ControlSizeTrigger.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::m_canTriggerProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"CanTrigger",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<UWPPackage::ControlSizeTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(true),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::m_maxWidthProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"MaxWidth",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<UWPPackage::ControlSizeTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(DBL_MAX),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::m_minWidthProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"MinWidth",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<UWPPackage::ControlSizeTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(0.0),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::m_maxHeightProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"MaxHeight",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<UWPPackage::ControlSizeTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(DBL_MAX),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::m_minHeightProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"MinHeight",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<UWPPackage::ControlSizeTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(0.0),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::m_targetElementProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"TargetElement",
			winrt::xaml_typename<winrt::Windows::UI::Xaml::FrameworkElement>(),
			winrt::xaml_typename<UWPPackage::ControlSizeTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				nullptr,
				&ControlSizeTrigger::onTargetElementPropertyChanged
			}
	);


	bool ControlSizeTrigger::CanTrigger()
	{
		return winrt::unbox_value<bool>(GetValue(m_canTriggerProperty));
	}

	void ControlSizeTrigger::CanTrigger(bool value)
	{
		SetValue(m_canTriggerProperty, winrt::box_value(value));
	}

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::CanTriggerProperty()
	{
		return m_canTriggerProperty;
	}

	double ControlSizeTrigger::MaxWidth()
	{
		return winrt::unbox_value<double>(GetValue(m_maxWidthProperty));
	}

	void ControlSizeTrigger::MaxWidth(double value)
	{
		SetValue(m_maxWidthProperty, winrt::box_value(value));
	}

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::MaxWidthProperty()
	{
		return m_maxWidthProperty;
	}

	double ControlSizeTrigger::MinWidth()
	{
		return winrt::unbox_value<double>(GetValue(m_minWidthProperty));
	}

	void ControlSizeTrigger::MinWidth(double value)
	{
		SetValue(m_minWidthProperty, winrt::box_value(value));
	}

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::MinWidthProperty()
	{
		return m_minWidthProperty;
	}

	double ControlSizeTrigger::MaxHeight()
	{
		return winrt::unbox_value<double>(GetValue(m_maxHeightProperty));
	}

	void ControlSizeTrigger::MaxHeight(double value)
	{
		SetValue(m_maxHeightProperty, winrt::box_value(value));
	}

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::MaxHeightProperty()
	{
		return m_maxHeightProperty;
	}

	double ControlSizeTrigger::MinHeight()
	{
		return winrt::unbox_value<double>(GetValue(m_minHeightProperty));
	}

	void ControlSizeTrigger::MinHeight(double value)
	{
		SetValue(m_minHeightProperty, winrt::box_value(value));
	}

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::MinHeightProperty()
	{
		return m_minHeightProperty;
	}

	winrt::Windows::UI::Xaml::FrameworkElement ControlSizeTrigger::TargetElement()
	{
		return GetValue(m_targetElementProperty).as<winrt::Windows::UI::Xaml::FrameworkElement>();
	}

	void ControlSizeTrigger::TargetElement(winrt::Windows::UI::Xaml::FrameworkElement value)
	{
		SetValue(m_targetElementProperty, value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty ControlSizeTrigger::TargetElementProperty()
	{
		return m_targetElementProperty;
	}

	bool ControlSizeTrigger::IsActive()
	{
		return m_isActive;
	}

	void ControlSizeTrigger::updateTrigger()
	{
		if (!TargetElement() || !CanTrigger())
		{
			SetActive(false);
			return;
		}

		bool const active =
			MinWidth() <= TargetElement().ActualWidth() &&
			TargetElement().ActualWidth() < MaxWidth() &&
			MinHeight() <= TargetElement().ActualHeight() &&
			TargetElement().ActualHeight() < MaxHeight();

		m_isActive = active;
		SetActive(active);
	}
	void ControlSizeTrigger::valueChangeCallback(
		winrt::Windows::UI::Xaml::DependencyObject d,
		winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<ControlSizeTrigger>(d.as<UWPPackage::ControlSizeTrigger>())->updateTrigger();
	}

	void ControlSizeTrigger::onTargetElementPropertyChanged(
		winrt::Windows::UI::Xaml::DependencyObject d,
		winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		winrt::get_self<ControlSizeTrigger>(d.as<UWPPackage::ControlSizeTrigger>())->updateTargetElement(
			e.OldValue().as<winrt::Windows::UI::Xaml::FrameworkElement>(),
			e.NewValue().as<winrt::Windows::UI::Xaml::FrameworkElement>()
		);
	}
	void ControlSizeTrigger::updateTargetElement(
		winrt::Windows::UI::Xaml::FrameworkElement oldValue,
		winrt::Windows::UI::Xaml::FrameworkElement newValue)
	{
		if (oldValue)
			oldValue.SizeChanged(m_onTargetElementSizeChanged);
		if (newValue)
		{
			m_onTargetElementSizeChanged = newValue.SizeChanged([this](auto...)
				{
					updateTrigger();
				});
		}
		updateTrigger();
	}
}
