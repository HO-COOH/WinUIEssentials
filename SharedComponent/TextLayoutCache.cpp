#include "pch.h"
#include "TextLayoutCache.h"

TextLayoutCache::TextLayoutCache(IDWriteFactory* dwriteFactory) : m_dwriteFactory(dwriteFactory)
{
}

void TextLayoutCache::SetFormat(IDWriteTextFormat* textFormat)
{
	m_textFormat = textFormat;
	winrt::check_hresult(m_dwriteFactory->CreateEllipsisTrimmingSign(textFormat, m_trimming.put()));
	m_cache.clear();
}

IDWriteTextLayout* TextLayoutCache::GetOrCreate(int row, int column, std::wstring_view str, FLOAT maxWidth, FLOAT maxHeight)
{
	if (row >= m_cache.size())
		m_cache.resize(row + 1);

	auto& rowCache = m_cache[row];
	if (column >= rowCache.size())
		rowCache.resize(column + 1);

	auto& cache = rowCache[column];
	if (cache.content == str && cache.maxWidth == maxWidth && cache.maxHeight == maxHeight)
		return cache.layout.get();

	//recreate
	cache.content = str;
	cache.maxWidth = maxWidth;
	cache.maxHeight = maxHeight;
	winrt::check_hresult(m_dwriteFactory->CreateTextLayout(
		str.data(),
		static_cast<uint32_t>(str.size()),
		m_textFormat,
		maxWidth,
		maxHeight,
		cache.layout.put()
	));
	constexpr DWRITE_TRIMMING trimmingOption{ .granularity = DWRITE_TRIMMING_GRANULARITY::DWRITE_TRIMMING_GRANULARITY_CHARACTER };
	winrt::check_hresult(cache.layout->SetTrimming(&trimmingOption, m_trimming.get()));
	return cache.layout.get();
}

