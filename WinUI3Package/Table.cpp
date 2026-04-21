#include "pch.h"
#include "Table.h"
#if __has_include("Table.g.cpp")
#include "Table.g.cpp"
#endif
#include "TableTestData.hpp"
#include "TableConstants.hpp"
#include "D2DPrimitiveHelper.h"

namespace winrt::WinUI3Package::implementation
{
    Table::Table()
    {
        InitializeComponent();

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

		winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), m_textBrush.put()));
    }

    void Table::ClickHandler(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }

    void Table::draw()
    {
        if (m_swapChain.CurrentSize.Width <= 0 || m_swapChain.CurrentSize.Height <= 0)
            return;

        m_d2dContext->BeginDraw();
        drawRows();
        drawHeader();
        m_d2dContext->EndDraw();
        DXGI_PRESENT_PARAMETERS presentParameters{};
        winrt::check_hresult(m_swapChain->Present1(0, DXGI_PRESENT_RESTART, &presentParameters));
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
                    .right = currentX + 200, 
                    .bottom = 30 
                },
                m_textBrush.get()
			);

			if (m_sortColumnIndex == column)
            {
                
            }

            D2DPrimitiveHelper::DrawVerticalLine(
                m_d2dContext.get(),
                currentX + 199,
                4,
                4 + TableConstants::HeaderFontSize,
                m_textBrush.get()
            );
            currentX += 200;
        }
    }

    void Table::drawRows()
    {
    }


    void Table::SwapChainPanel_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
    {
        m_swapChain.SizeChanged(*this, e);
		m_swapChain.SetTarget(m_d2dContext.get());
        draw();
    }

}
