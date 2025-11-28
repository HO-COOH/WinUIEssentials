#pragma once

#include "DataGrid.g.h"

struct ColumnMeasurement
{
    float width;
    float offset;
    winrt::Microsoft::Graphics::Canvas::Text::CanvasTextLayout layout;
};

namespace winrt::WinUI3Example::implementation
{
    struct DataGrid : DataGridT<DataGrid>
    {
        DataGrid()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
        void Canvas_Draw(
            winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, 
            winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args);

    private:
        float separatorWidth();
		void measureColumns(winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& session);
        bool columnMeasured() const;
        int getNumRows() const;
        void drawHeaders(winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& ds);
		void drawRows(winrt::Microsoft::Graphics::Canvas::CanvasDrawingSession const& ds, int row);
        std::vector<ColumnMeasurement> m_measuredColumnWidth;
        winrt::Microsoft::Graphics::Canvas::Text::CanvasTextFormat textFormat;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DataGrid : DataGridT<DataGrid, implementation::DataGrid>
    {
    };
}
