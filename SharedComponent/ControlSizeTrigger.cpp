#include "pch.h"
#include "ControlSizeTrigger.h"
#if __has_include("ControlSizeTrigger.g.cpp")
#include "ControlSizeTrigger.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::m_canTriggerProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::m_maxWidthProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::m_minWidthProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::m_maxHeightProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::m_minHeightProperty = nullptr;
	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::m_targetElementProperty = nullptr;

	void ControlSizeTrigger::EnsureDependencyProperties()
	{
		if (m_canTriggerProperty) return;
		m_canTriggerProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"CanTrigger",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				winrt::box_value(true),
				&ControlSizeTrigger::valueChangeCallback
			}
		);
		m_maxWidthProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"MaxWidth",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				winrt::box_value(DBL_MAX),
				&ControlSizeTrigger::valueChangeCallback
			}
		);
		m_minWidthProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"MinWidth",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				winrt::box_value(0.0),
				&ControlSizeTrigger::valueChangeCallback
			}
		);
		m_maxHeightProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"MaxHeight",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				winrt::box_value(DBL_MAX),
				&ControlSizeTrigger::valueChangeCallback
			}
		);
		m_minHeightProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"MinHeight",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				winrt::box_value(0.0),
				&ControlSizeTrigger::valueChangeCallback
			}
		);
		m_targetElementProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"TargetElement",
			winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::FrameworkElement>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
				nullptr,
				&ControlSizeTrigger::onTargetElementPropertyChanged
			}
		);
	}

	bool ControlSizeTrigger::CanTrigger()
	{
		return winrt::unbox_value<bool>(GetValue(m_canTriggerProperty));
	}

	void ControlSizeTrigger::CanTrigger(bool value)
	{
		SetValue(m_canTriggerProperty, winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::CanTriggerProperty()
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::MaxWidthProperty()
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::MinWidthProperty()
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::MaxHeightProperty()
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::MinHeightProperty()
	{
		return m_minHeightProperty;
	}

	winrt::WinUINamespace::UI::Xaml::FrameworkElement ControlSizeTrigger::TargetElement()
	{
		return GetValue(m_targetElementProperty).as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
	}

	void ControlSizeTrigger::TargetElement(winrt::WinUINamespace::UI::Xaml::FrameworkElement const& value)
	{
		SetValue(m_targetElementProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty ControlSizeTrigger::TargetElementProperty()
	{
		return m_targetElementProperty;
	}

	void ControlSizeTrigger::updateTrigger()
	{
		updateTrigger(TargetElement());
	}

	void ControlSizeTrigger::updateTrigger(winrt::WinUINamespace::UI::Xaml::FrameworkElement const& target)
	{
		if (!target || !CanTrigger())
		{
			SetActive(false);
			return;
		}

		auto const width = target.ActualWidth();
		auto const height = target.ActualHeight();

		SetActive(
			MinWidth() <= width && width < MaxWidth() &&
			MinHeight() <= height && height < MaxHeight()
		);
	}
	void ControlSizeTrigger::valueChangeCallback(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		GetSelf(d)->updateTrigger();
	}

	void ControlSizeTrigger::onTargetElementPropertyChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		auto const newElement = e.NewValue().try_as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
		if (newElement)
		{
			self->m_onTargetElementSizeChanged = newElement.SizeChanged(
				winrt::auto_revoke,
				[self](auto&& sender, auto&&)
				{
					self->updateTrigger(sender.as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>());
				});
		}
		else
			self->m_onTargetElementSizeChanged = {};

		self->updateTrigger(newElement);
	}
}
