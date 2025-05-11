#pragma once
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>


namespace VisualTreeHelper
{
	/**
	 * Find the first child (in a depth first search way) of a control that has the specified type and name
	 *
	 * @param parent The control to be searched
	 * @param name The name of the child component
	 * @tparam T The type of the child component
	 * @return The found child, or nullptr
	 */
	template<typename T>
	[[nodiscard]] T FindVisualChildByName(winrt::Microsoft::UI::Xaml::DependencyObject const& parent, winrt::hstring const& name)
	{
		if (!parent) return nullptr;

		//if the current element satisfy the condition
		if (auto current = parent.try_as<T>(); current && current.Name() == name)
			return current;

		//recursively check the visual children of the current element
		auto const childrenCount = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(parent);
		for (auto i = 0; i < childrenCount; ++i)
		{
			if (auto result = FindVisualChildByName<T>(winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChild(parent, i), name))
				return result;
		}

		return nullptr;
	}

	/**
	 * Find the first child (in a depth first search way) of a control that has the specified type
	 *
	 * @param parent The control to be searched
	 * @tparam T The type of the child component
	 * @return The found child, or nullptr
	 */
	template<typename T>
	[[nodiscard]] T FindVisualChildByType(winrt::Microsoft::UI::Xaml::DependencyObject const& parent)
	{
		if (!parent) return nullptr;

		//if the current element satisfy the condition
		if (auto current = parent.try_as<T>())
			return current;

		//recursively check the visual children of the current element
		auto const childrenCount = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(parent);
		for (auto i = 0; i < childrenCount; ++i)
		{
			if (auto result = FindVisualChildByType<T>(winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChild(parent, i)))
				return result;
		}

		return nullptr;
	}
}
