#pragma once

#include "AutoSuggestBoxHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct AutoSuggestBoxHelperPage : AutoSuggestBoxHelperPageT<AutoSuggestBoxHelperPage>
    {
        AutoSuggestBoxHelperPage() = default;
        void Control1_SuggestionChosen(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
        void Control1_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
        void Control2_SuggestionChosen(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
        constexpr static std::array Cats
        {
            L"Abyssinian",
            L"Aegean",
            L"American Bobtail",
            L"American Curl",
            L"American Ringtail",
            L"American Shorthair",
            L"American Wirehair",
            L"Aphrodite Giant",
            L"Arabian Mau",
            L"Asian cat",
            L"Asian Semi-longhair",
            L"Australian Mist",
            L"Balinese",
            L"Bambino",
            L"Bengal",
            L"Birman",
            L"Brazilian Shorthair",
            L"British Longhair",
            L"British Shorthair",
            L"Burmese",
            L"Burmilla",
            L"California Spangled",
            L"Chantilly-Tiffany",
            L"Chartreux",
            L"Chausie",
            L"Colorpoint Shorthair",
            L"Cornish Rex",
            L"Cymric",
            L"Cyprus",
            L"Devon Rex",
            L"Donskoy",
            L"Dragon Li",
            L"Dwelf",
            L"Egyptian Mau",
            L"European Shorthair",
            L"Exotic Shorthair",
            L"Foldex",
            L"German Rex",
            L"Havana Brown",
            L"Highlander",
            L"Himalayan",
            L"Japanese Bobtail",
            L"Javanese",
            L"Kanaani",
            L"Khao Manee",
            L"Kinkalow",
            L"Korat",
            L"Korean Bobtail",
            L"Korn Ja",
            L"Kurilian Bobtail",
            L"Lambkin",
            L"LaPerm",
            L"Lykoi",
            L"Maine Coon",
            L"Manx",
            L"Mekong Bobtail",
            L"Minskin",
            L"Napoleon",
            L"Munchkin",
            L"Nebelung",
            L"Norwegian Forest Cat",
            L"Ocicat",
            L"Ojos Azules",
            L"Oregon Rex",
            L"Persian (modern)",
            L"Persian (traditional)",
            L"Peterbald",
            L"Pixie-bob",
            L"Ragamuffin",
            L"Ragdoll",
            L"Raas",
            L"Russian Blue",
            L"Russian White",
            L"Sam Sawet",
            L"Savannah",
            L"Scottish Fold",
            L"Selkirk Rex",
            L"Serengeti",
            L"Serrade Petit",
            L"Siamese",
            L"Siberian or´Siberian Forest Cat",
            L"Singapura",
            L"Snowshoe",
            L"Sokoke",
            L"Somali",
            L"Sphynx",
            L"Suphalak",
            L"Thai",
            L"Thai Lilac",
            L"Tonkinese",
            L"Toyger",
            L"Turkish Angora",
            L"Turkish Van",
            L"Turkish Vankedisi",
            L"Ukrainian Levkoy",
            L"Wila Krungthep",
            L"York Chocolate"
        };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AutoSuggestBoxHelperPage : AutoSuggestBoxHelperPageT<AutoSuggestBoxHelperPage, implementation::AutoSuggestBoxHelperPage>
    {
    };
}
