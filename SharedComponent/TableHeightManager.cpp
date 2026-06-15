#include "pch.h"
#include "TableHeightManager.h"
#include <dwrite_3.h>
#include "TableProperty.h"


winrt::com_ptr<IDWriteFontCollection2>& TableHeightManager::ensureSystemFontCollection()
{
	if (!m_systemFontCollection)
		winrt::check_hresult(m_factory->GetSystemFontCollection(false, DWRITE_FONT_FAMILY_MODEL_TYPOGRAPHIC, m_systemFontCollection.put()));
	return m_systemFontCollection;
}

DWRITE_FONT_METRICS1 TableHeightManager::getFontMetrics(std::wstring_view fontFamily)
{
	winrt::com_ptr<IDWriteFontCollection2> collection;

	auto const poundPosition = fontFamily.find(L'#');
	if (poundPosition == std::wstring_view::npos)
	{
		//Example: "Segoe UI"
		collection = ensureSystemFontCollection();
	}
	else
	{
		//Example: "ms-appx:///FontFile.ttf#Family Name
		winrt::com_ptr<IDWriteFontSetBuilder1> fontSetBuilder;
		//TODO: 
	}

	UINT32 index{};
	BOOL exists{};
	winrt::check_hresult(collection->FindFamilyName(fontFamily.data(), &index, &exists));
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
	DWRITE_FONT_METRICS1 result;
	fontFace_1->GetMetrics(&result);
	return result;
}

TableHeightManager::TableHeightManager(IDWriteFactory6* factory) : m_factory{ factory }
{
	if (m_lastFontSource.empty())
	{
		m_lastFontMetrics = getFontMetrics(L"Segoe UI");
		m_lastFontSource = L"Segoe UI";
	}
	m_headerFontHeight.store(calculateFontHeight(TableProperty::DefaultHeaderFontSize), std::memory_order_relaxed);
	m_contentFontHeight.store(calculateFontHeight(TableProperty::DefaultContentFontSize), std::memory_order_relaxed);
}

void TableHeightManager::UpdateFont(winrt::WinUINamespace::UI::Xaml::Media::FontFamily const& fontFamily)
{
	auto fontSource = fontFamily.Source();
	std::wstring_view fontSourceView{ fontSource };
	if (m_lastFontSource == fontSourceView)
		return;

	m_lastFontMetrics = getFontMetrics(fontSourceView);
	m_lastFontSource = fontSourceView;
}

float TableHeightManager::SetHeaderFontSize(float fontSize)
{
	auto const value = calculateFontHeight(fontSize);
	m_headerFontHeight.store(value, std::memory_order_relaxed);
	return value;
}

void TableHeightManager::SetContentFontSize(float fontSize)
{
	m_contentFontHeight.store(calculateFontHeight(fontSize), std::memory_order_relaxed);
}

void TableHeightManager::SetVerticalPadding(float padding)
{
	m_verticalPadding.store(padding, std::memory_order_relaxed);
}

float TableHeightManager::HeaderFontHeight() const
{
	return m_headerFontHeight.load(std::memory_order_relaxed);
}

float TableHeightManager::ContentFontHeight() const
{
	return m_contentFontHeight.load(std::memory_order_relaxed);
}

float TableHeightManager::HeaderRowHeight() const
{
	return HeaderFontHeight() + m_verticalPadding.load(std::memory_order_relaxed);
}

float TableHeightManager::ContentRowHeight() const
{
	return ContentFontHeight() + m_verticalPadding.load(std::memory_order_relaxed);
}
