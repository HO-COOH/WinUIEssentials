#include "pch.h"
#include "DataGrid.xaml.h"
#if __has_include("DataGrid.g.cpp")
#include "DataGrid.g.cpp"
#endif
#include <numeric>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	float DataGrid::separatorWidth()
	{
		return 1.0f;
	}
	void DataGrid::measureColumns(winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& session)
	{
		for (auto header : MyData().Headers())
		{
			winrt::Microsoft::Graphics::Canvas::Text::CanvasTextLayout layout
			{
				session,
				header,
				textFormat,
				0.f,
				0.f
			};
			layout.WordWrapping(winrt::Microsoft::Graphics::Canvas::Text::CanvasWordWrapping::NoWrap);
			auto metrics = layout.ClusterMetrics();
			m_measuredColumnWidth.emplace_back(
				ColumnMeasurement
				{
					.width = std::accumulate(metrics.begin(), metrics.end(), 0.f, [](float acc, auto const& m) { return acc + m.Width; }),
					.offset = separatorWidth() + (m_measuredColumnWidth.empty() ? 0 : m_measuredColumnWidth.back().offset + m_measuredColumnWidth.back().width),
					.layout = layout
				}
			);
			//session.DrawTextLayout(layout, {}, winrt::Windows::UI::Colors::White());
		}
	}

	bool DataGrid::columnMeasured() const
	{
		return !m_measuredColumnWidth.empty();
	}

	int DataGrid::getNumRows() const
	{
		return 0;
	}

	void DataGrid::drawHeaders(winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& ds)
	{
		for (auto& layout : m_measuredColumnWidth)
		{
			ds.DrawTextLayout(
				layout.layout,
				{ layout.offset, 0 },
				winrt::Windows::UI::Colors::White()
			);
			ds.DrawLine({ layout.offset - separatorWidth(), 0 }, { layout.offset - separatorWidth(), 500 }, winrt::Windows::UI::Colors::White());
		}
	}

	void DataGrid::drawRows(winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& ds, int row)
	{

	}

	void DataGrid::Canvas_Draw(
		winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, 
		winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
	{
		auto session = args.DrawingSession();

		if (!columnMeasured())
			measureColumns(session);


		drawHeaders(session);
		auto rows = getNumRows();
		for (int i = 0; i < rows; ++i)
			drawRows(session, i);
	}

}
