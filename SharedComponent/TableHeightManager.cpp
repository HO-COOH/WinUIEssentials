#include "pch.h"
#include "TableHeightManager.h"
#include <dwrite_3.h>

void TableHeightManager::UpdateHeaderFont(winrt::WinUINamespace::UI::Xaml::Media::FontFamily const& fontFamily, double fontSize)
{
	auto fontSource = fontFamily.Source();
	std::wstring_view fontSourceView{ fontSource };

	winrt::com_ptr<IDWriteFontCollection2> collection;

	auto const poundPosition = fontSourceView.find(L'#');
	if (poundPosition == std::wstring_view::npos)
	{
		//Example: "Segoe UI"
		if (!m_systemFontCollection)
			winrt::check_hresult(m_factory->GetSystemFontCollection(false, DWRITE_FONT_FAMILY_MODEL_TYPOGRAPHIC, m_systemFontCollection.put()));
		collection = m_systemFontCollection;



	}
	else
	{
		//Example: "ms-appx:///FontFile.ttf#Family Name
		winrt::com_ptr<IDWriteFontSetBuilder1> fontSetBuilder;

	}

	UINT32 index{};
	BOOL exists{};
	winrt::check_hresult(collection->FindFamilyName(fontSourceView.data(), &index, &exists));
	if (!exists)
	{
		winrt::check_hresult(collection->FindFamilyName(L"Segoe UI", &index, &exists));
		assert(exists);
	}

	winrt::com_ptr<IDWriteFontFamily> dwriteFontFamily;
	winrt::check_hresult(collection->GetFontFamily(index, dwriteFontFamily.put()));

	winrt::com_ptr<IDWriteFont> dwriteFont;
	winrt::check_hresult(dwriteFontFamily->GetFirstMatchingFont(DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STRETCH_NORMAL, DWRITE_FONT_STYLE_NORMAL, dwriteFont.put()));

	winrt::com_ptr<IDWriteFontFace> fontFace;
	winrt::check_hresult(dwriteFont->CreateFontFace(fontFace.put()));

	winrt::com_ptr<IDWriteFontFace1> fontFace_1 = fontFace.as<IDWriteFontFace1>();
	
	DWRITE_FONT_METRICS1 fontMetrics;
	fontFace_1->GetMetrics(&fontMetrics);
	auto scale = 14.f / fontMetrics.designUnitsPerEm;
	auto height = (fontMetrics.glyphBoxTop - fontMetrics.glyphBoxBottom) * scale;
}
