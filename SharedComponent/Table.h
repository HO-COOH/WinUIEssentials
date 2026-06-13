#pragma once

#include "Table.g.h"
#include "TableD2DContent.h"
#include "CachedScrollBar.h"
#include "ResizeRequest.h"
#include "TableConstants.hpp"
#include "CachedCursor.hpp"
#include <include/PropertyChangeHelper.hpp>
#include "include/EnsureDependencyProperty.hpp"
#include "TableColumnCollection.h"
#include "TableProperty.h"
#include "SharedDataBase.hpp"
#include "TableOverlayManager.h"
#include "TableRowDataSource.h"

namespace winrt::PackageRoot::implementation
{
    struct Table : TableT<Table>, CachedCursor<Table>, MvvmHelper::PropertyChangeHelper<Table>, EnsureDependencyProperty<Table>
    {
        static void EnsureDependencyProperties();

        Table();

        void SwapChainPanel_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& e);
        void SwapChainPanel_CompositionScaleChanged(winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& sender, winrt::Windows::Foundation::IInspectable const& args);
        void VerticalScrollBar_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
        void HorizontalScrollBar_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
        void SwapChainPanel_PointerWheelChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void SwapChainPanel_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void SwapChainPanel_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void SwapChainPanel_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void Table_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
        void Table_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
        void Table_ActualThemeChanged(winrt::WinUINamespace::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const&);
		void SwapChainPanel_DoubleTapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& e);
        void updateVerticalScrollBar(float scrollOffsetY);

        //Properties
        int Fps();

        winrt::Windows::UI::Color HeaderForeground();
        void HeaderForeground(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderForegroundProperty();

        winrt::Windows::UI::Color ContentForeground();
        void ContentForeground(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentForegroundProperty();

        winrt::Windows::UI::Color HeaderBackground();
        void HeaderBackground(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderBackgroundProperty();

        winrt::Windows::UI::Color PointerOverBackground();
        void PointerOverBackground(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty const& PointerOverBackgroundProperty();

        double HeaderFontSize();
        void HeaderFontSize(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderFontSizeProperty();

        winrt::WinUINamespace::UI::Xaml::Thickness ContentPadding();
        void ContentPadding(winrt::WinUINamespace::UI::Xaml::Thickness const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentPaddingProperty();

        winrt::Windows::UI::Text::FontWeight HeaderFontWeight();
        void HeaderFontWeight(winrt::Windows::UI::Text::FontWeight const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderFontWeightProperty();

        double ContentFontSize();
        void ContentFontSize(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentFontSizeProperty();

        winrt::WinUINamespace::UI::Xaml::Media::FontFamily FontFamily();
        void FontFamily(winrt::WinUINamespace::UI::Xaml::Media::FontFamily const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty FontFamilyProperty();

        winrt::Windows::UI::Text::FontWeight ContentFontWeight();
        void ContentFontWeight(winrt::Windows::UI::Text::FontWeight const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentFontWeightProperty();

        winrt::Windows::UI::Text::FontStyle HeaderFontStyle();
        void HeaderFontStyle(winrt::Windows::UI::Text::FontStyle fontStyle);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderFontStyleProperty();

        winrt::Windows::UI::Text::FontStyle ContentFontStyle();
		void ContentFontStyle(winrt::Windows::UI::Text::FontStyle fontStyle);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentFontStyleProperty();

		winrt::Windows::UI::Text::FontStretch HeaderFontStretch();
		void HeaderFontStretch(winrt::Windows::UI::Text::FontStretch fontStretch);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderFontStretchProperty();

		winrt::Windows::UI::Text::FontStretch ContentFontStretch();
		void ContentFontStretch(winrt::Windows::UI::Text::FontStretch fontStretch);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentFontStretchProperty();

        winrt::Windows::UI::Color HorizontalLineColor();
        void HorizontalLineColor(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HorizontalLineColorProperty();

        double HorizontalLineThickness();
        void HorizontalLineThickness(double value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty HorizontalLineThicknessProperty();

        winrt::Windows::UI::Color VerticalLineColor();
        void VerticalLineColor(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty VerticalLineColorProperty();

		double VerticalLineThickness();
		void VerticalLineThickness(double value);
		static winrt::WinUINamespace::UI::Xaml::DependencyProperty VerticalLineThicknessProperty();

        winrt::PackageRoot::TableColumnCollection Columns();

        winrt::PackageRoot::ITableData ItemsSource();
        void ItemsSource(winrt::PackageRoot::ITableData const& data);

        winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::TableRow> Items();

        TableProperty m_tableProperty;
        SharedDataBase<TableProperty> m_sharedData{ m_tableProperty };
        TableD2DContent m_d2dContent{ *this };
        TableOverlayManager m_overlayManager{ *this };

    private:
        //Request a redraw and immediately refresh the scrollbars.
        void requestDraw(bool redraw = false);
        void setEffectiveTableData(winrt::PackageRoot::ITableData const& data);
        winrt::com_ptr<TableRowDataSource>& ensureTableRowDataSource();
        void onTableRowDataChanged(int32_t startRow, int32_t endRow);

        CachedScrollBar m_verticalScrollBarCache;
        CachedScrollBar m_horizontalScrollBarCache;
        bool m_isUpdatingVerticalScrollBarInCode{};
        bool m_isUpdatingHorizontalScrollBarInCode{};
        bool m_isLoaded{ false };
        float m_fps{};

        void updateHorizontalScrollBar(float scrollOffsetX);
        void updateScrollBars();
        void hideVerticalScrollBar();
        void hideHorizontalScrollBar();

        //resizing
        ResizeRequest m_resizeRequest;
        
        //fps
#if defined Build_WinUIPackage
        winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer m_fpsTimer{ nullptr };
#else
        winrt::Windows::UI::Xaml::DispatcherTimer m_fpsTimer;
#endif
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerForegroundProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentForegroundProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerBackgroundProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_pointerOverBackgroundProperty{ nullptr };
        //fonts
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerFontSizeProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentFontSizeProperty{ nullptr };

        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerFontWeightProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentFontWeightProperty{ nullptr };

        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerFontStyleProperty{ nullptr };
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentFontStyleProperty{ nullptr };

        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerFontStretchProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentFontStretchProperty{ nullptr };

        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentPaddingProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_fontFamilyProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_horizontalLineColorProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_horizontalLineThicknessProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_verticalLineColorProperty{ nullptr };
		static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_verticalLineThicknessProperty{ nullptr };


        static void onHeaderForegroundChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onContentForegroundChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onHeaderBackgroundChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onPointerOverBackgroundChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onHeaderFontSizeChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onContentPaddingChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onHeaderFontWeightChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onContentFontSizeChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onFontFamilyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onHorizontalLineColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onHorizontalLineThicknessChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onVerticalLineColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
		static void onVerticalLineThicknessChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
        static void onContentFontWeightChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
		static void onHeaderFontStyleChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
		static void onContentFontStyleChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
		static void onHeaderFontStretchChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
		static void onContentFontStretchChanged(
			winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
    public:
        winrt::com_ptr<TableColumnCollection> m_columns = winrt::make_self<TableColumnCollection>();
        winrt::com_ptr<TableRowDataSource> m_tableRowDataSource{ nullptr };
        winrt::PackageRoot::ITableData m_itemsSource{ nullptr };
        winrt::PackageRoot::ITableData m_tableData{ nullptr };
        winrt::PackageRoot::ITableData::UpdateRowData_revoker m_updateRowDataRevoker;
        void SwapChainPanel_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct Table : TableT<Table, implementation::Table>
    {
    };
}
