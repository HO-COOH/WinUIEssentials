#pragma once

#include "GroupBox.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::UWPPackage::implementation
{
    struct GroupBox : GroupBoxT<GroupBox>, TemplateControlHelper<GroupBox>
    {
        GroupBox() = default;

        //This really should be String, but it fucked up the compilation, because of https://github.com/microsoft/microsoft-ui-xaml/issues/8994
        //winrt::hstring Header();
        //void Header(winrt::hstring value);

        winrt::Windows::Foundation::IInspectable Header();
        void Header(winrt::Windows::Foundation::IInspectable value);
    private:
        winrt::Windows::Foundation::IInspectable m_header{ nullptr };
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct GroupBox : GroupBoxT<GroupBox, implementation::GroupBox>
    {
    };
}
