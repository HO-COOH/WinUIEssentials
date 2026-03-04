#pragma once

#include "GroupBox.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct GroupBox : GroupBoxT<GroupBox>, TemplateControlHelper<GroupBox>
    {
        GroupBox() = default;

        //This really should be String, but it fucked up the compilation, because of https://github.com/microsoft/microsoft-ui-xaml/issues/8994
        winrt::hstring Header();
        void Header(winrt::hstring const& value);

        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/GroupBox_Resource.xaml";
    private:
        winrt::hstring m_header;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct GroupBox : GroupBoxT<GroupBox, implementation::GroupBox>
    {
    };
}
 