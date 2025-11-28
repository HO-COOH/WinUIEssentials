#pragma once
#include "ComboBoxHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ComboBoxHelperPage : ComboBoxHelperPageT<ComboBoxHelperPage>
    {
        ComboBoxHelperPage() = default;
        void Combo1_SelectionChanged(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Combo4_SelectionChanged(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Combo3_TextSubmitted(
            winrt::Microsoft::UI::Xaml::Controls::ComboBox const& sender, 
            winrt::Microsoft::UI::Xaml::Controls::ComboBoxTextSubmittedEventArgs const& args);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Fonts();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> FontSizes();
        static double GetDoubleFromComboBox(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::Media::FontFamily GetFontFamilyFromComboBox(winrt::Windows::Foundation::IInspectable const& value);
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_fonts
            = winrt::single_threaded_vector(
                std::vector<winrt::Windows::Foundation::IInspectable>
                {
                    winrt::WinUI3Example::FontInfo{ L"Arial", winrt::Microsoft::UI::Xaml::Media::FontFamily{L"Arial"}},
                    winrt::WinUI3Example::FontInfo{L"Comic Sans MS", winrt::Microsoft::UI::Xaml::Media::FontFamily{L"Comic Sans MS"}},
                    winrt::WinUI3Example::FontInfo{L"Courier New", winrt::Microsoft::UI::Xaml::Media::FontFamily{L"Courier New"}},
                    winrt::WinUI3Example::FontInfo{L"Segoe UI", winrt::Microsoft::UI::Xaml::Media::FontFamily{L"Segoe UI"}},
                    winrt::WinUI3Example::FontInfo{L"Times New Roman", winrt::Microsoft::UI::Xaml::Media::FontFamily{L"Times New Roman"}}
                }
            );
		winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_fontSizes = 
            winrt::single_threaded_vector(
                std::vector{
					winrt::box_value(8),
					winrt::box_value(9),
					winrt::box_value(10),
					winrt::box_value(11),
					winrt::box_value(12),
                    winrt::box_value(14),
					winrt::box_value(16),
					winrt::box_value(18),
					winrt::box_value(20),
                    winrt::box_value(24),
					winrt::box_value(28),
                    winrt::box_value(36),
					winrt::box_value(48),
					winrt::box_value(72)
                }
            );   
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ComboBoxHelperPage : ComboBoxHelperPageT<ComboBoxHelperPage, implementation::ComboBoxHelperPage>
    {
    };
}
