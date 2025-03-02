#include "pch.h"
#include "ColorTile.xaml.h"
#if __has_include("ColorTile.g.cpp")
#include "ColorTile.g.cpp"
#endif


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::hstring ColorTile::ColorName()
	{
		return m_colorName;
	}

	void ColorTile::ColorName(winrt::hstring const& value)
	{
		m_colorName = value;
	}

	winrt::hstring ColorTile::ColorValue()
	{
		return {};
	}

	winrt::hstring ColorTile::FromColor(winrt::Windows::UI::Color color)
	{
		return winrt::hstring{ std::format(L"#{:02X}{:02X}{:02X}", color.R, color.G, color.B) };
	}
}
