#pragma once

#include "MyGridData.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MyGridData : MyGridDataT<MyGridData>
    {
        MyGridData();

        winrt::Windows::Foundation::Collections::IVector<winrt::hstring> Headers();

		winrt::hstring OnGetData(int32_t row, int32_t column);
        int OnGetNumRows();
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::hstring> m_headers{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MyGridData : MyGridDataT<MyGridData, implementation::MyGridData>
    {
    };
}
