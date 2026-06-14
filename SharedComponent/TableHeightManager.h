#pragma once
#include <atomic>
#include <dwrite_3.h>

struct IDWriteFactory6;

class TableHeightManager
{
	static inline winrt::com_ptr<IDWriteFontCollection2> m_systemFontCollection;
	static inline std::wstring m_lastFontSource;
	static inline DWRITE_FONT_METRICS1 m_lastFontMetrics;

	IDWriteFactory6* m_factory;
	std::atomic<float> m_headerFontHeight{};
	std::atomic<float> m_contentFontHeight{};
	std::atomic<float> m_verticalPadding{};
	winrt::com_ptr<IDWriteFontCollection2>& ensureSystemFontCollection();

	DWRITE_FONT_METRICS1 getFontMetrics(std::wstring_view fontFamily);

	constexpr static float calculateFontHeight(float fontSize)
	{
		auto const scale = fontSize / m_lastFontMetrics.designUnitsPerEm;
		return (m_lastFontMetrics.ascent + m_lastFontMetrics.descent + m_lastFontMetrics.lineGap) * scale;
	}
public:
	TableHeightManager(IDWriteFactory6* factory);

	void UpdateFont(winrt::WinUINamespace::UI::Xaml::Media::FontFamily const& fontFamily);
	[[maybe_unused]] float SetHeaderFontSize(float fontSize); //return the new calculated value
	void SetContentFontSize(float fontSize);
	void SetVerticalPadding(float padding);

	float HeaderFontHeight() const;
	float ContentFontHeight() const;
	float HeaderRowHeight() const;
	float ContentRowHeight() const;
};
