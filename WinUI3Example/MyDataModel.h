#pragma once

#include "MyDataModel.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MyDataModel : MyDataModelT<MyDataModel>
    {
        MyDataModel(
            winrt::hstring const& name, 
            winrt::hstring const& info, 
            winrt::hstring const& itemType, 
            winrt::hstring const& linkDescription, 
            winrt::hstring const& url
        );

        winrt::hstring Name();
        winrt::hstring Info();
        winrt::hstring ItemType();
        winrt::hstring LinkDescription();
        winrt::hstring Url();
    private:
        winrt::hstring m_name;
        winrt::hstring m_info;
        winrt::hstring m_itemType;
        winrt::hstring m_linkDescription;
        winrt::hstring m_url;
    };
}
