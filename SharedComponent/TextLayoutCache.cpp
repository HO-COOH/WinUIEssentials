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
	m_perCellCache.clear();
	m_perColumnCache.clear();
}

void TextLayoutCache::SetNumColumns(size_t columns)
{
	m_perColumnCache.resize(columns);
}

IDWriteTextLayout* TextLayoutCache::GetOrCreate(
	int column, 
	std::wstring_view str, 
	FLOAT maxWidth, 
	FLOAT maxHeight, 
	DWRITE_TEXT_ALIGNMENT horizontalAlignment, 
	DWRITE_PARAGRAPH_ALIGNMENT verticalAlignment)
{
	auto& columnLayout = m_perColumnCache[column];
	auto& headerCache = m_perCellCache.front();
	if (headerCache.empty())
		headerCache.resize(m_perColumnCache.size());
	auto& columnHeaderCache = headerCache[column];

	if (str != columnHeaderCache.content)
	{
		winrt::check_hresult(m_dwriteFactory->CreateTextLayout(
			str.data(),
			str.size(),
			m_headerTextFormat.get(),
			maxWidth,
			maxHeight,
			columnHeaderCache.layout.put()
		));
		if (
			(std::exchange(columnLayout.maxWidth, maxWidth) != maxWidth) |
			(std::exchange(columnLayout.maxHeight, maxHeight) != maxHeight)
		)
		{
			++columnLayout.m_contentLayoutVersion;
		}

		columnLayout.HeaderHorizontalAlignment = horizontalAlignment;
		columnLayout.HeaderVerticalAlignment = verticalAlignment;
		winrt::check_hresult(columnHeaderCache.layout->SetTextAlignment(horizontalAlignment));
		winrt::check_hresult(columnHeaderCache.layout->SetParagraphAlignment(verticalAlignment));
		constexpr DWRITE_TRIMMING trimmingOption{ .granularity = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER };
		winrt::check_hresult(columnHeaderCache.layout->SetTrimming(&trimmingOption, m_headerTrimming.get()));
		columnHeaderCache.content = str;

		return columnHeaderCache.layout.get();
	}

	if (std::exchange(columnLayout.maxWidth, maxWidth) != maxWidth)
	{
		winrt::check_hresult(columnHeaderCache.layout->SetMaxWidth(maxWidth));
		++columnLayout.m_contentLayoutVersion;
	}

	if (std::exchange(columnLayout.maxHeight, maxHeight) != maxHeight)
	{
		winrt::check_hresult(columnHeaderCache.layout->SetMaxHeight(maxHeight));
		++columnLayout.m_contentLayoutVersion;
	}

	if (std::exchange(columnLayout.HeaderHorizontalAlignment, horizontalAlignment) != horizontalAlignment)
		winrt::check_hresult(columnHeaderCache.layout->SetTextAlignment(horizontalAlignment));

	if (std::exchange(columnLayout.HeaderVerticalAlignment, verticalAlignment) != verticalAlignment)
		winrt::check_hresult(columnHeaderCache.layout->SetParagraphAlignment(verticalAlignment));
	return columnHeaderCache.layout.get();
}

void TextLayoutCache::SetColumnFormat(
	size_t column,
	DWRITE_TEXT_ALIGNMENT horizontalAlignment,
	DWRITE_PARAGRAPH_ALIGNMENT verticalAlignment
)
{
	auto& columnCache = m_perColumnCache[column];
	if (
		(std::exchange(columnCache.ContentHorizontalAlignment, horizontalAlignment) != horizontalAlignment) |
		(std::exchange(columnCache.ContentVerticalAlignment, verticalAlignment) != verticalAlignment)
		)
		++columnCache.m_contentLayoutVersion;
}

IDWriteTextLayout* TextLayoutCache::GetOrCreate(int row, int column, std::wstring_view str)
{
	//first row for Header
	row += 1;
	if (row >= m_perCellCache.size())
		m_perCellCache.resize(row + 1);

	auto& rowCache = m_perCellCache[row];
	if (column >= rowCache.size())
		rowCache.resize(column + 1);

	auto& cache = rowCache[column];
	if (cache.content == str)
	{
		if (auto& columnCache = m_perColumnCache[column]; std::exchange(cache.m_contentLayoutVersion, columnCache.m_contentLayoutVersion) != columnCache.m_contentLayoutVersion)
		{
			winrt::check_hresult(cache.layout->SetMaxHeight(columnCache.maxHeight));
			winrt::check_hresult(cache.layout->SetMaxWidth(columnCache.maxWidth));
			winrt::check_hresult(cache.layout->SetTextAlignment(columnCache.ContentHorizontalAlignment));
			winrt::check_hresult(cache.layout->SetParagraphAlignment(columnCache.ContentVerticalAlignment));
		}
		return cache.layout.get();
	}

	//recreate
	cache.content = str;
	auto& columnCache = m_perColumnCache[column];
	cache.m_contentLayoutVersion = columnCache.m_contentLayoutVersion;
	winrt::check_hresult(m_dwriteFactory->CreateTextLayout(
		str.data(),
		static_cast<uint32_t>(str.size()),
		row == 0 ? m_headerTextFormat.get() : m_cellTextFormat.get(),
		columnCache.maxWidth,
		columnCache.maxHeight,
		cache.layout.put()
	));
	constexpr DWRITE_TRIMMING trimmingOption{ .granularity = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER };
	winrt::check_hresult(cache.layout->SetTrimming(&trimmingOption, m_cellTrimming.get()));
	winrt::check_hresult(cache.layout->SetTextAlignment(columnCache.ContentHorizontalAlignment));
	winrt::check_hresult(cache.layout->SetParagraphAlignment(columnCache.ContentVerticalAlignment));
	return cache.layout.get();
}

