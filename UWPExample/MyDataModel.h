#pragma once

#include "MyDataModel.g.h"

namespace winrt::UWPExample::implementation
{
    struct MyDataModel : MyDataModelT<MyDataModel>
    {
        MyDataModel() = default;

        winrt::hstring Name();
        void Name(winrt::hstring value);

        winrt::hstring Info();
        void Info(winrt::hstring value);

        winrt::hstring ItemType();
        void ItemType(winrt::hstring value);

        winrt::hstring LinkDescription();
        void LinkDescription(winrt::hstring value);

        winrt::hstring Url();
        void Url(winrt::hstring value);

    private:
        winrt::hstring m_name;
        winrt::hstring m_info;
        winrt::hstring m_itemType;
        winrt::hstring m_linkDescription;
        winrt::hstring m_url;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct MyDataModel : MyDataModelT<MyDataModel, implementation::MyDataModel>
    {
    };
}
