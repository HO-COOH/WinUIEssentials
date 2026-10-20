#pragma once
#include <winrt/Microsoft.UI.Xaml.Controls.h>

namespace GridHelper
{
	template<bool SpanRow = true, bool SpanColumn = true>
	void SpanGrid(winrt::Microsoft::UI::Xaml::FrameworkElement const& element, winrt::Microsoft::UI::Xaml::Controls::Grid const& grid)
	{
		if constexpr (SpanRow)
			winrt::Microsoft::UI::Xaml::Controls::Grid::SetRowSpan(element, (std::max)(1u, grid.RowDefinitions().Size())); //Size() returns uint32_t

		if constexpr (SpanColumn)
			winrt::Microsoft::UI::Xaml::Controls::Grid::SetColumnSpan(element, (std::max)(1u, grid.ColumnDefinitions().Size()));
	}
}