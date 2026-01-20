#pragma once

#include "RevealComboBox.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct RevealComboBox : RevealComboBoxT<RevealComboBox>
    {
        RevealComboBox() = default;

		void OnApplyTemplate();
        void PrepareContainerForItemOverride(
			winrt::Microsoft::UI::Xaml::DependencyObject const& element, 
            winrt::Windows::Foundation::IInspectable const& item
        );
    private:
		winrt::Microsoft::UI::Xaml::Controls::Border m_border{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct RevealComboBox : RevealComboBoxT<RevealComboBox, implementation::RevealComboBox>
    {
    };
}
