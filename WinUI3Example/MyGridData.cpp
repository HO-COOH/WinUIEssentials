#include "pch.h"
#include "MyGridData.h"
#if __has_include("MyGridData.g.cpp")
#include "MyGridData.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	MyGridData::MyGridData() : m_headers{ winrt::single_threaded_vector(
		std::vector<winrt::hstring>
		{
			L"Column1",
			L"Column2"
		}
	) }
	{

	}

	winrt::Windows::Foundation::Collections::IVector<winrt::hstring> MyGridData::Headers()
	{
		return m_headers;
	}

	winrt::hstring MyGridData::OnGetData(int32_t row, int32_t column)
	{
		return winrt::hstring{ std::format(L"R{}C{}", row, column) };
	}

	int MyGridData::OnGetNumRows()
	{
		return 3;
	}
}
