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

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> ComboBoxHelperPage::FontSizes()
	{
		return m_fontSizes;
	}

	double ComboBoxHelperPage::GetDoubleFromComboBox(winrt::Windows::Foundation::IInspectable const& value)
	{
		return winrt::unbox_value<int>(value);
	}

	winrt::Microsoft::UI::Xaml::Media::FontFamily ComboBoxHelperPage::GetFontFamilyFromComboBox(winrt::Windows::Foundation::IInspectable const& value)
	{
		return value.as<winrt::Microsoft::UI::Xaml::Media::FontFamily>();
	}

	void ComboBoxHelperPage::Combo4_SelectionChanged(
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

		Control4Output().Fill(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ color });
	}


	void winrt::WinUI3Example::implementation::ComboBoxHelperPage::Combo3_TextSubmitted(
		winrt::Microsoft::UI::Xaml::Controls::ComboBox const& sender, 
		winrt::Microsoft::UI::Xaml::Controls::ComboBoxTextSubmittedEventArgs const& args)
	{
		bool isInt{};
		int newValue;
		try 
		{
			newValue = std::stoi(sender.Text().data());
			isInt = true;
		}
		catch (...) 
		{
		}

		uint32_t index;
		if (isInt && (m_fontSizes.IndexOf(winrt::box_value(newValue), index) || (newValue < 100 && newValue > 8)))
			sender.SelectedItem(winrt::box_value(newValue));
		else
		{
			sender.Text(winrt::to_hstring(sender.SelectedValue().as<int>()));
			winrt::Microsoft::UI::Xaml::Controls::ContentDialog dialog;
			dialog.Content(winrt::box_value(L"The font size must be a number between 8 and 100."));
			dialog.CloseButtonText(L"Close");
			dialog.DefaultButton(winrt::Microsoft::UI::Xaml::Controls::ContentDialogButton::Close);
			dialog.XamlRoot(sender.XamlRoot());
			dialog.ShowAsync();
		}
		args.Handled(true);
	}
}
