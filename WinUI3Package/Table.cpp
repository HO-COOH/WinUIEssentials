#include "pch.h"
#include "Table.h"
#if __has_include("Table.g.cpp")
#include "Table.g.cpp"
#endif
#include "TableConstants.hpp"
#include "D2DPrimitiveHelper.h"
#include <winrt/Microsoft.UI.Input.h>
#include <timeapi.h>

namespace winrt::WinUI3Package::implementation
{
    Table::Table() : m_smoothScrollThread{ [this](std::stop_token st) {scrollThreadProc(st); } }
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

        //get ui elements
        m_verticalScrollBar = VerticalScrollBar();
		m_horizontalScrollBar = HorizontalScrollBar();
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

		m_verticalScrollBar.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		m_verticalScrollBar.Maximum(maxScroll);
		m_verticalScrollBar.ViewportSize(viewportHeight);
		m_verticalScrollBar.LargeChange(viewportHeight);
		m_verticalScrollBar.SmallChange(TableConstants::RowHeight);
		m_isUpdatingVerticalScrollBarInCode = true;
		m_verticalScrollBar.Value(m_scrollOffsetY);
		m_isUpdatingVerticalScrollBarInCode = false;
    }

    void Table::updateHorizontalScrollBar()
    {
		auto const viewportWidth = getViewportWidth();

		if (viewportWidth <= 0)
            return hideHorizontalScrollBar();

        auto const totalWidth = std::size(TableTestData::Columns) * TableConstants::ColumnWidth;
        auto const maxScroll = (std::max)(0.f, totalWidth - viewportWidth);
		if (maxScroll <= 0)
            return hideHorizontalScrollBar();

		m_horizontalScrollBar.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		m_horizontalScrollBar.Maximum(maxScroll);
		m_horizontalScrollBar.ViewportSize(viewportWidth);
		m_horizontalScrollBar.LargeChange(viewportWidth);
		m_horizontalScrollBar.SmallChange(TableConstants::ColumnWidth);
		m_isUpdatingHorizontalScrollBarInCode = true;
		m_horizontalScrollBar.Value(m_scrollOffsetX);
        m_isUpdatingHorizontalScrollBarInCode = false;
    }

    void Table::hideVerticalScrollBar()
    {
		m_verticalScrollBar.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    void Table::hideHorizontalScrollBar()
    {
		m_horizontalScrollBar.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
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
                m_scrollEvent.wait(lock, [this] {return m_scrollRequest.isPending; });
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
                if (done)
                {
                    m_isScrolling = false;
                    break;
                }

                {
                    //sleep to avoid flooding dispatcher
                    std::unique_lock lock{ m_scrollMutex };
                    m_scrollEvent.wait_for(lock, std::chrono::milliseconds{ 4 }, [this] {return m_scrollRequest.isPending; });
                }
            }
            timeEndPeriod(1);
        }
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
		auto const rawWidth = m_swapChain.CurrentSize.Width * m_swapChain.Scale;
		auto currentX = -m_scrollOffsetX;
        for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
        {
            if (currentX >= rawWidth)
                break;

            m_d2dContext->DrawTextW(
                TableTestData::Columns[column],
                static_cast<uint32_t>(std::wstring_view{ TableTestData::Columns[column] }.size()),
                m_headerTextFormat.get(),
                D2D1_RECT_F
                { 
                    .left = currentX, 
                    .top = 0, 
                    .right = currentX + TableConstants::ColumnWidth, 
                    .bottom = 30 
                },
                m_textBrush.get()
			);

			if (m_sortColumnIndex == column)
            {
                
            }

            D2DPrimitiveHelper::DrawVerticalLine(
                m_d2dContext.get(),
                currentX + TableConstants::ColumnWidth - 1,
                4,
                4 + TableConstants::HeaderFontSize,
                m_textBrush.get()
            );
            currentX += TableConstants::ColumnWidth;
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
            for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
            {
				auto const& header = m_data.Header()[column];
                auto const& columnData = rowData[column];
                auto const& layoutCache = m_textLayoutCache.GetOrCreate(row, column, columnData, 200, rawRowHeight);
                winrt::check_hresult(layoutCache->SetParagraphAlignment(header.VerticalAlignment));
                winrt::check_hresult(layoutCache->SetTextAlignment(header.HorizontalAlignment));
                m_d2dContext->DrawTextLayout(
                    D2D1::Point2F(column * 200.f - m_scrollOffsetX, rowY),
                    layoutCache,
                    m_textBrush.get()
				);
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
		auto const pointerPoint = e.GetCurrentPoint(*this);
		auto const wheelDelta = -pointerPoint.Properties().MouseWheelDelta(); //the MouseWheelDelta is positive when scrolling up, but we want to scroll up when the wheel delta is negative, so we negate it here
        
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
        winrt::Windows::Foundation::IInspectable const& sender, 
        winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (m_isUpdatingHorizontalScrollBarInCode)
            return;

        m_scrollOffsetX = static_cast<float>(e.NewValue());
        draw();
    }

}
