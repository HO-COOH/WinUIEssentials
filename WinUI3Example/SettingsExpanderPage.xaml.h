// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "SettingsExpanderPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SettingsExpanderPage : SettingsExpanderPageT<SettingsExpanderPage>
    {
        SettingsExpanderPage();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> MyDataSet();

    private:
        std::vector<winrt::Windows::Foundation::IInspectable> m_myDataSet
        {
            []
            {
                WinUI3Example::MyDataModel model;
                model.Name(L"First Item");
                model.Info(L"More about first item.");
                model.ItemType(L"Item type: Button");
                model.LinkDescription(L"Click here for more on first item.");
                model.Url(L"https://microsoft.com/");
                return model;
            }(),
            []
            {
                WinUI3Example::MyDataModel model;
                model.Name(L"Second Item");
                model.Info(L"More about second item.");
                model.ItemType(L"Item type: Link button");
                model.LinkDescription(L"Click here for more on second item.");
                model.Url(L"https://xbox.com/");
                return model;
            }(),
            []
            {
                WinUI3Example::MyDataModel model;
                model.Name(L"Third Item");
                model.Info(L"More about third item.");
                model.ItemType(L"Item type: No button");
                model.LinkDescription(L"Click here for more on third item.");
                model.Url(L"https://toolkitlabs.dev/");
                return model;
            }()
        };
    public:
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SettingsExpanderPage : SettingsExpanderPageT<SettingsExpanderPage, implementation::SettingsExpanderPage>
    {
    };
}
