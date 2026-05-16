#include "pch.h"
#include "RowRequestedEventArgs.h"
#if __has_include("RowRequestedEventArgs.g.cpp")
#include "RowRequestedEventArgs.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	RowRequestedEventArgs::RowRequestedEventArgs(int startRow, int endRow)
	{
	}
	int RowRequestedEventArgs::StartRow()
	{
		return 0;
	}

	int RowRequestedEventArgs::EndRow()
	{
		return 0;
	}

	void RowRequestedEventArgs::SetRow(int row, winrt::array_view<winrt::hstring const> const& content)
	{
	}

	bool RowRequestedEventArgs::IsCanceled()
	{
		return false;
	}

	winrt::event_token RowRequestedEventArgs::Canceled(winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::RowRequestedEventArgs> const& handler)
	{
		return winrt::event_token();
	}

	void RowRequestedEventArgs::Canceled(winrt::event_token const& token)
	{
	}
}
