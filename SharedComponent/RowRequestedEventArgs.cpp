#include "pch.h"
#include "RowRequestedEventArgs.h"
#if __has_include("RowRequestedEventArgs.g.cpp")
#include "RowRequestedEventArgs.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
    int32_t RowRequestedEventArgs::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void RowRequestedEventArgs::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
}
