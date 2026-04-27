#include "pch.h"
#include "Table.h"
#if __has_include("Table.g.cpp")
#include "Table.g.cpp"
#endif
#include "TableConstants.hpp"
#include "D2DPrimitiveHelper.h"
#include <winrt/Microsoft.UI.Input.h>
#include <timeapi.h>
#include <numeric>

namespace winrt::WinUI3Package::implementation
{
    Table::Table() : m_columnWidths(m_data.Count(), TableConstants::ColumnWidth), m_smoothScrollThread{[this](std::stop_token st) {scrollThreadProc(st); }}
    {
        InitializeComponent();
        m_dispatcherQueue = DispatcherQueue();

        //graphics devices
		m_swapChain.Set(m_d3dDevice.get(), *this);
        auto dxgiDevice = m_d3dDevice.as<IDXGIDevice1>();
        winrt::check_hresult(dxgiDevice->SetMaximumFrameLatency(1));
        auto d2d1Factory = DirectN::CreateD2D1Factory();
        auto d2d1Device = DirectN::GetD2D1Device(d2d1Factory.get(), m_d3dDevice.get());
		winrt::check_hresult(d2d1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, m_d2dContext.put()));
        winrt::check_hresult(m_dwriteFactory->CreateTextFormat(
            L"Segoe UI Semibold",
            nullptr,
            DWRITE_FONT_WEIGHT_SEMI_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            TableConstants::HeaderFontSize,
            L"en-US",
            m_headerTextFormat.put()
        ));
        winrt::check_hresult(m_dwriteFactory->CreateTextFormat(
            L"Segoe UI",
            nullptr,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            TableConstants::CellFontSize,
            L"en-US",
            m_cellTextFormat.put()
        ));
		m_textLayoutCache.SetFormat(m_cellTextFormat.get());
		winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), m_textBrush.put()));
		winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x0F / static_cast<float>(0xFF)), m_backgroundBrush.put()));
		winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x2F / static_cast<float>(0xFF)), m_alternateBackgroundBrush.put()));
        winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x4cc2ff), m_pillBrush.put()));

        //get ui elements
        m_verticalScrollBarCache.Set(VerticalScrollBar());
		m_horizontalScrollBarCache.Set(HorizontalScrollBar());
    }

    void Table::ClickHandler(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }

    void Table::updateVerticalScrollBar()
    {
        auto const viewportHeight = getViewportHeight();

        if (viewportHeight <= 0)
            return hideVerticalScrollBar();

		auto const totalHeight = m_data.Count() * TableConstants::RowHeight;
		auto const maxScroll = (std::max)(0.f, totalHeight - viewportHeight);

        if (maxScroll <= 0)
            return hideVerticalScrollBar();

        m_verticalScrollBarCache.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        m_verticalScrollBarCache.Maximum(maxScroll);
        m_verticalScrollBarCache.ViewportSize(viewportHeight);
        m_verticalScrollBarCache.LargeChange(viewportHeight);
        m_verticalScrollBarCache.SmallChange(TableConstants::RowHeight);
        m_isUpdatingVerticalScrollBarInCode = true;
        m_verticalScrollBarCache.Value(m_scrollOffsetY);
        m_isUpdatingVerticalScrollBarInCode = false;
    }

    void Table::updateHorizontalScrollBar()
    {
		auto const viewportWidth = getViewportWidth();

		if (viewportWidth <= 0)
            return hideHorizontalScrollBar();

        auto const totalWidth = std::accumulate(m_columnWidths.begin(), m_columnWidths.begin() + std::size(TableTestData::Columns), 0.f);
        auto const maxScroll = (std::max)(0.f, totalWidth - viewportWidth);
		if (maxScroll <= 0)
            return hideHorizontalScrollBar();

        m_horizontalScrollBarCache.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        m_horizontalScrollBarCache.Maximum(maxScroll);
        m_horizontalScrollBarCache.ViewportSize(viewportWidth);
        m_horizontalScrollBarCache.LargeChange(viewportWidth);
        m_horizontalScrollBarCache.SmallChange(TableConstants::ColumnWidth);
        m_isUpdatingHorizontalScrollBarInCode = true;
        m_horizontalScrollBarCache.Value(m_scrollOffsetX);
        m_isUpdatingHorizontalScrollBarInCode = false;
    }

    void Table::hideVerticalScrollBar()
    {
        m_verticalScrollBarCache.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    void Table::hideHorizontalScrollBar()
    {
        m_horizontalScrollBarCache.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    void Table::stopSmoothScroll()
    {
        m_isScrolling = false;
        m_scrollEvent.notify_one();
    }

    void Table::startSmoothScroll(float targetY)
    {
        m_isScrolling = true;
		m_smoothScrollTargetY = targetY;
        {
			std::lock_guard lock{ m_scrollMutex };
			m_scrollRequest.startY = m_scrollOffsetY;
			m_scrollRequest.endY = targetY;
			m_scrollRequest.startTime = std::chrono::steady_clock::now();
			m_scrollRequest.isPending = true;
        }
		m_scrollEvent.notify_one();
    }

    float Table::getViewportHeight() const
    {
        return m_swapChain.CurrentSize.Height - TableConstants::RowHeight; //minus header size
    }

    float Table::getViewportWidth() const
    {
        return m_swapChain.CurrentSize.Width;
    }

    void Table::scrollThreadProc(std::stop_token stopToken)
    {
        while (!stopToken.stop_requested())
        {
            ScrollRequest request;
            {
				std::unique_lock lock{ m_scrollMutex };
                m_scrollEvent.wait(lock, stopToken, [this] {return m_scrollRequest.isPending; });
                if (stopToken.stop_requested())
                    break;
				request = m_scrollRequest;
                m_scrollRequest.isPending = false;
            }

            timeBeginPeriod(1);
            while (!stopToken.stop_requested())
            {
				auto elapsed = std::chrono::steady_clock::now() - request.startTime;
                auto const progress = std::clamp(std::chrono::duration<double>(elapsed).count() / std::chrono::duration<double>(TableConstants::SmoothScrollDuration).count(), 0.0, 1.0);
                auto const eased = 1.0 - std::pow(1.0 - progress, 5.0);
				auto const done = progress >= 1.0;
				auto const newY = done? request.endY : request.startY + (request.endY - request.startY) * static_cast<float>(eased);
                m_dispatcherQueue.TryEnqueue([this, newY] {
                    if (!m_isScrolling)
                        return;

                    m_scrollOffsetY = newY;
                    draw();
                });

                bool pickedUpNewRequest = false;
                {
                    //sleep to avoid flooding dispatcher, and pick up any new request that arrived
                    std::unique_lock lock{ m_scrollMutex };
                    if (!done)
                        m_scrollEvent.wait_for(lock, std::chrono::milliseconds{ 4 }, [this] {return m_scrollRequest.isPending; });
                    if (m_scrollRequest.isPending)
                    {
                        request = m_scrollRequest;
                        m_scrollRequest.isPending = false;
                        pickedUpNewRequest = true;
                    }
                }

                if (done && !pickedUpNewRequest)
                {
                    m_isScrolling = false;
                    break;
                }
            }
            timeEndPeriod(1);
        }
    }

    int Table::getResizeColumnIndex(float x)
    {
        /*
            |---Column 1 ---|---Column 2 --|
                |-------------------------|
                        viewport
            |---| m_scrollOffsetX
        */
        
        float currentColumnEndX = -m_scrollOffsetX;
        for (int i = 0; i < m_data.Count(); ++i)
        {
            currentColumnEndX += m_columnWidths[i];
            if (std::abs(x - currentColumnEndX) <= TableConstants::ResizeHotZoneDelta)
                return i;
        }

        return TableConstants::ResizeColumnIndexNone;
    }

    D2D1_ROUNDED_RECT Table::getResizePillRect(int column)
    {
        auto const columnEndX = std::accumulate(m_columnWidths.begin(), m_columnWidths.begin() + column + 1, -m_scrollOffsetX);
        auto const rawColumnEndX = columnEndX * m_swapChain.Scale;
        auto const left = rawColumnEndX -TableConstants::ResizeHotZoneDelta * m_swapChain.Scale;

        return D2D1_ROUNDED_RECT
        {
            .rect = D2D_RECT_F
            {
                .left = left,
                .top = TableConstants::PillPadding * m_swapChain.Scale,
                .right = left + TableConstants::ResizeHotZoneDelta * m_swapChain.Scale,
                .bottom = (TableConstants::RowHeight - TableConstants::PillPadding) * m_swapChain.Scale
            },
            .radiusX = TableConstants::PillCornerRadius * m_swapChain.Scale,
            .radiusY = TableConstants::PillCornerRadius * m_swapChain.Scale
        };
    }

    void Table::draw()
    {
        if (m_swapChain.CurrentSize.Width <= 0 || m_swapChain.CurrentSize.Height <= 0)
            return;

        m_d2dContext->BeginDraw();
        m_d2dContext->Clear(D2D1::ColorF(0, 0));
        drawRows();
        drawHeader();
        m_d2dContext->EndDraw();
        DXGI_PRESENT_PARAMETERS presentParameters{};
        winrt::check_hresult(m_swapChain->Present1(0, DXGI_PRESENT_RESTART, &presentParameters));

        updateVerticalScrollBar();
        updateHorizontalScrollBar();
    }

    void Table::drawHeader()
    {
		auto const scale = m_swapChain.Scale;
		auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
		auto currentX = -m_scrollOffsetX * scale;
        for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
        {
            auto const rawColumnWidth = m_columnWidths[column] * scale;
            m_d2dContext->DrawTextW(
                TableTestData::Columns[column],
                static_cast<uint32_t>(std::wstring_view{ TableTestData::Columns[column] }.size()),
                m_headerTextFormat.get(),
                D2D1_RECT_F
                {
                    .left = currentX,
                    .top = 0,
                    .right = currentX + rawColumnWidth,
                    .bottom = 30 * scale
                },
                m_textBrush.get()
			);

			if (m_sortColumnIndex == column)
            {
                //draw sort indicator here
            }

            if (m_hoveredResizeColumn != TableConstants::ResizeColumnIndexNone)
            {
                auto const pillRect = getResizePillRect(m_hoveredResizeColumn);
                m_d2dContext->FillRoundedRectangle(&pillRect, m_pillBrush.get());
            }

            D2DPrimitiveHelper::DrawVerticalLine(
                m_d2dContext.get(),
                currentX + rawColumnWidth - 1,
                4 * scale,
                (4 + TableConstants::HeaderFontSize) * scale,
                m_textBrush.get()
            );
            currentX += rawColumnWidth;
        }
    }

    void Table::drawRows()
    {
		auto const rawRowHeight = TableConstants::RowHeight * m_swapChain.Scale;

        int const first = (std::max)(0, static_cast<int>(m_scrollOffsetY / rawRowHeight));
        int const last = (std::min)(m_data.Count() - 1, static_cast<int>((m_scrollOffsetY + m_swapChain.CurrentSize.Height * m_swapChain.Scale) / rawRowHeight));
        for (int row = first; row <= last; ++row)
        {
            auto& rowData = m_data[row];
            auto const rowY = (row + 1) * rawRowHeight - m_scrollOffsetY;

            //draw background
            D2D1_ROUNDED_RECT const rect
            {
                .rect = D2D1::RectF(0, rowY, m_swapChain.CurrentSize.Width * m_swapChain.Scale, rowY + rawRowHeight),
                .radiusX = TableConstants::CornerRadius * m_swapChain.Scale,
                .radiusY = TableConstants::CornerRadius * m_swapChain.Scale
            };
            m_d2dContext->FillRoundedRectangle(
                &rect,
                (row % 2 == 0) ? m_backgroundBrush.get() : m_alternateBackgroundBrush.get()
            );

            //draw columns
            auto const scale = m_swapChain.Scale;
            auto currentX = -m_scrollOffsetX * scale;
            for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
            {
                auto const rawColumnWidth = m_columnWidths[column] * scale;
				auto const& header = m_data.Header()[column];
                auto const& columnData = rowData[column];
                auto const& layoutCache = m_textLayoutCache.GetOrCreate(row, column, columnData, rawColumnWidth, rawRowHeight);
                winrt::check_hresult(layoutCache->SetParagraphAlignment(header.VerticalAlignment));
                winrt::check_hresult(layoutCache->SetTextAlignment(header.HorizontalAlignment));
                m_d2dContext->DrawTextLayout(
                    D2D1::Point2F(currentX, rowY),
                    layoutCache,
                    m_textBrush.get()
				);
                currentX += rawColumnWidth;
            }

            //draw line
            D2DPrimitiveHelper::DrawHorizontalLine(
                m_d2dContext.get(),
                0,
                m_swapChain.CurrentSize.Width * m_swapChain.Scale,
                rowY + rawRowHeight,
                m_textBrush.get()
			);
        }
    }

    void Table::setCursor(winrt::Microsoft::UI::Input::InputSystemCursorShape cursorShape)
    {
        ProtectedCursor(winrt::Microsoft::UI::Input::InputSystemCursor::Create(cursorShape));
    }

    void Table::resetCursor()
    {
        ProtectedCursor(nullptr);
    }

    void Table::SwapChainPanel_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
    {
        m_swapChain.SizeChanged(*this, e);
		m_swapChain.SetTarget(m_d2dContext.get());
        draw();
    }

    void Table::VerticalScrollBar_ValueChanged(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (m_isUpdatingVerticalScrollBarInCode)
            return;

        if (m_isScrolling)
            stopSmoothScroll();

		m_scrollOffsetY = static_cast<float>(e.NewValue());
        draw();
    }

    void Table::SwapChainPanel_PointerWheelChanged(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
		auto const currentPoint = e.GetCurrentPoint(*this);
		auto const wheelDelta = -currentPoint.Properties().MouseWheelDelta(); //the MouseWheelDelta is positive when scrolling up, but we want to scroll up when the wheel delta is negative, so we negate it here
        
        constexpr static auto numWheelStepRow = 3;
		auto const wheelStepY = TableConstants::RowHeight * numWheelStepRow; //one wheel step scrolls 3 rows
        
        constexpr static auto wheelStepDelta = 120;
        auto const scrollY = wheelDelta / wheelStepDelta * wheelStepY; //number of steps of wheel * step Y 
        
        auto const baseY = m_isScrolling ? m_smoothScrollTargetY : m_scrollOffsetY;
		auto const maxY = m_data.Count() * TableConstants::RowHeight - getViewportHeight();
        if (maxY >= 0)
        {
            auto const targetY = std::clamp(baseY + scrollY, 0.f, maxY);
            startSmoothScroll(targetY);
        }
        e.Handled(true);
    }


    void Table::HorizontalScrollBar_ValueChanged(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (m_isUpdatingHorizontalScrollBarInCode)
            return;

        m_scrollOffsetX = static_cast<float>(e.NewValue());
        draw();
    }

    void Table::SwapChainPanel_PointerMoved(
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto const currentPoint = e.GetCurrentPoint(*this);
        auto const [x, y] = currentPoint.Position();

        if (y <= TableConstants::RowHeight)
        {
            //resizing
            if (m_resizeRequest)
            {
                /*
                        |-----Column-----|
                                       |-|-|   resize hotzone
                                         m_resizeStartX
                                       |<->| resize hot-zone

                    After resizing
                        |-----Column-----|---|
                                         m_resizeStartX
                                         |---| delta = x - m_resizeStartX
                        |<------------------>|
                                         m_resizeStartWidth + delta
                */

                auto const delta = x - m_resizeRequest.m_resizeStartX;
                auto const newColumnWidth = (std::max)(TableConstants::MinColumnWidth, m_resizeRequest.m_resizeStartWidth + delta);
                m_columnWidths[m_resizeRequest.m_resizeColumnIndex] = newColumnWidth;
                draw();
                return;
            }

            //is inside resize-hotzone
            if (auto const resizeColumnIndex = getResizeColumnIndex(x); resizeColumnIndex != m_hoveredResizeColumn)
            {
                m_hoveredResizeColumn = resizeColumnIndex;
                if (resizeColumnIndex != TableConstants::ResizeColumnIndexNone)
                    setCursor(winrt::Microsoft::UI::Input::InputSystemCursorShape::SizeWestEast);
                else
                    resetCursor();
                draw();
                return;
            }

            return;
        }

        //not in header row
        if (m_hoveredResizeColumn != TableConstants::ResizeColumnIndexNone)
        {
            m_hoveredResizeColumn = TableConstants::ResizeColumnIndexNone;
            resetCursor();
            draw();
        }
    }


    void Table::SwapChainPanel_PointerPressed(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto const currentPoint = e.GetCurrentPoint(*this);
        auto const [x, y] = currentPoint.Position();

        //is resize column
        if (y >= TableConstants::RowHeight)
            return;

        //calculate resize column index
        auto const resizeColumnIndex = getResizeColumnIndex(x);
        if (resizeColumnIndex == TableConstants::ResizeColumnIndexNone)
            return;
        m_resizeRequest = true;
        m_resizeRequest.m_resizeColumnIndex = resizeColumnIndex;
        m_resizeRequest.m_resizeStartX = x;
        m_resizeRequest.m_resizeStartWidth = m_columnWidths[resizeColumnIndex];
        return;
    }

    void Table::SwapChainPanel_PointerReleased(
        winrt::Windows::Foundation::IInspectable const&, 
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        m_resizeRequest = false;
    }

}
