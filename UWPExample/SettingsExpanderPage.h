#pragma once

#include "SettingsExpanderPage.g.h"
#include "MyDataModel.h"

namespace winrt::UWPExample::implementation
{
    struct SettingsExpanderPage : SettingsExpanderPageT<SettingsExpanderPage>
    {

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> MyDataSet();

    private:
        std::vector<winrt::Windows::Foundation::IInspectable> m_myDataSet
        {
            winrt::make<MyDataModel>(
                L"First Item",
                L"More about first item.",
                L"Item type: Button",
                L"Click here for more on first item.",
                L"https://microsoft.com/"
            ),
            winrt::make<MyDataModel>(
                L"Second Item", L"More about second item.", L"Item type: Link button",
                L"Click here for more on second item.", L"https://xbox.com/"
            ),
            winrt::make<MyDataModel>(
                L"Third Item", L"More about third item.", L"Item type: No button",
                L"Click here for more on third item.", L"https://toolkitlabs.dev/"
            )
        };
    public:
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SettingsExpanderPage : SettingsExpanderPageT<SettingsExpanderPage, implementation::SettingsExpanderPage>
    {
    };
}
