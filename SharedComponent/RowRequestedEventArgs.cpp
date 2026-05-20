#include "pch.h"
#include "RowRequestedEventArgs.h"
#if __has_include("RowRequestedEventArgs.g.cpp")
#include "RowRequestedEventArgs.g.cpp"
#endif
#include "TextLayoutCache.h"

namespace winrt::PackageRoot::implementation
{
	RowRequestedEventArgs::RowRequestedEventArgs(int startRow, int endRow, TextLayoutCache& cache) :
		m_startRow{ startRow }, m_endRow{ endRow }, m_cache{ cache }
	{
	}

	int RowRequestedEventArgs::StartRow()
	{
		return m_startRow;
	}

	int RowRequestedEventArgs::EndRow()
	{
		return m_endRow;
	}

	void RowRequestedEventArgs::SetRow(int row, winrt::array_view<winrt::hstring const> const& content)
	{
		for (uint32_t col = 0; col < content.size(); ++col)
		{
			auto const& s = content[col];
			m_cache.SetCellContent(row, static_cast<int>(col), std::wstring_view{ s });
		}
		m_cache.MarkRowFresh(row);
	}

	bool RowRequestedEventArgs::IsCanceled()
	{
		return false;
	}

	winrt::event_token RowRequestedEventArgs::Canceled(winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::RowRequestedEventArgs> const& handler)
	{
		return m_canceled.add(handler);
	}

	void RowRequestedEventArgs::Canceled(winrt::event_token const& token)
	{
		m_canceled.remove(token);
	}
}
