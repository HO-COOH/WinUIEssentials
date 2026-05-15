#include "pch.h"
#include "DemoTableData.h"
#if __has_include("DemoTableData.g.cpp")
#include "DemoTableData.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	int DemoTableData::RowCount()
	{
		return 100;
	}

	int DemoTableData::RowRequested(winrt::WinUI3Package::RowRequestedEventArgs const& args)
	{
		return 100;
	}
}
