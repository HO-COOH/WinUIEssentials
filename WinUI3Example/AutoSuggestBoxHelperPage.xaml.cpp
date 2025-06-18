#include "pch.h"
#include "AutoSuggestBoxHelperPage.xaml.h"
#if __has_include("AutoSuggestBoxHelperPage.g.cpp")
#include "AutoSuggestBoxHelperPage.g.cpp"
#endif
#include <boost/algorithm/string.hpp>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	void AutoSuggestBoxHelperPage::Control1_SuggestionChosen(
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const&, 
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args)
	{
		SuggestionOutput().Text(args.SelectedItem().as<winrt::hstring>());
	}

	void AutoSuggestBoxHelperPage::Control2_SuggestionChosen(
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const&,
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args)
	{
		SuggestionOutput2().Text(args.SelectedItem().as<winrt::hstring>());
	}

	void AutoSuggestBoxHelperPage::Control1_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
	{
		if (args.Reason() == winrt::Microsoft::UI::Xaml::Controls::AutoSuggestionBoxTextChangeReason::UserInput)
		{
			std::vector<winrt::Windows::Foundation::IInspectable> suitableItems;
			std::vector<std::wstring> splitText;
			boost::algorithm::split(
				splitText, 
				boost::algorithm::to_lower_copy(std::wstring{ sender.Text() }), 
				boost::is_space()
			);
			for (auto const& cat : Cats)
			{
				auto const found = std::ranges::any_of(splitText, [cat](auto const& key) {
					return boost::to_lower_copy<std::wstring>(cat).find(key) != std::wstring::npos;
				});
				if(found)
					suitableItems.push_back(winrt::box_value(cat));
			}
			if (suitableItems.size() == 0)
				suitableItems.push_back(winrt::box_value(L"No results found"));
			sender.ItemsSource(winrt::single_threaded_vector(std::move(suitableItems)));
		}
	}

}
