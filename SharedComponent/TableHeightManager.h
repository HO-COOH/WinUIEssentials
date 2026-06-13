#pragma once
#include <atomic>
#include <dwrite_3.h>

struct IDWriteFactory6;

class TableHeightManager
{
	IDWriteFactory6* m_factory;
	winrt::com_ptr<IDWriteFontCollection2> m_systemFontCollection;
	std::atomic<float> m_headerRowHeight;
public:
	TableHeightManager(IDWriteFactory6* factory) : m_factory{ factory }
	{
	}

	void UpdateHeaderFont(
		winrt::WinUINamespace::UI::Xaml::Media::FontFamily const& fontFamily,
		double fontSize
	);
};