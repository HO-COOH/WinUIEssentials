#include "pch.h"
#include "Table.h"
#if __has_include("Table.g.cpp")
#include "Table.g.cpp"
#endif
#include "TableConstants.hpp"
#include <wil/resource.h>
#include "D2DConvert.hpp"

namespace winrt::PackageRoot::implementation
{
    void Table::EnsureDependencyProperties()
    {
        if (s_headerForegroundProperty) return;

        s_headerForegroundProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HeaderForeground",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onHeaderForegroundChanged }
        );
        s_contentForegroundProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"ContentForeground",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onContentForegroundChanged }
        );
        s_headerBackgroundProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HeaderBackground",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onHeaderBackgroundChanged }
        );
        s_headerFontSizeProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HeaderFontSize",
            winrt::xaml_typename<float>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onHeaderFontSizeChanged }
        );
        s_contentPaddingProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"ContentPadding",
            winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::Thickness>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata
            { 
                winrt::box_value(TableProperty::DefaultContentPadding), 
                &Table::onContentPaddingChanged
            }
        );
        s_headerFontWeightProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HeaderFontWeight",
            winrt::xaml_typename<winrt::Windows::UI::Text::FontWeight>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata
            {
                winrt::box_value(winrt::Windows::UI::Text::FontWeights::Normal()),
                &Table::onHeaderFontWeightChanged
            }
        );
        s_contentFontSizeProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"ContentFontSize",
            winrt::xaml_typename<float>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata
            {
                winrt::box_value(14.f),
                &Table::onContentFontSizeChanged
            }
        );
        s_fontFamilyProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"FontFamily",
            winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::Media::FontFamily>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onFontFamilyChanged }
        );
        s_horizontalLineColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HorizontalLineColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onHorizontalLineColorChanged }
        );
        s_verticalLineColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"VerticalLineColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onVerticalLineColorChanged }
        );
        s_contentFontWeightProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"ContentFontWeight",
            winrt::xaml_typename<winrt::Windows::UI::Text::FontWeight>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata
            {
                winrt::box_value(winrt::Windows::UI::Text::FontWeights::Normal()),
                &Table::onContentFontWeightChanged
            }
        );
    }

    Table::Table()
    {
        InitializeComponent();
        m_data.InitializeForTheme(ActualTheme());
        m_overlayManager.OnInitializedComponent();

        //get ui elements
        m_verticalScrollBarCache.Set(VerticalScrollBar());
        m_horizontalScrollBarCache.Set(HorizontalScrollBar());

#if defined Build_WinUIPackage
        m_fpsTimer = m_d2dContent.m_dispatcher.CreateTimer();
#endif
        m_fpsTimer.Tick([lastTick = std::chrono::steady_clock::now(), this](auto&&...) mutable {
            auto frames = m_d2dContent.Frames.exchange(0, std::memory_order_relaxed);
            auto const seconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - std::exchange(lastTick, std::chrono::steady_clock::now())).count();
            m_fps = frames / (seconds / 1000.f);
            raisePropertyChange(L"Fps");
        });
        m_fpsTimer.Interval(std::chrono::seconds{ 1 });
        m_fpsTimer.Start();
    }

    void Table::Table_Unloaded(winrt::Windows::Foundation::IInspectable const&, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
    {
        m_fpsTimer.Stop();
        m_d2dContent.Stop();
        m_d2dContent.DetachSwapChain(*this);
    }

    void Table::Table_ActualThemeChanged(winrt::WinUINamespace::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const&)
    {
        auto const unset = winrt::WinUINamespace::UI::Xaml::DependencyProperty::UnsetValue();
        auto const headerForegroundSet = ReadLocalValue(s_headerForegroundProperty) != unset;
        auto const contentForegroundSet = ReadLocalValue(s_contentForegroundProperty) != unset;
        auto const headerBackgroundSet = ReadLocalValue(s_headerBackgroundProperty) != unset;
        m_sharedData.Update([headerForegroundSet, contentForegroundSet, headerBackgroundSet, theme = ActualTheme()](TableProperty& data)
        {
            if (theme == winrt::WinUINamespace::UI::Xaml::ElementTheme::Light)
            {
                if (!headerForegroundSet)
                    data.m_headerForeground = TableProperty::DefaultHeaderForegroundLight;
                if (!contentForegroundSet)
                    data.m_contentForeground = TableProperty::DefaultContentForegroundLight;
            }
            else
            {
                if (!headerForegroundSet)
                    data.m_headerForeground = TableProperty::DefaultHeaderForegroundDark;
                if (!contentForegroundSet)
                    data.m_contentForeground = TableProperty::DefaultContentForegroundDark;
            }
        });
        
        if (!headerForegroundSet && !contentForegroundSet && !headerBackgroundSet)
            requestDraw(true);
    }

    void Table::requestDraw(bool redraw)
    {
        m_d2dContent.RequestDraw(redraw ? 
            (FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty) : 
            0
        );
        m_d2dContent.m_dispatcher.TryEnqueue([this] { updateScrollBars(); });
    }

    void Table::updateVerticalScrollBar(float scrollOffsetY)
    {
        if (m_isUpdatingVerticalScrollBarInCode || !m_verticalScrollBarCache)
            return;
        m_isUpdatingVerticalScrollBarInCode = true;
        auto reset = wil::scope_exit([this] { m_isUpdatingVerticalScrollBarInCode = false; });

        auto const viewportHeight = m_d2dContent.GetViewportHeight();

        if (viewportHeight <= 0)
            return hideVerticalScrollBar();

        auto const totalHeight = m_d2dContent.DataCount() * TableConstants::RowHeight;
        auto const maxScroll = (std::max)(0.f, totalHeight - viewportHeight);

        if (maxScroll <= 0)
            return hideVerticalScrollBar();

        m_verticalScrollBarCache.Visibility(winrt::WinUINamespace::UI::Xaml::Visibility::Visible);
        m_verticalScrollBarCache.Maximum(maxScroll);
        m_verticalScrollBarCache.ViewportSize(viewportHeight);
        m_verticalScrollBarCache.LargeChange(viewportHeight);
        m_verticalScrollBarCache.SmallChange(TableConstants::RowHeight);
        m_verticalScrollBarCache.Value(scrollOffsetY);
    }

    int Table::Fps()
    {
        return static_cast<int>(m_fps);
    }

    winrt::Windows::UI::Color Table::HeaderForeground()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(HeaderForegroundProperty()));
    }

    void Table::HeaderForeground(winrt::Windows::UI::Color const& value)
    {
        SetValue(HeaderForegroundProperty(), winrt::box_value(value));
    }

    winrt::Windows::UI::Color Table::ContentForeground()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(s_contentForegroundProperty));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::HeaderForegroundProperty()
    {
        return s_headerForegroundProperty;
    }

    void Table::ContentForeground(winrt::Windows::UI::Color const& value)
    {
        SetValue(s_contentForegroundProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::ContentForegroundProperty()
    {
        return s_contentForegroundProperty;
    }

    winrt::Windows::UI::Color Table::HeaderBackground()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(s_headerBackgroundProperty);
    }

    void Table::HeaderBackground(winrt::Windows::UI::Color const& value)
    {
        SetValue(s_headerBackgroundProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::HeaderBackgroundProperty()
    {
        return s_headerBackgroundProperty;
    }

    float Table::HeaderFontSize()
    {
        return winrt::unbox_value<float>(GetValue(HeaderFontSizeProperty()));
    }

    void Table::HeaderFontSize(float value)
    {
        SetValue(HeaderFontSizeProperty(), winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::HeaderFontSizeProperty()
    {
        return s_headerFontSizeProperty;
    }

    winrt::WinUINamespace::UI::Xaml::Thickness Table::ContentPadding()
    {
        return winrt::unbox_value<winrt::WinUINamespace::UI::Xaml::Thickness>(GetValue(ContentPaddingProperty()));
    }

    void Table::ContentPadding(winrt::WinUINamespace::UI::Xaml::Thickness const& value)
    {
        SetValue(ContentPaddingProperty(), winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::ContentPaddingProperty()
    {
        return s_contentPaddingProperty;
    }

    winrt::Windows::UI::Text::FontWeight Table::HeaderFontWeight()
    {
        return GetValue(s_headerFontWeightProperty).as<winrt::Windows::UI::Text::FontWeight>();
    }

    void Table::HeaderFontWeight(winrt::Windows::UI::Text::FontWeight const& value)
    {
        SetValue(s_headerFontWeightProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::HeaderFontWeightProperty()
    {
        return s_headerFontWeightProperty;
    }

    float Table::ContentFontSize()
    {
        return winrt::unbox_value<float>(GetValue(s_contentFontSizeProperty));
    }

    void Table::ContentFontSize(float value)
    {
        SetValue(s_contentFontSizeProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::ContentFontSizeProperty()
    {
        return s_contentFontSizeProperty;
    }

    winrt::WinUINamespace::UI::Xaml::Media::FontFamily Table::FontFamily()
    {
        return GetValue(s_fontFamilyProperty).as<winrt::WinUINamespace::UI::Xaml::Media::FontFamily>();
    }

    void Table::FontFamily(winrt::WinUINamespace::UI::Xaml::Media::FontFamily const& value)
    {
        SetValue(s_fontFamilyProperty, value);
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::FontFamilyProperty()
    {
        return s_fontFamilyProperty;
    }

    winrt::Windows::UI::Text::FontWeight Table::ContentFontWeight()
    {
        return winrt::unbox_value<winrt::Windows::UI::Text::FontWeight>(s_contentFontWeightProperty);
    }

    void Table::ContentFontWeight(winrt::Windows::UI::Text::FontWeight const& value)
    {
        SetValue(s_contentFontWeightProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::ContentFontWeightProperty()
    {
        return s_contentFontWeightProperty;
    }

    winrt::Windows::UI::Color Table::HorizontalLineColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(s_horizontalLineColorProperty);
    }

    void Table::HorizontalLineColor(winrt::Windows::UI::Color const& value)
    {
        SetValue(s_horizontalLineColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::HorizontalLineColorProperty()
    {
        return s_horizontalLineColorProperty;
    }

    winrt::Windows::UI::Color Table::VerticalLineColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(s_verticalLineColorProperty);
    }

    void Table::VerticalLineColor(winrt::Windows::UI::Color const& value)
    {
        SetValue(s_verticalLineColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::VerticalLineColorProperty()
    {
        return s_verticalLineColorProperty;
    }

    winrt::PackageRoot::TableColumnCollection Table::Columns()
    {
        return *m_columns;
    }

    winrt::PackageRoot::ITableData Table::Data()
    {
        return m_tableData;
    }

    void Table::Data(winrt::PackageRoot::ITableData const& data)
    {
        m_tableData = data;
        m_d2dContent.m_textLayoutCache.OnTableDataSet(&m_tableData);

        m_updateRowDataRevoker = m_tableData.UpdateRowData(winrt::auto_revoke,
            [weak = get_weak()](winrt::Windows::Foundation::IInspectable const&, winrt::PackageRoot::UpdateRowDataEventArgs const& arg)
            {
                auto strong = weak.get();
                if (!strong)
                    return;
                auto& cache = strong->m_d2dContent.m_textLayoutCache;
                for (int r = arg.StartRow; r <= arg.EndRow; ++r)
                    cache.InvalidateRow(r);
                strong->m_overlayManager.InvalidateRows(arg.StartRow, arg.EndRow);
                if (strong->m_isLoaded)
                    strong->requestDraw(true);
            }
        );

        if (!m_isLoaded)
            return;
        m_d2dContent.m_textLayoutCache.Invalidate();
        requestDraw(true);
    }

    void Table::updateHorizontalScrollBar(float scrollOffsetX)
    {
        if (m_isUpdatingHorizontalScrollBarInCode || !m_horizontalScrollBarCache)
            return;
        m_isUpdatingHorizontalScrollBarInCode = true;
        auto reset = wil::scope_exit([this] { m_isUpdatingHorizontalScrollBarInCode = false; });

        auto const viewportWidth = m_d2dContent.GetViewportWidth();

        if (viewportWidth <= 0)
            return hideHorizontalScrollBar();

        auto const totalWidth = m_d2dContent.TotalContentWidth();
        auto const maxScroll = (std::max)(0.f, totalWidth - viewportWidth);
        if (maxScroll <= 0)
            return hideHorizontalScrollBar();

        m_horizontalScrollBarCache.Visibility(winrt::WinUINamespace::UI::Xaml::Visibility::Visible);
        m_horizontalScrollBarCache.Maximum(maxScroll);
        m_horizontalScrollBarCache.ViewportSize(viewportWidth);
        m_horizontalScrollBarCache.LargeChange(viewportWidth);
        m_horizontalScrollBarCache.SmallChange(TableConstants::ColumnWidth);
        m_horizontalScrollBarCache.Value(scrollOffsetX);
    }

    void Table::updateScrollBars()
    {
        updateVerticalScrollBar(m_d2dContent.ScrollOffsetY());
        updateHorizontalScrollBar(m_d2dContent.ScrollOffsetX());
    }

    void Table::hideVerticalScrollBar()
    {
        m_verticalScrollBarCache.Visibility(winrt::WinUINamespace::UI::Xaml::Visibility::Collapsed);
    }

    void Table::hideHorizontalScrollBar()
    {
        m_horizontalScrollBarCache.Visibility(winrt::WinUINamespace::UI::Xaml::Visibility::Collapsed);
    }

    void Table::SwapChainPanel_SizeChanged(winrt::Windows::Foundation::IInspectable const&, winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& e)
    {
        m_d2dContent.SizeChanged(*this, e);
        m_d2dContent.m_dispatcher.TryEnqueue([this] { updateScrollBars(); });
    }

    void Table::SwapChainPanel_CompositionScaleChanged(winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const&, winrt::Windows::Foundation::IInspectable const&)
    {
        m_d2dContent.CompositionScaleChanged(*this);
    }

    void Table::VerticalScrollBar_ValueChanged(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (m_isUpdatingVerticalScrollBarInCode)
            return;

        if (m_d2dContent.IsScrolling())
            m_d2dContent.StopSmoothScroll();

        auto const value = static_cast<float>(e.NewValue());
		m_overlayManager.OnScrollYChanged(value);
        m_d2dContent.SetScrollOffsetY(value);
        requestDraw();
    }

    void Table::SwapChainPanel_PointerWheelChanged(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        if (m_overlayManager.IsEditing())
            return;

        auto const currentPoint = e.GetCurrentPoint(*this);
        auto const wheelDelta = -currentPoint.Properties().MouseWheelDelta(); //the MouseWheelDelta is positive when scrolling up, but we want to scroll up when the wheel delta is negative, so we negate it here

        constexpr static auto numWheelStepRow = 3;
        auto const wheelStepY = TableConstants::RowHeight * numWheelStepRow; //one wheel step scrolls 3 rows

        constexpr static auto wheelStepDelta = 120;
        auto const scrollY = wheelDelta / wheelStepDelta * wheelStepY; //(number of steps of wheel) * (step Y)

        auto const maxScrollY = m_d2dContent.DataCount() * TableConstants::RowHeight - m_d2dContent.GetViewportHeight();
        if (maxScrollY > 0)
        {
            auto const baseY = m_d2dContent.IsScrolling() ? m_d2dContent.SmoothScrollTargetY() : m_d2dContent.ScrollOffsetY();
            auto const targetY = std::clamp(baseY + scrollY, 0.f, maxScrollY);
            m_overlayManager.OnMouseScroll(targetY);
            m_d2dContent.StartSmoothScrollY(targetY);
        }
        e.Handled(true);
    }

    void Table::HorizontalScrollBar_ValueChanged(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (m_isUpdatingHorizontalScrollBarInCode)
            return;

        auto const value = static_cast<float>(e.NewValue());
		m_overlayManager.OnScrollXChanged(value);
        m_d2dContent.SetScrollOffsetX(value);
        requestDraw();
    }

    void Table::SwapChainPanel_PointerMoved(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto const currentPoint = e.GetCurrentPoint(*this);
        auto const [x, y] = currentPoint.Position();

        //resizing should continue even after the cursor leaves header row
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
            m_d2dContent.m_columnWidthManager.Set(m_resizeRequest.m_resizeColumnIndex, newColumnWidth);
            m_overlayManager.OnColumnResized(m_resizeRequest.m_resizeColumnIndex);
            requestDraw(true);
            return;
        }

        if (y <= TableConstants::RowHeight)
        {
            //clear row hover while in header
            m_d2dContent.SetHover(-1.0f);

            //is inside resize-hotzone
            if (auto const resizeColumnIndex = m_d2dContent.GetResizeColumnIndex(x); m_d2dContent.SetHoveredResizeColumn(resizeColumnIndex))
            {
                if (resizeColumnIndex != TableConstants::ResizeColumnIndexNone)
                {
#if defined Build_WinUIPackage
                    setCursor(winrt::WinUINamespace::UI::Input::InputSystemCursorShape::SizeWestEast);
#else
                    setCursor(winrt::Windows::UI::Core::CoreCursorType::SizeWestEast);
#endif
                }
                else
                    resetCursor();
            }
            return;
        }

        //not in header row
        if (m_d2dContent.SetHoveredResizeColumn(TableConstants::ResizeColumnIndexNone))
            resetCursor();
        m_d2dContent.SetHover(y);
    }

    void Table::SwapChainPanel_PointerPressed(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto const currentPoint = e.GetCurrentPoint(*this);
        auto const [x, y] = currentPoint.Position();

        //click outside the editor dismisses it. Clicks on the editor itself
        //don't bubble up to SwapChainPanel because the inner control handles them.
        if (m_overlayManager.IsEditing())
        {
            m_overlayManager.EndEdit();
            return;
        }

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
        m_resizeRequest.m_resizeStartWidth = m_d2dContent.m_columnWidthManager.Get(resizeColumnIndex);
        return;
    }

    void Table::SwapChainPanel_PointerReleased(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const&)
    {
        m_resizeRequest = false;
    }

    void Table::SwapChainPanel_DoubleTapped(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& e)
    {
        auto [x, y] = e.GetPosition(*this);

        //ignore double-tap on the header
        if (y < TableConstants::HeaderHeight)
            return;

        //hit-test column
        auto& widthManager = m_d2dContent.m_columnWidthManager;
        auto const numColumns = static_cast<int>(widthManager.NumColumns());
        float columnLeft = -m_d2dContent.ScrollOffsetX();
        int columnIndex = -1;
        for (int i = 0; i < numColumns; ++i)
        {
            float const width = widthManager.Get(i);
            if (x >= columnLeft && x < columnLeft + width)
            {
                columnIndex = i;
                break;
            }
            columnLeft += width;
        }
        if (columnIndex < 0)
            return;

        //hit-test row
        int const row = static_cast<int>((y - TableConstants::HeaderHeight + m_d2dContent.ScrollOffsetY()) / TableConstants::RowHeight);
        if (row < 0 || row >= m_d2dContent.DataCount())
            return;

        m_overlayManager.BeginEdit(row, columnIndex);
        e.Handled(true);
    }

    void Table::Table_Loaded(winrt::Windows::Foundation::IInspectable const&, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
    {
        m_isLoaded = true;
    }

    void Table::onHeaderForegroundChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue());
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_headerForeground = D2DConvert::ToD2DColor(value); });
        else
            self->m_data.m_headerForeground = D2DConvert::ToD2DColor(value);
    }

    void Table::onContentForegroundChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_contentForeground = value; });
        else
            self->m_data.m_contentForeground = value;
    }

    void Table::onHeaderBackgroundChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_headerBackground = value; });
        else
            self->m_data.m_headerBackground = value;
    }

    void Table::onHeaderFontSizeChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = winrt::unbox_value<float>(e.NewValue());
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_headerFontSize = value; });
        else
            self->m_data.m_headerFontSize = value;
    }

    void Table::onContentPaddingChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = winrt::unbox_value<winrt::WinUINamespace::UI::Xaml::Thickness>(e.NewValue());
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_contentPadding = value; });
        else
            self->m_data.m_contentPadding = value;
    }

    void Table::onHeaderFontWeightChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToDWriteFontWeight(winrt::unbox_value<winrt::Windows::UI::Text::FontWeight>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_headerFontWeight = value; });
        else
            self->m_data.m_headerFontWeight = value;
    }

    void Table::onContentFontSizeChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = winrt::unbox_value<float>(e.NewValue());
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_contentFontSize = value; });
        else
            self->m_data.m_contentFontSize = value;
    }

    void Table::onFontFamilyChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
    }

    void Table::onHorizontalLineColorChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
		auto self = GetSelf(d);
		auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_horizontalLineColor = value; });
        else
			self->m_data.m_horizontalLineColor = value;
    }

    void Table::onVerticalLineColorChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
		auto self = GetSelf(d);
		auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_verticalLineColor = value; });
        else
            self->m_data.m_verticalLineColor = value;
    }

    void Table::onContentFontWeightChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToDWriteFontWeight(winrt::unbox_value<winrt::Windows::UI::Text::FontWeight>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_contentFontWeight = value; });
        else
            self->m_data.m_contentFontWeight = value;
    }

    void Table::SwapChainPanel_PointerExited(winrt::Windows::Foundation::IInspectable const&, winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const&)
    {
        m_d2dContent.SetHover(-1.0);
    }
}
