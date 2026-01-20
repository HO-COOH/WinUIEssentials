#include "pch.h"
#include "RevealComboBox.h"
#if __has_include("RevealComboBox.g.cpp")
#include "RevealComboBox.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void RevealComboBox::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		m_border = GetTemplateChild(L"PopupBorder").as<winrt::Microsoft::UI::Xaml::Controls::Border>();
	}

	void RevealComboBox::PrepareContainerForItemOverride(winrt::Microsoft::UI::Xaml::DependencyObject const& element, winrt::Windows::Foundation::IInspectable const& item)
	{
		base_type::PrepareContainerForItemOverride(element, item);
		if (auto container = element.as<winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem>(); m_border)
			winrt::WinUI3Package::RevealFocusPanel::SetAttachToPanel(container, m_border);
	}
}
