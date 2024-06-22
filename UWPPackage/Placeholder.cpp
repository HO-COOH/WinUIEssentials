#include "pch.h"
#include "Placeholder.h"
#if __has_include("Placeholder.g.cpp")
#include "Placeholder.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
    int32_t Placeholder::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Placeholder::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
}
