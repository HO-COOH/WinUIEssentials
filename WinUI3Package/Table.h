#pragma once

#include "Table.g.h"
#include "SwapChainInterop.h"
#include "DirectN.h"
#include "TableTestData.hpp"
#include "TextLayoutCache.h"

namespace winrt::WinUI3Package::implementation
{
    struct Table : TableT<Table>
    {
        Table();

        void ClickHandler(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void SwapChainPanel_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
    private:
		winrt::com_ptr<ID3D11Device> m_d3dDevice = DirectN::CreateD3D11Device();
		winrt::com_ptr<ID2D1DeviceContext> m_d2dContext;
        winrt::com_ptr<IDWriteFactory>  m_dwriteFactory = DirectN::CreateDWriteFactory();

        SwapChainInterop m_swapChain;

        //text
        winrt::com_ptr<IDWriteTextFormat> m_headerTextFormat;
		winrt::com_ptr<IDWriteTextFormat> m_cellTextFormat;
        TextLayoutCache m_textLayoutCache{ m_dwriteFactory.get() };

        //brushes
        winrt::com_ptr<ID2D1SolidColorBrush> m_textBrush;

        //scrolling
        float m_scrollOffsetX{};
        float m_scrollOffsetY{};
        int m_sortColumnIndex{ -1 };

        //data
		TableTestData m_data;

        void draw();
        void drawHeader();
        void drawRows();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Table : TableT<Table, implementation::Table>
    {
    };
}
