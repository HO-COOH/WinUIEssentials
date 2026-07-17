#include "pch.h"
#include "Table.h"
#if __has_include("Table.g.cpp")
#include "Table.g.cpp"
#endif
#include "TableConstants.hpp"
#include <wil/resource.h>
#include "D2DConvert.hpp"
#include "ContextMenuRequestedEventArgs.h"
#include <algorithm>
#include <numeric>
#include <vector>
#include "DefaultTableContextMenu.h"
#include "DefaultTableHeaderContextMenu.h"

//Best-effort string form of a cell for lexical comparison.
static inline winrt::hstring GetString(winrt::Windows::Foundation::IInspectable const& value)
{
    if (!value)
        return {};
    if (auto const str = value.try_as<winrt::hstring>())
        return *str;
    if (auto const pv = value.try_as<winrt::Windows::Foundation::IPropertyValue>(); pv && pv.Type() == winrt::Windows::Foundation::PropertyType::String)
        return pv.GetString();
    return {};
}

static inline std::partial_ordering compareObject(
    winrt::Windows::Foundation::IInspectable const& lhs,
    winrt::Windows::Foundation::IInspectable const& rhs)
{
    auto const lhsValue = lhs.as<winrt::Windows::Foundation::IPropertyValue>();
    auto const rhsValue = rhs.as<winrt::Windows::Foundation::IPropertyValue>();

    switch (lhsValue.Type())
    {
        case winrt::Windows::Foundation::PropertyType::Int16: return lhsValue.GetInt16() <=> rhsValue.GetInt16();
        case winrt::Windows::Foundation::PropertyType::Int32: return lhsValue.GetInt32() <=> rhsValue.GetInt32();
        case winrt::Windows::Foundation::PropertyType::Int64: return lhsValue.GetInt64() <=> rhsValue.GetInt64();
        case winrt::Windows::Foundation::PropertyType::UInt8: return lhsValue.GetUInt8() <=> rhsValue.GetUInt8();
        case winrt::Windows::Foundation::PropertyType::UInt16: return lhsValue.GetUInt16() <=> rhsValue.GetUInt16();
        case winrt::Windows::Foundation::PropertyType::UInt32: return lhsValue.GetUInt32() <=> rhsValue.GetUInt32();
        case winrt::Windows::Foundation::PropertyType::UInt64: return lhsValue.GetUInt64() <=> rhsValue.GetUInt64();
        case winrt::Windows::Foundation::PropertyType::Single: return lhsValue.GetSingle() <=> rhsValue.GetSingle();
        case winrt::Windows::Foundation::PropertyType::Double: return lhsValue.GetDouble() <=> rhsValue.GetDouble();
        case winrt::Windows::Foundation::PropertyType::Boolean: return lhsValue.GetBoolean() <=> rhsValue.GetBoolean();
        case winrt::Windows::Foundation::PropertyType::String:
            return std::wstring_view{ GetString(lhs) } <=> std::wstring_view{ GetString(rhs) };
        default:
            throw std::invalid_argument("Unsupported property type for comparison");
    }
}

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
		s_pointerOverBackgroundProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"PointerOverBackground",
			winrt::xaml_typename<winrt::Windows::UI::Color>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onPointerOverBackgroundChanged }
		);
        s_headerFontSizeProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HeaderFontSize",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onHeaderFontSizeChanged }
        );
        s_contentPaddingProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"ContentPadding",
            winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::Thickness>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onContentPaddingChanged }
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
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onContentFontSizeChanged }
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
        s_horizontalLineThicknessProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HorizontalLineThickness",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ winrt::box_value(1.0), &Table::onHorizontalLineThicknessChanged }
        );
        s_verticalLineColorProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"VerticalLineColor",
            winrt::xaml_typename<winrt::Windows::UI::Color>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onVerticalLineColorChanged }
        );
		s_verticalLineThicknessProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"VerticalLineThickness",
			winrt::xaml_typename<double>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ winrt::box_value(1.0), &Table::onVerticalLineThicknessChanged }
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
        s_headerFontStyleProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HeaderFontStyle",
            winrt::xaml_typename<winrt::Windows::UI::Text::FontStyle>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onHeaderFontStyleChanged }
        );
		s_contentFontStyleProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"ContentFontStyle",
			winrt::xaml_typename<winrt::Windows::UI::Text::FontStyle>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onContentFontStyleChanged }
		);
        s_headerFontStretchProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"HeaderFontStretch",
            winrt::xaml_typename<winrt::Windows::UI::Text::FontStretch>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onHeaderFontStretchChanged }
        );
		s_contentFontStretchProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"ContentFontStretch",
			winrt::xaml_typename<winrt::Windows::UI::Text::FontStretch>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onContentFontStretchChanged }
		);
		s_alternateRowColorsProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"AlternateRowColors",
			winrt::xaml_typename<winrt::Windows::Foundation::Collections::IVector<PackageRoot::TableAlternateRowColor>>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &Table::onAlternateRowColorsChanged }
		);
    }

    Table::Table()
    {
        InitializeComponent();
        m_tableProperty.InitializeForTheme(ActualTheme());
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
        m_sharedData.Update([headerForegroundSet, contentForegroundSet, theme = ActualTheme()](TableProperty& data)
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
        
        if (!headerForegroundSet || !contentForegroundSet)
            requestDraw(true);
    }

    void Table::SetSort(TableSortParameter sortParameter)
    {
        if (sortParameter.sortDirection == TableSortDirection::None)
            sortParameter.sortColumn = -1;

        if (m_sortContext.sortParameter == sortParameter)
            return;

        m_sortContext.sortParameter = sortParameter;
        m_sortContext.sortedIndices.clear();

        if (sortParameter.sortColumn >= 0 && m_tableData)
        {
            int const rowCount = m_tableData.RowCount();

            //The built-in TableRowDataSource keeps the cell objects in memory, so
            //we can read typed keys directly. An external ITableData only feeds us
            //rows through RowRequested, so fetch the whole set into the cache first
            //and compare the cached strings.
            if (!m_tableRowDataSource && rowCount > 0)
            {
                auto args = winrt::make_self<winrt::PackageRoot::implementation::RowRequestedEventArgs>(0, rowCount - 1, *this);
                m_tableData.RowRequested(*args);
            }

            auto& indices = m_sortContext.sortedIndices;
            indices.resize(rowCount);
            std::iota(indices.begin(), indices.end(), size_t{ 0 });

            m_tableRowDataSource ? sortObjectImpl(rowCount) : sortStringImpl(rowCount);
        }

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

    void Table::UpdateVerticalScrollBar(float scrollOffsetY)
    {
        if (m_isUpdatingVerticalScrollBarInCode || !m_verticalScrollBarCache)
            return;
        m_isUpdatingVerticalScrollBarInCode = true;
        auto reset = wil::scope_exit([this] { m_isUpdatingVerticalScrollBarInCode = false; });

        auto const viewportHeight = m_d2dContent.GetViewportHeight();

        if (viewportHeight <= 0)
            return hideVerticalScrollBar();

        auto const contentRowHeight = m_d2dContent.m_tableHeight.ContentRowHeight();
        auto const totalHeight = m_d2dContent.DataCount() * contentRowHeight;
        auto const maxScroll = (std::max)(0.f, totalHeight - viewportHeight);

        if (maxScroll <= 0)
            return hideVerticalScrollBar();

        m_verticalScrollBarCache.ViewportSize(viewportHeight);
        m_verticalScrollBarCache.Maximum(maxScroll);
        m_verticalScrollBarCache.LargeChange(viewportHeight);
        m_verticalScrollBarCache.SmallChange(contentRowHeight);
        m_verticalScrollBarCache.Value(scrollOffsetY);
        m_verticalScrollBarCache.Visibility(winrt::WinUINamespace::UI::Xaml::Visibility::Visible);
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

    winrt::Windows::UI::Color Table::PointerOverBackground()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(s_pointerOverBackgroundProperty);
    }

    void Table::PointerOverBackground(winrt::Windows::UI::Color const& value)
    {
		SetValue(s_pointerOverBackgroundProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty const& Table::PointerOverBackgroundProperty()
    {
        return s_pointerOverBackgroundProperty;
    }

    double Table::HeaderFontSize()
    {
        return winrt::unbox_value<double>(GetValue(HeaderFontSizeProperty()));
    }

    void Table::HeaderFontSize(double value)
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

    double Table::ContentFontSize()
    {
        return winrt::unbox_value<double>(GetValue(s_contentFontSizeProperty));
    }

    void Table::ContentFontSize(double value)
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

    winrt::Windows::UI::Text::FontStyle Table::HeaderFontStyle()
    {
		return winrt::unbox_value<winrt::Windows::UI::Text::FontStyle>(GetValue(s_headerFontStyleProperty));
    }

    void Table::HeaderFontStyle(winrt::Windows::UI::Text::FontStyle fontStyle)
    {
		SetValue(s_headerFontStyleProperty, winrt::box_value(fontStyle));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::HeaderFontStyleProperty()
    {
        return s_headerFontStyleProperty;
    }

    winrt::Windows::UI::Text::FontStyle Table::ContentFontStyle()
    {
		return winrt::unbox_value<winrt::Windows::UI::Text::FontStyle>(GetValue(s_contentFontStyleProperty));
    }

    void Table::ContentFontStyle(winrt::Windows::UI::Text::FontStyle fontStyle)
    {
        SetValue(s_contentFontStyleProperty, winrt::box_value(fontStyle));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::ContentFontStyleProperty()
    {
        return s_contentFontStyleProperty;
    }

    winrt::Windows::UI::Text::FontStretch Table::HeaderFontStretch()
    {
        return winrt::unbox_value<winrt::Windows::UI::Text::FontStretch>(GetValue(s_headerFontStretchProperty));
    }

    void Table::HeaderFontStretch(winrt::Windows::UI::Text::FontStretch fontStretch)
    {
        SetValue(s_headerFontStretchProperty, winrt::box_value(fontStretch));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::HeaderFontStretchProperty()
    {
        return s_headerFontStretchProperty;
    }

    winrt::Windows::UI::Text::FontStretch Table::ContentFontStretch()
    {
		return winrt::unbox_value<winrt::Windows::UI::Text::FontStretch>(GetValue(s_contentFontStretchProperty));
    }

    void Table::ContentFontStretch(winrt::Windows::UI::Text::FontStretch fontStretch)
    {
		SetValue(s_contentFontStretchProperty, winrt::box_value(fontStretch));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::ContentFontStretchProperty()
    {
        return s_contentFontStretchProperty;
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

    double Table::HorizontalLineThickness()
    {
        return winrt::unbox_value<double>(GetValue(s_horizontalLineThicknessProperty));
    }

    void Table::HorizontalLineThickness(double value)
    {
        SetValue(s_horizontalLineThicknessProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::HorizontalLineThicknessProperty()
    {
        return s_horizontalLineThicknessProperty;
    }

    winrt::Windows::UI::Color Table::VerticalLineColor()
    {
        return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(s_verticalLineColorProperty));
    }

    void Table::VerticalLineColor(winrt::Windows::UI::Color const& value)
    {
        SetValue(s_verticalLineColorProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::VerticalLineColorProperty()
    {
        return s_verticalLineColorProperty;
    }

    double Table::VerticalLineThickness()
    {
        return winrt::unbox_value<double>(GetValue(s_verticalLineThicknessProperty));
    }

    void Table::VerticalLineThickness(double value)
    {
        SetValue(s_verticalLineThicknessProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::VerticalLineThicknessProperty()
    {
        return s_verticalLineThicknessProperty;
    }

    winrt::Windows::Foundation::Collections::IVector<PackageRoot::TableAlternateRowColor> Table::AlternateRowColors()
    {
        return GetValue(s_alternateRowColorsProperty).as<winrt::Windows::Foundation::Collections::IVector<PackageRoot::TableAlternateRowColor>>();
    }

    void Table::AlternateRowColors(winrt::Windows::Foundation::Collections::IVector<PackageRoot::TableAlternateRowColor> const& value)
    {
		SetValue(s_alternateRowColorsProperty, value);
    }

	winrt::WinUINamespace::UI::Xaml::DependencyProperty Table::AlternateRowColorsProperty()
	{
		return s_alternateRowColorsProperty;
	}

    winrt::PackageRoot::TableColumnCollection Table::Columns()
    {
        return *m_columns;
    }

    winrt::PackageRoot::ITableData Table::ItemsSource()
    {
        return m_itemsSource;
    }

    void Table::ItemsSource(winrt::PackageRoot::ITableData const& data)
    {
        m_itemsSource = data;
    }

    void Table::setEffectiveTableData(winrt::PackageRoot::ITableData const& data)
    {
        m_tableData = data;
        m_d2dContent.m_textLayoutCache.OnTableDataSet(m_tableData ? &m_tableData : nullptr);

        if (m_tableData)
        {
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
        }

        m_d2dContent.m_textLayoutCache.Invalidate();
    }

    winrt::com_ptr<TableRowDataSource>& Table::ensureTableRowDataSource()
    {
        if (!m_tableRowDataSource)
        {
            m_tableRowDataSource = winrt::make_self<TableRowDataSource>();
            m_tableRowDataSource->Changed([this](int32_t startRow, int32_t endRow)
            {
                onTableRowDataChanged(startRow, endRow);
            });
        }

        return m_tableRowDataSource;
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::TableRow> Table::Items()
    {
        return ensureTableRowDataSource()->Items();
    }

    void Table::onTableRowDataChanged(int32_t startRow, int32_t endRow)
    {
        for (int r = startRow; r <= endRow; ++r)
            m_d2dContent.m_textLayoutCache.InvalidateRow(r);

        if (endRow >= startRow)
            m_overlayManager.InvalidateRows(startRow, endRow);

        if (m_isLoaded)
            requestDraw(true);
    }

    void Table::UpdateHorizontalScrollBar(float scrollOffsetX)
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

        m_horizontalScrollBarCache.ViewportSize(viewportWidth);
        m_horizontalScrollBarCache.Maximum(maxScroll);
        m_horizontalScrollBarCache.LargeChange(viewportWidth);
        m_horizontalScrollBarCache.Value(scrollOffsetX);
        m_horizontalScrollBarCache.Visibility(winrt::WinUINamespace::UI::Xaml::Visibility::Visible);
    }

    void Table::updateScrollBars()
    {
        UpdateVerticalScrollBar(m_d2dContent.ScrollOffsetY());
        UpdateHorizontalScrollBar(m_d2dContent.ScrollOffsetX());
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
        auto const contentRowHeight = m_d2dContent.m_tableHeight.ContentRowHeight();
        auto const wheelStepY = contentRowHeight * numWheelStepRow; //one wheel step scrolls 3 rows

        constexpr static auto wheelStepDelta = 120;
        auto const scrollY = wheelDelta / wheelStepDelta * wheelStepY; //(number of steps of wheel) * (step Y)

        auto const maxScrollY = m_d2dContent.DataCount() * contentRowHeight - m_d2dContent.GetViewportHeight();
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

        if (y <= m_d2dContent.m_tableHeight.HeaderRowHeight())
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

    void Table::onLeftClicked(winrt::WinUINamespace::UI::Input::PointerPoint const& pointer)
    {
        auto const [x, y] = pointer.Position();

        //click outside the editor dismisses it. Clicks on the editor itself
        //don't bubble up to SwapChainPanel because the inner control handles them.
        if (m_overlayManager.IsEditing())
        {
            m_overlayManager.EndEdit();
            return;
        }

        //is resize column
        if (y >= m_d2dContent.m_tableHeight.HeaderRowHeight())
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

	int Table::hitTestDataRow(float y) const
	{
		return static_cast<int>((y - m_d2dContent.m_tableHeight.HeaderRowHeight() + m_d2dContent.ScrollOffsetY()) / m_d2dContent.m_tableHeight.ContentRowHeight());
	}

	int Table::hitTestColumn(float x) const
	{
		auto& widthManager = m_d2dContent.m_columnWidthManager;
		auto const numColumns = static_cast<int>(widthManager.NumColumns());
		float columnLeft = -m_d2dContent.ScrollOffsetX();
		for (int i = 0; i < numColumns; ++i)
		{
			float const width = widthManager.Get(i);
			if (x >= columnLeft && x < columnLeft + width)
				return i;
			columnLeft += width;
		}
		return -1;
	}

	void Table::onRightClicked(winrt::WinUINamespace::UI::Input::PointerPoint const& pointer)
	{
        auto const [x, y] = pointer.Position();
        auto const headerRowHeight = m_d2dContent.m_tableHeight.HeaderRowHeight();

        int const rowIndex = y <= headerRowHeight ? -1 : hitTestDataRow(y);
        if (rowIndex >= m_d2dContent.DataCount())
            return;
        int const columnIndex = hitTestColumn(x);

        winrt::WinUINamespace::UI::Xaml::Controls::MenuFlyout menu{ nullptr };
        if (m_contextMenuRequestedEvent)
        {
            if (columnIndex < 0)
                return;

            auto args = winrt::make_self<implementation::ContextMenuRequestedEventArgs>(rowIndex, columnIndex);
            //DataContext: use the built-in TableRow when the user is filling `Items`; otherwise pass the ITableData source.
            //Map the display row to its source row so sorting returns the right item.
            if (m_tableRowDataSource && rowIndex >= 0)
                args->m_dataContext = m_tableRowDataSource->Items().GetAt(m_sortContext.Source(rowIndex));
            else if (m_itemsSource)
                args->m_dataContext = m_itemsSource;

            m_contextMenuRequestedEvent(*this, *args);


            if (args->Handled())
            {
                menu = args->ContextMenu();
                if (!menu)
                    return;
            }
        }

        if (!menu)
        {
            if (rowIndex < 0)
                menu = *winrt::make_self<implementation::DefaultTableHeaderContextMenu>(this, columnIndex);
            else
                menu = *winrt::make_self<implementation::DefaultTableContextMenu>(this, rowIndex, columnIndex);
        }
        auto const [px, py] = pointer.Position();
        menu.ShowAt(*this, winrt::Windows::Foundation::Point{ px, py });
	}

	winrt::event_token Table::ContextMenuRequested(
		winrt::Windows::Foundation::TypedEventHandler<
			winrt::PackageRoot::Table,
			winrt::PackageRoot::ContextMenuRequestedEventArgs> const& handler)
	{
		return m_contextMenuRequestedEvent.add(handler);
	}

	void Table::ContextMenuRequested(winrt::event_token const& token)
	{
		m_contextMenuRequestedEvent.remove(token);
	}

    void Table::SwapChainPanel_PointerPressed(
        winrt::Windows::Foundation::IInspectable const&,
        winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        auto const currentPoint = e.GetCurrentPoint(*this);
        auto const properties = currentPoint.Properties();
        if (properties.IsLeftButtonPressed())
            onLeftClicked(currentPoint);
        else if (properties.IsRightButtonPressed())
            onRightClicked(currentPoint);
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
		auto const headerRowHeight = m_d2dContent.m_tableHeight.HeaderRowHeight();

        //ignore double-tap on the header
        if (y < headerRowHeight)
            return;

        //hit-test column
        int const columnIndex = hitTestColumn(x);
        if (columnIndex < 0)
            return;

        //hit-test row
        int const row = hitTestDataRow(y);
        if (row < 0 || row >= m_d2dContent.DataCount())
            return;

        m_overlayManager.BeginEdit(row, columnIndex);
        e.Handled(true);
    }

    void Table::Table_Loaded(winrt::Windows::Foundation::IInspectable const&, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
    {
        if (m_itemsSource)
            setEffectiveTableData(m_itemsSource);
        else
            setEffectiveTableData(ensureTableRowDataSource().as<winrt::PackageRoot::ITableData>());
        m_isLoaded = true;

        m_overlayManager.OnLoaded();
        requestDraw(true);
    }

    void Table::onHeaderForegroundChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue());
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_headerForeground = D2DConvert::ToD2DColor(value); });
        else
            self->m_tableProperty.m_headerForeground = D2DConvert::ToD2DColor(value);
    }

    void Table::onContentForegroundChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_contentForeground = value; });
        else
            self->m_tableProperty.m_contentForeground = value;
    }

    void Table::onHeaderBackgroundChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_headerBackground = value; });
        else
            self->m_tableProperty.m_headerBackground = value;
    }

    void Table::onPointerOverBackgroundChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
        {
            self->m_sharedData.Update([value](TableProperty& data) {data.m_pointerOverBackground = value; });
            self->m_d2dContent.RequestDraw(FrameRequest::Flag::HoverColorDirty);
        }
        else
            self->m_tableProperty.m_pointerOverBackground = value;
    }

    void Table::onHeaderFontSizeChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = static_cast<float>(winrt::unbox_value<double>(e.NewValue()));
        auto const fontHeight = self->m_d2dContent.m_tableHeight.SetHeaderFontSize(value);
        if (self->m_isLoaded)
        {
            self->m_sharedData.Update([value](TableProperty& data) { data.m_headerFontSize = value; });
            self->requestDraw(true);
        }
        else
            self->m_tableProperty.m_headerFontSize = value;
		auto const contentPadding = self->ContentPadding();
		self->VerticalScrollBar().Margin(winrt::WinUINamespace::UI::Xaml::Thickness{ 0, fontHeight + contentPadding.Top + contentPadding.Bottom, 0, 0});
    }

    void Table::onContentPaddingChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = winrt::unbox_value<winrt::WinUINamespace::UI::Xaml::Thickness>(e.NewValue());
        auto const verticalPadding = static_cast<float>(value.Top + value.Bottom);
        self->m_d2dContent.m_tableHeight.SetVerticalPadding(verticalPadding);
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_contentPadding = value; });
        else
            self->m_tableProperty.m_contentPadding = value;
		self->VerticalScrollBar().Margin(winrt::WinUINamespace::UI::Xaml::Thickness{ 0, self->m_d2dContent.m_tableHeight.HeaderFontHeight() + verticalPadding, 0, 0});
    }

    void Table::onHeaderFontWeightChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToDWriteFontWeight(winrt::unbox_value<winrt::Windows::UI::Text::FontWeight>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_headerFontWeight = value; });
        else
            self->m_tableProperty.m_headerFontWeight = value;
    }

    void Table::onContentFontSizeChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = static_cast<float>(winrt::unbox_value<double>(e.NewValue()));
        self->m_d2dContent.m_tableHeight.SetContentFontSize(value);
        if (self->m_isLoaded)
        {
            self->m_sharedData.Update([value](TableProperty& data) { data.m_contentFontSize = value; });
            self->requestDraw(true);
        }
        else
            self->m_tableProperty.m_contentFontSize = value;
    }

    void Table::onFontFamilyChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto fontFamily = e.NewValue().as<winrt::WinUINamespace::UI::Xaml::Media::FontFamily>();
        auto self = GetSelf(d);
        auto& tableHeight = self->m_d2dContent.m_tableHeight;
        tableHeight.UpdateFont(fontFamily);
        tableHeight.SetHeaderFontSize(static_cast<float>(self->HeaderFontSize()));
        tableHeight.SetContentFontSize(static_cast<float>(self->ContentFontSize()));
        if (self->m_isLoaded)
            self->requestDraw(true);
    }

    void Table::onHorizontalLineColorChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
		auto self = GetSelf(d);
		auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
        {
            self->m_sharedData.Update([value](TableProperty& data) {data.m_horizontalLineColor = value; });
            self->m_d2dContent.RequestDraw(FrameRequest::Flag::FullRedraw);
        }
        else
			self->m_tableProperty.m_horizontalLineColor = value;
    }

    void Table::onHorizontalLineThicknessChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = static_cast<float>(winrt::unbox_value<double>(e.NewValue()));
        if (self->m_isLoaded)
        {
            self->m_sharedData.Update([value](TableProperty& data) {data.m_horizontalLineThickness = value; });
            self->m_d2dContent.RequestDraw(FrameRequest::Flag::FullRedraw);
        }
        else
            self->m_tableProperty.m_horizontalLineThickness = value;
    }

    void Table::onVerticalLineColorChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
		auto self = GetSelf(d);
		auto const value = D2DConvert::ToD2DColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
        if (self->m_isLoaded)
        {
            self->m_sharedData.Update([value](TableProperty& data) {data.m_verticalLineColor = value; });
            self->m_d2dContent.RequestDraw(FrameRequest::Flag::FullRedraw | FrameRequest::Flag::VerticalLineDirty);
        }
        else
            self->m_tableProperty.m_verticalLineColor = value;
    }

    void Table::onVerticalLineThicknessChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = static_cast<float>(winrt::unbox_value<double>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_verticalLineThickness = value; });
        else
            self->m_tableProperty.m_verticalLineThickness = value;
    }

    void Table::onContentFontWeightChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToDWriteFontWeight(winrt::unbox_value<winrt::Windows::UI::Text::FontWeight>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) {data.m_contentFontWeight = value; });
        else
            self->m_tableProperty.m_contentFontWeight = value;
    }

    void Table::onHeaderFontStyleChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToDwriteFontStyle(winrt::unbox_value<winrt::Windows::UI::Text::FontStyle>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_headerFontStyle = value; });
        else
            self->m_tableProperty.m_headerFontStyle = value;
    }

    void Table::onContentFontStyleChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToDwriteFontStyle(winrt::unbox_value<winrt::Windows::UI::Text::FontStyle>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_contentFontStyle = value; });
        else
            self->m_tableProperty.m_contentFontStyle = value;
    }

    void Table::onHeaderFontStretchChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToDwriteFontStretch(winrt::unbox_value<winrt::Windows::UI::Text::FontStretch>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_headerFontStretch = value; });
        else
            self->m_tableProperty.m_headerFontStretch = value;
    }

	void Table::onAlternateRowColorsChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		auto const value = e.NewValue().as<PackageRoot::TableAlternateRowColorCollection>();
		self->m_alternateRowColors.copy_from(winrt::get_self<implementation::TableAlternateRowColorCollection>(value));

		std::vector<TableProperty::AlternateRowColorPair> snapshot;
		snapshot.reserve(self->m_alternateRowColors->m_data.size());
		for (auto const& color : self->m_alternateRowColors->m_data)
			snapshot.push_back({ D2DConvert::ToD2DColor(color->m_foregroundColor), D2DConvert::ToD2DColor(color->m_backgroundColor) });

		if (self->m_isLoaded)
		{
			self->m_sharedData.Update([s = std::move(snapshot)](TableProperty& data) mutable { data.m_alternateRowColors = std::move(s); });
			self->m_d2dContent.RequestDraw(FrameRequest::Flag::FullRedraw | FrameRequest::Flag::AlternateRowDirty);
		}
		else
		{
			self->m_tableProperty.m_alternateRowColors = std::move(snapshot);
			self->m_d2dContent.m_request.Set(FrameRequest::Flag::AlternateRowDirty);
		}
	}

    void Table::sortObjectImpl(int rowCount)
    {
        std::ranges::stable_sort(m_sortContext.sortedIndices, [this](size_t lhsIndex, size_t rhsIndex)
        {
            auto const cmp = compareObject(
                m_tableRowDataSource->m_items->m_data[lhsIndex]->m_data[m_sortContext.sortParameter.sortColumn],
                m_tableRowDataSource->m_items->m_data[rhsIndex]->m_data[m_sortContext.sortParameter.sortColumn]
            );
            return m_sortContext.sortParameter.sortDirection == TableSortDirection::Ascending ? std::is_lt(cmp) : std::is_gt(cmp);
        });
    }

    void Table::sortStringImpl(int rowCount)
    {
        std::ranges::stable_sort(m_sortContext.sortedIndices, [this](size_t lhsIndex, size_t rhsIndex)
        {
            auto const cmp = 
                m_d2dContent.m_textLayoutCache.GetCellContent(lhsIndex, m_sortContext.sortParameter.sortColumn) <=>
                m_d2dContent.m_textLayoutCache.GetCellContent(rhsIndex, m_sortContext.sortParameter.sortColumn)
            ;
            return m_sortContext.sortParameter.sortDirection == TableSortDirection::Ascending ? std::is_lt(cmp) : std::is_gt(cmp);
        });
    }

    void Table::onContentFontStretchChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = GetSelf(d);
        auto const value = D2DConvert::ToDwriteFontStretch(winrt::unbox_value<winrt::Windows::UI::Text::FontStretch>(e.NewValue()));
        if (self->m_isLoaded)
            self->m_sharedData.Update([value](TableProperty& data) { data.m_contentFontStretch = value; });
        else
            self->m_tableProperty.m_contentFontStretch = value;
    }

    void Table::SwapChainPanel_PointerExited(winrt::Windows::Foundation::IInspectable const&, winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const&)
    {
        m_d2dContent.SetHover(-1.0);
    }
}
