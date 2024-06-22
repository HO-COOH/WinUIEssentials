#include "pch.h"
#include "ControlSizeTrigger.h"
#if __has_include("ControlSizeTrigger.g.cpp")
#include "ControlSizeTrigger.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::m_canTriggerProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CanTrigger",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<WinUI3Package::ControlSizeTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				winrt::box_value(true),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::m_maxWidthProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"MaxWidth",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<WinUI3Package::ControlSizeTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				winrt::box_value(DBL_MAX),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::m_minWidthProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"MinWidth",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<WinUI3Package::ControlSizeTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				winrt::box_value(0.0),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::m_maxHeightProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"MaxHeight",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<WinUI3Package::ControlSizeTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				winrt::box_value(DBL_MAX),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::m_minHeightProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"MinHeight",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<WinUI3Package::ControlSizeTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				winrt::box_value(0.0),
				&ControlSizeTrigger::valueChangeCallback
			}
	);

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::m_targetElementProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"TargetElement",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::FrameworkElement>(),
			winrt::xaml_typename<WinUI3Package::ControlSizeTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
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

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::CanTriggerProperty()
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

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::MaxWidthProperty()
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

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::MinWidthProperty()
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

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::MaxHeightProperty()
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

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::MinHeightProperty()
	{
		return m_minHeightProperty;
	}

	winrt::Microsoft::UI::Xaml::FrameworkElement ControlSizeTrigger::TargetElement()
	{
		return GetValue(m_targetElementProperty).as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
	}

	void ControlSizeTrigger::TargetElement(winrt::Microsoft::UI::Xaml::FrameworkElement value)
	{
		SetValue(m_targetElementProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ControlSizeTrigger::TargetElementProperty()
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
		winrt::Microsoft::UI::Xaml::DependencyObject d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<ControlSizeTrigger>(d.as<WinUI3Package::ControlSizeTrigger>())->updateTrigger();
	}

	void ControlSizeTrigger::onTargetElementPropertyChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		winrt::get_self<ControlSizeTrigger>(d.as<WinUI3Package::ControlSizeTrigger>())->updateTargetElement(
			e.OldValue().as<winrt::Microsoft::UI::Xaml::FrameworkElement>(),
			e.NewValue().as<winrt::Microsoft::UI::Xaml::FrameworkElement>()
		);
	}
	void ControlSizeTrigger::updateTargetElement(
		winrt::Microsoft::UI::Xaml::FrameworkElement oldValue,
		winrt::Microsoft::UI::Xaml::FrameworkElement newValue)
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
