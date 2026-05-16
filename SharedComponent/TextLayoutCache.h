#pragma once
#include <vector>
#include <winrt/base.h>
#include <dwrite.h>

namespace winrt::PackageRoot
{
	struct ITableData;
}

class ColumnWidthManager;

class TextLayoutCache
{
public:
	TextLayoutCache(IDWriteFactory* dwriteFactory);

	void CreateHeaderTextFormat(
		WCHAR const* fontFamilyName,
		IDWriteFontCollection* fontCollection,
		DWRITE_FONT_WEIGHT fontWeight,
		DWRITE_FONT_STYLE fontStyle,
		DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize,
		WCHAR const* localeName
	);

	void OnTableDataSet(winrt::PackageRoot::ITableData* tableDataRef);

	void CreateCeilTextFormat(
		WCHAR const* fontFamilyName,
		IDWriteFontCollection* fontCollection,
		DWRITE_FONT_WEIGHT fontWeight,
		DWRITE_FONT_STYLE fontStyle,
		DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize,
		WCHAR const* localeName
	);
	void Clear();
	void SetNumColumns(size_t columns);

	//for header
	IDWriteTextLayout* GetOrCreate(
		int column,
		std::wstring_view str,
		FLOAT maxWidth,
		FLOAT maxHeight,
		DWRITE_TEXT_ALIGNMENT horizontalAlignment,
		DWRITE_PARAGRAPH_ALIGNMENT verticalAlignment
	);

	//for content
	void SetColumnFormat(
		size_t column,
		DWRITE_TEXT_ALIGNMENT horizontalAlignment,
		DWRITE_PARAGRAPH_ALIGNMENT verticalAlignment
	);
	IDWriteTextLayout* GetOrCreate(
		int row, 
		int column
	);

	float Scale{ -1.f };
	
	size_t RowCount() const;
private:
	mutable size_t m_rowCount{};
	struct TextLayout
	{
		std::wstring content{};
		winrt::com_ptr<IDWriteTextLayout> layout;
		uint32_t m_contentLayoutVersion{};
	};

	struct PerColumnLayout
	{
		FLOAT maxWidth = (std::numeric_limits<FLOAT>::max)();
		FLOAT maxHeight = (std::numeric_limits<FLOAT>::max)();
		DWRITE_TEXT_ALIGNMENT HeaderHorizontalAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER;
		DWRITE_TEXT_ALIGNMENT ContentHorizontalAlignment;
		DWRITE_PARAGRAPH_ALIGNMENT HeaderVerticalAlignment = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
		DWRITE_PARAGRAPH_ALIGNMENT ContentVerticalAlignment = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
		uint32_t m_contentLayoutVersion = 1;
	};

	std::vector<std::vector<TextLayout>> m_perCellCache; //this include the header row
	std::vector<PerColumnLayout> m_perColumnCache;

	IDWriteFactory* m_dwriteFactory;

	//header text
	winrt::com_ptr<IDWriteTextFormat> m_headerTextFormat;
	winrt::com_ptr<IDWriteInlineObject> m_headerTrimming;

	//cell text
	winrt::com_ptr<IDWriteTextFormat> m_cellTextFormat;
	winrt::com_ptr<IDWriteInlineObject> m_cellTrimming;

	winrt::PackageRoot::ITableData* m_tableDataRef{};

	friend class ColumnWidthManager;
};