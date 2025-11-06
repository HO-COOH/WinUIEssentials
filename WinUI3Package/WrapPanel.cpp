#include "pch.h"
#include "WrapPanel.h"
#if __has_include("WrapPanel.g.cpp")
#include "WrapPanel.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty WrapPanel::s_horizontalSpacingProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"HorizontalSpacing",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(0.0), &WrapPanel::propertyChanged }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty WrapPanel::s_verticalSpacingProperty = 
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"VerticalSpacing",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(0.0), &WrapPanel::propertyChanged }
	);

	winrt::Microsoft::UI::Xaml::DependencyProperty WrapPanel::s_orientationProperty = 
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Orientation",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::Orientation>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ 
					winrt::box_value(winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal), 
					&WrapPanel::propertyChanged 
				}
	);

	double WrapPanel::HorizontalSpacing()
	{
		return winrt::unbox_value<double>(GetValue(s_horizontalSpacingProperty));
	}

	void WrapPanel::HorizontalSpacing(double value)
	{
		SetValue(s_horizontalSpacingProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WrapPanel::HorizontalSpacingProperty()
	{
		return s_horizontalSpacingProperty;
	}

	double WrapPanel::VerticalSpacing()
	{
		return winrt::unbox_value<double>(GetValue(s_verticalSpacingProperty));
	}

	void WrapPanel::VerticalSpacing(double value)
	{
		SetValue(s_verticalSpacingProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WrapPanel::VerticalSpacingProperty()
	{
		return s_verticalSpacingProperty;
	}

	winrt::Microsoft::UI::Xaml::Controls::Orientation WrapPanel::Orientation()
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Xaml::Controls::Orientation>(GetValue(s_orientationProperty));
	}

	void WrapPanel::Orientation(winrt::Microsoft::UI::Xaml::Controls::Orientation value)
	{
		SetValue(s_orientationProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WrapPanel::OrientationProperty()
	{
		return s_orientationProperty;
	}

	winrt::Windows::Foundation::Size WrapPanel::MeasureOverride(winrt::Windows::Foundation::Size availableSize)
	{
		winrt::Windows::Foundation::Size desiredSize{ 0, 0 };
		float currentLineSize = 0;
		float currentLineHeight = 0;
		float const horizontalSpacing = HorizontalSpacing();
		float const verticalSpacing = VerticalSpacing();
		auto const orientation = Orientation();
		
		for (auto const& child : Children())
		{
			child.Measure(availableSize);
			auto childDesiredSize = child.DesiredSize();

			if (orientation == winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal)
			{
				if (currentLineSize + childDesiredSize.Width > availableSize.Width)
				{
					desiredSize.Height += currentLineHeight + verticalSpacing;
					currentLineHeight = 0;
					currentLineSize = 0;
				}
				currentLineSize += childDesiredSize.Width + horizontalSpacing;
				desiredSize.Width = max(desiredSize.Width, currentLineSize - horizontalSpacing);
				currentLineHeight = max(currentLineHeight, childDesiredSize.Height);
			}
			else
			{
				// Vertical orientation
				if (currentLineSize + childDesiredSize.Height > availableSize.Height)
				{
					desiredSize.Width += currentLineHeight + horizontalSpacing;
					currentLineHeight = 0;
					currentLineSize = 0;
				}
				currentLineSize += childDesiredSize.Height + verticalSpacing;
				desiredSize.Height = max(desiredSize.Height, currentLineSize - verticalSpacing);
				currentLineHeight = max(currentLineHeight, childDesiredSize.Width);
			}
		}
		if (orientation == winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal)
		{
			//desiredSize.Width = currentLineSize - horizontalSpacing;
			desiredSize.Height += currentLineHeight;
		}
		else
		{
			//desiredSize.Height = currentLineSize - horizontalSpacing;
			desiredSize.Width += currentLineHeight;
		}
		return desiredSize;
	}

	winrt::Windows::Foundation::Size WrapPanel::ArrangeOverride(winrt::Windows::Foundation::Size finalSize)
	{
		float currentLineSize = 0;
		float currentLineHeight = 0;
		float const horizontalSpacing = HorizontalSpacing();
		float const verticalSpacing = VerticalSpacing();
		auto const orientation = Orientation();
		float offsetX = 0;
		float offsetY = 0;
		for (auto const& child : Children())
		{
			auto childDesiredSize = child.DesiredSize();
			if (orientation == winrt::Microsoft::UI::Xaml::Controls::Orientation::Horizontal)
			{
				if (currentLineSize + childDesiredSize.Width > finalSize.Width)
				{
					offsetY += currentLineHeight + verticalSpacing;
					offsetX = 0;
					currentLineHeight = 0;
					currentLineSize = 0;
				}
				child.Arrange(winrt::Windows::Foundation::Rect{ offsetX, offsetY, childDesiredSize.Width, childDesiredSize.Height });
				offsetX += childDesiredSize.Width + horizontalSpacing;
				currentLineHeight = max(currentLineHeight, childDesiredSize.Height);
				currentLineSize += childDesiredSize.Width + horizontalSpacing;
			}
			else
			{
				if (currentLineSize + childDesiredSize.Height > finalSize.Height)
				{
					offsetX += currentLineHeight + horizontalSpacing;
					offsetY = 0;
					currentLineHeight = 0;
					currentLineSize = 0;
				}
				child.Arrange(winrt::Windows::Foundation::Rect{ offsetX, offsetY, childDesiredSize.Width, childDesiredSize.Height });
				offsetY += childDesiredSize.Height + verticalSpacing;
				currentLineHeight = max(currentLineHeight, childDesiredSize.Width);
				currentLineSize += childDesiredSize.Height + verticalSpacing;
			}
		}
		
		return finalSize;
	}

	void WrapPanel::propertyChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
	{
		if (auto panel = sender.try_as<WrapPanel>())
		{
			panel->InvalidateMeasure();
			panel->InvalidateArrange();
		}
	}
}
