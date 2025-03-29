#include "pch.h"
#include "ComboBoxHelperPage.xaml.h"
#if __has_include("ComboBoxHelperPage.g.cpp")
#include "ComboBoxHelperPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	void ComboBoxHelperPage::Combo1_SelectionChanged(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{
		auto colorName = e.AddedItems().GetAt(0).as<winrt::hstring>();
		winrt::Windows::UI::Color color;
		if (colorName == L"Yellow") color = winrt::Windows::UI::Colors::Yellow();
		else if (colorName == L"Green") color = winrt::Windows::UI::Colors::Green();
		else if (colorName == L"Blue") color = winrt::Windows::UI::Colors::Blue();
		else if (colorName == L"Red") color = winrt::Windows::UI::Colors::Red();
		else throw winrt::hresult_invalid_argument{ colorName };

		Control1Output().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ color });
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> ComboBoxHelperPage::Fonts()
	{
		return m_fonts;
	}

	double ComboBoxHelperPage::GetDoubleFromComboBox(winrt::Windows::Foundation::IInspectable const& value)
	{
		return winrt::unbox_value<int>(value);
	}

	winrt::Microsoft::UI::Xaml::Media::FontFamily ComboBoxHelperPage::GetFontFamilyFromComboBox(winrt::Windows::Foundation::IInspectable const& value)
	{
		return value.as<winrt::Microsoft::UI::Xaml::Media::FontFamily>();
	}


}
