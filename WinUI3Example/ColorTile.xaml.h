#pragma once

#include "ColorTile.g.h"
#include <PropertyChangeHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct ColorTile : ColorTileT<ColorTile>, MvvmHelper::PropertyChangeHelper<ColorTile>
    {
        ColorTile() = default;

		winrt::hstring ColorName();
		void ColorName(winrt::hstring const& value);

		winrt::hstring ColorValue();
		static winrt::hstring FromColor(winrt::Windows::UI::Color color);
	private:
		winrt::hstring m_colorName;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ColorTile : ColorTileT<ColorTile, implementation::ColorTile>
    {
    };
}
