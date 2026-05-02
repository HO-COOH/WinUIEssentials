#include "pch.h"
#include "TextLayoutCache.h"

TextLayoutCache::TextLayoutCache(IDWriteFactory* dwriteFactory) : m_dwriteFactory(dwriteFactory)
{
}

void TextLayoutCache::CreateHeaderTextFormat(
	WCHAR const* fontFamilyName, 
	IDWriteFontCollection* fontCollection,
	DWRITE_FONT_WEIGHT fontWeight, 
	DWRITE_FONT_STYLE fontStyle, 
	DWRITE_FONT_STRETCH fontStretch, 
	FLOAT fontSize, 
	WCHAR const* localeName)
{
	winrt::check_hresult(m_dwriteFactory->CreateTextFormat(
		fontFamilyName,
		fontCollection,
		fontWeight,
		fontStyle,
		fontStretch,
		fontSize,
		localeName,
		m_headerTextFormat.put()
	));
	winrt::check_hresult(m_dwriteFactory->CreateEllipsisTrimmingSign(m_headerTextFormat.get(), m_headerTrimming.put()));
}

void TextLayoutCache::CreateCeilTextFormat(
	WCHAR const* fontFamilyName, 
	IDWriteFontCollection* fontCollection,
	DWRITE_FONT_WEIGHT fontWeight,
	DWRITE_FONT_STYLE fontStyle, 
	DWRITE_FONT_STRETCH fontStretch,
	FLOAT fontSize, 
	WCHAR const* localeName)
{
	winrt::check_hresult(m_dwriteFactory->CreateTextFormat(
		fontFamilyName,
		fontCollection,
		fontWeight,
		fontStyle,
		fontStretch,
		fontSize,
		localeName,
		m_cellTextFormat.put()
	));
	winrt::check_hresult(m_dwriteFactory->CreateEllipsisTrimmingSign(m_cellTextFormat.get(), m_cellTrimming.put()));
}

void TextLayoutCache::Clear()
{
	m_cache.clear();
}

IDWriteTextLayout* TextLayoutCache::GetOrCreate(int row, int column, std::wstring_view str, FLOAT maxWidth, FLOAT maxHeight)
{
	//first row for Header
	row += 1;
	if (row >= m_cache.size())
		m_cache.resize(row + 1);

	auto& rowCache = m_cache[row];
	if (column >= rowCache.size())
		rowCache.resize(column + 1);

	auto& cache = rowCache[column];
	if (cache.content == str)
	{
		if (cache.maxWidth != maxWidth)
		{
			winrt::check_hresult(cache.layout->SetMaxWidth(maxWidth));
			cache.maxWidth = maxWidth;
		}
		if (cache.maxHeight != maxHeight)
		{
			winrt::check_hresult(cache.layout->SetMaxHeight(maxHeight));
			cache.maxHeight = maxHeight;
		}
		return cache.layout.get();
	}

	//recreate
	cache.content = str;
	cache.maxWidth = maxWidth;
	cache.maxHeight = maxHeight;
	winrt::check_hresult(m_dwriteFactory->CreateTextLayout(
		str.data(),
		static_cast<uint32_t>(str.size()),
		row == 0 ? m_headerTextFormat.get() : m_cellTextFormat.get(),
		maxWidth,
		maxHeight,
		cache.layout.put()
	));
	constexpr DWRITE_TRIMMING trimmingOption{ .granularity = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER };
	winrt::check_hresult(cache.layout->SetTrimming(&trimmingOption, m_cellTrimming.get()));
	//winrt::check_hresult(cache.layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER));
	return cache.layout.get();
}

