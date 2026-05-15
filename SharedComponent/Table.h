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
#include "TableData.h"
#include "SharedDataBase.hpp"

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
        
        void updateVerticalScrollBar(float scrollOffsetY);

        //Properties
        int Fps();
        int DataCount();
        void DataCount(int value);

        winrt::Windows::UI::Color HeaderForeground();
        void HeaderForeground(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderForegroundProperty();

        winrt::Windows::UI::Color ContentForeground();
        void ContentForeground(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentForegroundProperty();

        winrt::Windows::UI::Color HeaderBackground();
        void HeaderBackground(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderBackgroundProperty();

        float HeaderFontSize();
        void HeaderFontSize(float value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderFontSizeProperty();

        winrt::WinUINamespace::UI::Xaml::Thickness ContentPadding();
        void ContentPadding(winrt::WinUINamespace::UI::Xaml::Thickness const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentPaddingProperty();

        winrt::Windows::UI::Text::FontWeight HeaderFontWeight();
        void HeaderFontWeight(winrt::Windows::UI::Text::FontWeight const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HeaderFontWeightProperty();

        float ContentFontSize();
        void ContentFontSize(float value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentFontSizeProperty();

        winrt::WinUINamespace::UI::Xaml::Media::FontFamily FontFamily();
        void FontFamily(winrt::WinUINamespace::UI::Xaml::Media::FontFamily const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty FontFamilyProperty();

        winrt::Windows::UI::Text::FontWeight ContentFontWeight();
        void ContentFontWeight(winrt::Windows::UI::Text::FontWeight const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentFontWeightProperty();

        winrt::Windows::UI::Color HorizontalLineColor();
        void HorizontalLineColor(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HorizontalLineColorProperty();

        winrt::Windows::UI::Color VerticalLineColor();
        void VerticalLineColor(winrt::Windows::UI::Color const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty VerticalLineColorProperty();

        winrt::PackageRoot::TableColumnCollection Columns();

        winrt::PackageRoot::ITableData Data();
        void Data(winrt::PackageRoot::ITableData const& data);
    public:
        TableData m_data;
        SharedDataBase<TableData> m_sharedData{ m_data };
        bool m_isLoaded{ false };
    private:
        TableD2DContent m_d2dContent{ *this };

        //Request a redraw and immediately refresh the scrollbars.
        //UI-thread only.
        void requestDraw(bool redraw = false);

        //scrollbars (XAML - UI thread only)
        CachedScrollBar m_verticalScrollBarCache;
        CachedScrollBar m_horizontalScrollBarCache;
        bool m_isUpdatingVerticalScrollBarInCode{};
        bool m_isUpdatingHorizontalScrollBarInCode{};

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
        float m_fps{};
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerForegroundProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentForegroundProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerBackgroundProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerFontSizeProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentPaddingProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_headerFontWeightProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentFontSizeProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_fontFamilyProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_horizontalLineColorProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_verticalLineColorProperty{ nullptr };
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentFontWeightProperty{ nullptr };

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
        static void onVerticalLineColorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onContentFontWeightChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    public:
        winrt::com_ptr<TableColumnCollection> m_columns = winrt::make_self<TableColumnCollection>();
        winrt::PackageRoot::ITableData m_tableData{ nullptr };
        void SwapChainPanel_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::Input::PointerRoutedEventArgs const& e);
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct Table : TableT<Table, implementation::Table>
    {
    };
}
