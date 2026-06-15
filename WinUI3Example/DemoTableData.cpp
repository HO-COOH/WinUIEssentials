#include "pch.h"
#include "DemoTableData.h"
#if __has_include("DemoTableData.g.cpp")
#include "DemoTableData.g.cpp"
#endif
#include <array>

namespace winrt::WinUI3Example::implementation
{
	int DemoTableData::RowCount()
	{
		return m_data.Count();
	}

	int DemoTableData::RowRequested(winrt::WinUI3Package::RowRequestedEventArgs const& args)
	{
		constexpr size_t columnCount = std::size(TableTestData::Columns);
		std::array<winrt::Windows::Foundation::IInspectable, columnCount> cells;

		int const start = args.StartRow();
		int const end = args.EndRow();
		for (int row = start; row <= end; ++row)
		{
			auto& data = m_data[row];
			for (size_t col = 0; col < columnCount; ++col)
			{
				auto const& content = data[static_cast<int>(col)];
				switch (content.index())
				{
					case 1:
						cells[col] = winrt::box_value(std::get<bool>(content));
						break;
					case 2:
						cells[col] = winrt::box_value(std::get<std::wstring>(content));
						break;
					default:
						throw std::runtime_error{ "Invalid data type" };
				}
			}

			args.SetRow(row, cells);
		}
		return end - start + 1;
	}

	void DemoTableData::SetData(int row, int column, winrt::Windows::Foundation::IInspectable const& value)
	{
		auto& data = m_data[row];
		if (auto pv = value.try_as<winrt::Windows::Foundation::IPropertyValue>())
		{
			switch (pv.Type())
			{
				case winrt::Windows::Foundation::PropertyType::String:
					data.Set(column, std::wstring{ pv.GetString() });
					break;
				case winrt::Windows::Foundation::PropertyType::Boolean:
					data.Set(column, pv.GetBoolean());
					break;
			}
		}
	}
}
