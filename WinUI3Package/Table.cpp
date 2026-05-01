#include "pch.h"
#include "Table.h"
#if __has_include("Table.g.cpp")
#include "Table.g.cpp"
#endif
#include "TableConstants.hpp"
#include <winrt/Microsoft.UI.Input.h>

namespace winrt::WinUI3Package::implementation
{
    Table::Table()
    {
        InitializeComponent();

        //get ui elements
        m_verticalScrollBarCache.Set(VerticalScrollBar());
        m_horizontalScrollBarCache.Set(HorizontalScrollBar());

        m_d2dContent.Initialize(*this);
    }

    void Table::requestDraw()
    {
        m_d2dContent.RequestDraw();
        updateScrollBars();
    }

    void Table::ClickHandler(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }

    void Table::updateVerticalScrollBar(float scrollOffsetY)
    {
        auto const viewportHeight = m_d2dContent.GetViewportHeight();

        if (viewportHeight <= 0)
            return hideVerticalScrollBar();

        auto const totalHeight = m_d2dContent.DataCount() * TableConstants::RowHeight;
        auto const maxScroll = (std::max)(0.f, totalHeight - viewportHeight);

        if (maxScroll <= 0)
            return hideVerticalScrollBar();

        m_verticalScrollBarCache.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        m_verticalScrollBarCache.Maximum(maxScroll);
        m_verticalScrollBarCache.ViewportSize(viewportHeight);
        m_verticalScrollBarCache.LargeChange(viewportHeight);
        m_verticalScrollBarCache.SmallChange(TableConstants::RowHeight);
        m_isUpdatingVerticalScrollBarInCode = true;
        m_verticalScrollBarCache.Value(scrollOffsetY);
        m_isUpdatingVerticalScrollBarInCode = false;
    }

    void Table::updateHorizontalScrollBar(float scrollOffsetX)
    {
        auto const viewportWidth = m_d2dContent.GetViewportWidth();

        if (viewportWidth <= 0)
            return hideHorizontalScrollBar();

        auto const totalWidth = m_d2dContent.TotalContentWidth();
        auto const maxScroll = (std::max)(0.f, totalWidth - viewportWidth);
        if (maxScroll <= 0)
            return hideHorizontalScrollBar();

        m_horizontalScrollBarCache.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
        m_horizontalScrollBarCache.Maximum(maxScroll);
        m_horizontalScrollBarCache.ViewportSize(viewportWidth);
        m_horizontalScrollBarCache.LargeChange(viewportWidth);
        m_horizontalScrollBarCache.SmallChange(TableConstants::ColumnWidth);
        m_isUpdatingHorizontalScrollBarInCode = true;
        m_horizontalScrollBarCache.Value(scrollOffsetX);
        m_isUpdatingHorizontalScrollBarInCode = false;
    }

    void Table::updateScrollBars()
    {
        updateVerticalScrollBar(m_d2dContent.ScrollOffsetY());
        updateHorizontalScrollBar(m_d2dContent.ScrollOffsetX());
    }

    void Table::hideVerticalScrollBar()
    {
        m_verticalScrollBarCache.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    void Table::hideHorizontalScrollBar()
    {
        m_horizontalScrollBarCache.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    void Table::setCursor(winrt::Microsoft::UI::Input::InputSystemCursorShape cursorShape)
    {
        ProtectedCursor(winrt::Microsoft::UI::Input::InputSystemCursor::Create(cursorShape));
    }

    void Table::resetCursor()
    {
        ProtectedCursor(nullptr);
    }

    void Table::SwapChainPanel_SizeChanged(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
    {
        m_d2dContent.SizeChanged(*this, e);
        updateScrollBars();
    }

    void Table::SwapChainPanel_CompositionScaleChanged(winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel const&, winrt::Windows::Foundation::IInspectable const&)
    {
        m_d2dContent.CompositionScaleChanged(*this);
    }

    void Table::VerticalScrollBar_ValueChanged(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (m_isUpdatingVerticalScrollBarInCode)
            return;

        if (m_d2dContent.IsScrolling())
            m_d2dContent.StopSmoothScroll();

        m_d2dContent.SetScrollOffsetY(static_cast<float>(e.NewValue()));
        requestDraw();
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

        auto const baseY = m_d2dContent.IsScrolling() ? m_d2dContent.SmoothScrollTargetY() : m_d2dContent.ScrollOffsetY();
        auto const maxY = m_d2dContent.DataCount() * TableConstants::RowHeight - m_d2dContent.GetViewportHeight();
        if (maxY >= 0)
        {
            auto const targetY = std::clamp(baseY + scrollY, 0.f, maxY);
            m_d2dContent.StartSmoothScrollY(targetY);
        }
        e.Handled(true);
    }

    void Table::HorizontalScrollBar_ValueChanged(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (m_isUpdatingHorizontalScrollBarInCode)
            return;

        m_d2dContent.SetScrollOffsetX(static_cast<float>(e.NewValue()));
        requestDraw();
    }

    void Table::SwapChainPanel_PointerMoved(
        winrt::Windows::Foundation::IInspectable const&,
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
                m_d2dContent.SetColumnWidth(m_resizeRequest.m_resizeColumnIndex, newColumnWidth);
                requestDraw();
                return;
            }

            //is inside resize-hotzone
            if (auto const resizeColumnIndex = m_d2dContent.GetResizeColumnIndex(x); m_d2dContent.SetHoveredResizeColumn(resizeColumnIndex))
            {
                if (resizeColumnIndex != TableConstants::ResizeColumnIndexNone)
                    setCursor(winrt::Microsoft::UI::Input::InputSystemCursorShape::SizeWestEast);
                else
                    resetCursor();
                m_d2dContent.RequestDraw();
                return;
            }

            return;
        }

        //not in header row
        bool hoverNeedRedraw = false;
        if (m_d2dContent.SetHoveredResizeColumn(TableConstants::ResizeColumnIndexNone))
        {
            resetCursor();
            hoverNeedRedraw = true;
        }
        if (m_d2dContent.SetHover(y))
            hoverNeedRedraw = true;

        if (hoverNeedRedraw)
            m_d2dContent.RequestDraw();
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
        auto const resizeColumnIndex = m_d2dContent.GetResizeColumnIndex(x);
        if (resizeColumnIndex == TableConstants::ResizeColumnIndexNone)
            return;
        m_resizeRequest = true;
        m_resizeRequest.m_resizeColumnIndex = resizeColumnIndex;
        m_resizeRequest.m_resizeStartX = x;
        m_resizeRequest.m_resizeStartWidth = m_d2dContent.ColumnWidth(resizeColumnIndex);
        return;
    }

    void Table::SwapChainPanel_PointerReleased(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        m_resizeRequest = false;
    }


    void Table::SwapChainPanel_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        m_d2dContent.SetHover(-1.0);
        m_d2dContent.RequestDraw();
    }
}
