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
		fontSize * Scale,
		localeName,
		m_headerTextFormat.put()
	));
	winrt::check_hresult(m_dwriteFactory->CreateEllipsisTrimmingSign(m_headerTextFormat.get(), m_headerTrimming.put()));
}

void TextLayoutCache::OnTableDataSet(winrt::PackageRoot::ITableData* tableDataRef)
{
	m_tableDataRef = tableDataRef;
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
		fontSize * Scale,
		localeName,
		m_cellTextFormat.put()
	));
	winrt::check_hresult(m_dwriteFactory->CreateEllipsisTrimmingSign(m_cellTextFormat.get(), m_cellTrimming.put()));
}

void TextLayoutCache::Clear()
{
	for (auto& row : m_perCellCache)
	{
		for (auto& cell : row)
			cell.content.clear();
	}
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
	if (m_perCellCache.empty())
		m_perCellCache.resize(1);
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

IDWriteTextLayout* TextLayoutCache::GetOrCreate(int row, int column)
{
	//first row for Header
	int const rowIndex = row + 1;
	if (rowIndex >= static_cast<int>(m_perCellCache.size()))
		return nullptr;

	auto& rowCache = m_perCellCache[rowIndex];
	if (column >= static_cast<int>(rowCache.size()))
		return nullptr;

	auto& cache = rowCache[column];
	if (!cache.layout)
		return nullptr;

	if (auto& columnCache = m_perColumnCache[column]; std::exchange(cache.m_contentLayoutVersion, columnCache.m_contentLayoutVersion) != columnCache.m_contentLayoutVersion)
	{
		winrt::check_hresult(cache.layout->SetMaxHeight(columnCache.maxHeight));
		winrt::check_hresult(cache.layout->SetMaxWidth(columnCache.maxWidth));
		winrt::check_hresult(cache.layout->SetTextAlignment(columnCache.ContentHorizontalAlignment));
		winrt::check_hresult(cache.layout->SetParagraphAlignment(columnCache.ContentVerticalAlignment));
	}
	return cache.layout.get();
}

void TextLayoutCache::Invalidate()
{
	++m_dataVersion;
	m_rowCount = 0;
}

void TextLayoutCache::InvalidateRow(int row)
{
	if (row < 0 || static_cast<size_t>(row) >= m_rowDataVersions.size())
		return;
	m_rowDataVersions[row] = 0;
}

bool TextLayoutCache::IsRowStale(int row) const
{
	if (row < 0)
		return false;
	if (static_cast<size_t>(row) >= m_rowDataVersions.size())
		return true;
	return m_rowDataVersions[row] != m_dataVersion;
}

void TextLayoutCache::SetCellContent(int row, int column, std::wstring_view str)
{
	int const rowIndex = row + 1;
	if (rowIndex >= static_cast<int>(m_perCellCache.size()))
		m_perCellCache.resize(rowIndex + 1);

	auto& rowCache = m_perCellCache[rowIndex];
	if (column >= static_cast<int>(rowCache.size()))
		rowCache.resize(column + 1);

	auto& cache = rowCache[column];
	if (cache.layout && cache.content == str)
		return;

	auto& columnCache = m_perColumnCache[column];
	cache.content = str;
	cache.m_contentLayoutVersion = columnCache.m_contentLayoutVersion;
	winrt::check_hresult(m_dwriteFactory->CreateTextLayout(
		str.data(),
		static_cast<uint32_t>(str.size()),
		m_cellTextFormat.get(),
		columnCache.maxWidth,
		columnCache.maxHeight,
		cache.layout.put()
	));
	constexpr DWRITE_TRIMMING trimmingOption{ .granularity = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER };
	winrt::check_hresult(cache.layout->SetTrimming(&trimmingOption, m_cellTrimming.get()));
	winrt::check_hresult(cache.layout->SetTextAlignment(columnCache.ContentHorizontalAlignment));
	winrt::check_hresult(cache.layout->SetParagraphAlignment(columnCache.ContentVerticalAlignment));
}

std::wstring_view TextLayoutCache::GetCellContent(int row, int column) const
{
	//row 0 is for header row
	return m_perCellCache[row + 1][column].content;
}

void TextLayoutCache::MarkRowFresh(int row)
{
	if (row < 0)
		return;
	if (static_cast<size_t>(row) >= m_rowDataVersions.size())
		m_rowDataVersions.resize(row + 1, 0);
	m_rowDataVersions[row] = m_dataVersion;
}

size_t TextLayoutCache::RowCount() const
{
	if (!m_rowCount && m_tableDataRef)
		m_rowCount = m_tableDataRef->RowCount();

	return m_rowCount;
}

