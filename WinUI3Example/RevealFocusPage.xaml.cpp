#include "pch.h"
#include "RevealFocusPage.xaml.h"
#if __has_include("RevealFocusPage.g.cpp")
#include "RevealFocusPage.g.cpp"
#endif

#include <numeric>
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    void RevealFocusPage::OnNavigatedTo(winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        BaseListView().ItemsSource(winrt::single_threaded_observable_vector(GetContactAsync()));
        std::vector<int> days(30, 0);
        std::iota(days.begin(), days.end(), 0);
        BaseGridView().ItemsSource(winrt::single_threaded_observable_vector(std::move(days)));
    }

    void RevealFocusPage::BaseListView_ContainerContentChanging(
        winrt::Microsoft::UI::Xaml::Controls::ListViewBase const& sender,
        winrt::Microsoft::UI::Xaml::Controls::ContainerContentChangingEventArgs const& args)
    {
        if (args.InRecycleQueue())
            return;

        if (auto itemContainer = args.ItemContainer())
            itemContainer.SetValue(winrt::WinUI3Package::RevealFocusPanel::AttachToPanelProperty(), sender.Tag());
    }

    std::vector<winrt::WinUI3Example::Contact> RevealFocusPage::GetContactAsync()
    {
        constexpr static std::array lines
        {
            L"Kendall",
            L"Collins",
            L"Adatum Corporation",
            L"Henry",
            L"Ross",
            L"Adventure Works Cycles",
            L"Vance",
            L"DeLeon",
            L"Alpine Ski House",
            L"Victoria",
            L"Burke",
            L"Bellows College",
            L"Amber",
            L"Rodriguez",
            L"Best For You Organics Company",
            L"Amari",
            L"Rivera",
            L"Contoso, Ltd.",
            L"Jessie",
            L"Irwin",
            L"Contoso Pharmaceuticals",
            L"Quinn",
            L"Campbell",
            L"Contoso Suites",
            L"Olivia",
            L"Wilson",
            L"Consolidated Messenger",
            L"Ana",
            L"Bowman",
            L"Fabrikam, Inc.",
            L"Shawn",
            L"Hughes",
            L"Fabrikam Residences",
            L"Oscar",
            L"Ward",
            L"First Up Consultants",
            L"Madison",
            L"Butler",
            L"Fourth Coffee",
            L"Graham",
            L"Barnes",
            L"Graphic Design Institute",
            L"Anthony",
            L"Ivanov",
            L"Humongous Insurance",
            L"Michael",
            L"Peltier",
            L"Lamna Healthcare Company",
            L"Morgan",
            L"Connors",
            L"Liberty's Delightful Sinful Bakery & Cafe",
            L"Andre",
            L"Lawson",
            L"Lucerne Publishing",
            L"Preston",
            L"Morales",
            L"Margie's Travel",
            L"Briana",
            L"Hernandez",
            L"Nod Publishers",
            L"Nicole",
            L"Wagner",
            L"Northwind Traders",
            L"Mario",
            L"Rogers",
            L"Proseware, Inc.",
            L"Eugenia",
            L"Lopez",
            L"Relecloud",
            L"Nathan",
            L"Rigby",
            L"School of Fine Art",
            L"Ellis",
            L"Turner",
            L"Southridge Video",
            L"Miguel",
            L"Reyes",
            L"Tailspin Toys",
            L"Hayden",
            L"Cook",
            L"Tailwind Traders"
        };

        std::vector<winrt::WinUI3Example::Contact> contacts;
        for (int i = 0; i < lines.size() - 2; i += 3)
            contacts.push_back(winrt::WinUI3Example::Contact{ lines[i], lines[i + 1], lines[i + 2] });
        return contacts;
    }
}
