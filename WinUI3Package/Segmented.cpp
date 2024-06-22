#include "pch.h"
#include "Segmented.h"
#if __has_include("Segmented.g.cpp")
#include "Segmented.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	Segmented::Segmented()
	{
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::Controls::Primitives::Selector::SelectedIndexProperty(),
			{ this, &Segmented::onSelectedIndexChanged }
		);
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::Controls::ListViewBase::SelectionModeProperty(),
			{ this, &Segmented::onSelectionModeChanged }
		);
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::FrameworkElement::HorizontalAlignmentProperty(),
			{ this, &Segmented::onHorizontalAlignmentChanged }
		);
		RegisterPropertyChangedCallback(
			winrt::Microsoft::UI::Xaml::Controls::ItemsControl::ItemsPanelProperty(),
			{ this, &Segmented::onItemsPanelChanged }
		);
	}

	void Segmented::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();


		auto knob = GetTemplateChild(L"Knob");
		if (!knob)
			return;

		m_knob = knob.as<winrt::Microsoft::UI::Xaml::Controls::Border>();

		m_knobTranslateXAnimation = GetTemplateChild(L"KnobTranslateAnimation").as<winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation>();
		m_knobTranslateYAnimation = GetTemplateChild(L"KnobTranslateYAnimation").as<winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation>();

		m_knobWidthAnimation = GetTemplateChild(L"KnobWidthAnimation").as<winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation>();
		m_knobHeightAnimation = GetTemplateChild(L"KnobHeightAnimation").as<winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation>();

		m_knobAnimation = GetTemplateChild(L"KnobAnimation").as<winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard>();

		winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"MultiSelectionState", false);

		if (m_isMultiSelect = (SelectionMode() == winrt::Microsoft::UI::Xaml::Controls::ListViewSelectionMode::Multiple))
			setMultiSelectStyle(m_isMultiSelect);
	}

	winrt::Windows::Foundation::Numerics::float2 Segmented::SelectedItemActualWidth()
	{
		return Items().GetAt(m_internalSelectedIndex).as<winrt::Microsoft::UI::Xaml::UIElement>().ActualSize();
	}

	winrt::Windows::Foundation::Numerics::float2 Segmented::SelectedItemOffset()
	{
		auto selectedItem2 = Items().GetAt(m_internalSelectedIndex).as<winrt::Microsoft::UI::Xaml::UIElement>();
		auto transform = selectedItem2.TransformToVisual(*this);

		auto actualWidth = ActualWidth();

		auto selectedItemSize = selectedItem2.ActualSize();
		auto relative = transform.TransformPoint({ float(selectedItemSize.x / 2), float(selectedItemSize.y / 2) });
		return winrt::Windows::Foundation::Numerics::float2(relative.X - actualWidth / 2, relative.Y - ActualHeight() / 2);
	}

	void Segmented::onSelectedIndexChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyProperty const& indexProperty)
	{
		if (!m_knob)
			return;

		auto const selectedIndex = SelectedIndex();
		if (selectedIndex == -1)
			return;

		if (/*m_internalSelectedIndex == -1 && selectedIndex > -1*/ !m_isMultiSelect)
		{
			m_internalSelectedIndex = selectedIndex;

			if (!m_isFirst)
			{

				auto currentItemSize = SelectedItemActualWidth();
				m_knobWidthAnimation.To(currentItemSize.x);
				m_knobHeightAnimation.To(currentItemSize.y);
			}
			else
			{
				//play occuring animation
				auto [width, height] = SelectedItemActualWidth();
				m_knob.Width(width);
				m_knob.Height(height);
				GetTemplateChild(L"KnobAppearAnimation").as<winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard>().Begin();
				m_isFirst = false;
			}

			auto [offsetX, offsetY] = SelectedItemOffset();
			m_knobTranslateXAnimation.To(offsetX);
			m_knobTranslateYAnimation.To(offsetY);
			m_knobAnimation.Begin();

			m_knobSizeChangeRevoker = Items().GetAt(selectedIndex).as<winrt::Microsoft::UI::Xaml::FrameworkElement>().SizeChanged(
				winrt::auto_revoke,
				[this](auto...)
				{
					onSelectedIndexChanged(nullptr, nullptr);
				}
			);
		}
	}

	void Segmented::onSelectionModeChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyProperty const& selectionModeProperty)
	{
		if (!m_knob)
			return;

		setMultiSelectStyle(
			winrt::unbox_value<winrt::Microsoft::UI::Xaml::Controls::ListViewSelectionMode>(sender.GetValue(selectionModeProperty)) ==
			winrt::Microsoft::UI::Xaml::Controls::ListViewSelectionMode::Multiple
		);
	}

	void Segmented::onHorizontalAlignmentChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyProperty const& horizontalAlignmentProperty)
	{
		if (auto panel = ItemsPanelRoot())
		{
			panel.HorizontalAlignment(winrt::unbox_value<winrt::Microsoft::UI::Xaml::HorizontalAlignment>(GetValue(horizontalAlignmentProperty)));
		}
	}

	void Segmented::onItemsPanelChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender, winrt::Microsoft::UI::Xaml::DependencyProperty const& itemsPanelProperty)
	{
		onHorizontalAlignmentChanged(nullptr, nullptr);
	}

	void Segmented::setMultiSelectStyle(bool value)
	{
		m_isMultiSelect = value;
		ItemContainerStyle(
			winrt::Microsoft::UI::Xaml::Application::Current().Resources().Lookup(winrt::box_value(value ? L"MultiSelectionSegmentedItemStyle" : L"DefaultSegmentedItemStyle")).as<winrt::Microsoft::UI::Xaml::Style>()
		);
		if (m_knob)
		{
			m_knob.Opacity(0);
			m_isFirst = !value;
		}
	}
}
