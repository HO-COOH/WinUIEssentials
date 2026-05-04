#pragma once

#include "GroupBox.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::PackageRoot::implementation
{
    struct GroupBox : GroupBoxT<GroupBox>, TemplateControlHelper<GroupBox>
    {
        GroupBox() = default;

        //This really should be String, but it fucked up the compilation, because of https://github.com/microsoft/microsoft-ui-xaml/issues/8994
        winrt::hstring Header();
        void Header(winrt::hstring const& value);

#if defined Build_WinUIPackage
        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/GroupBox_Resource.xaml";
#else
        constexpr static auto ResourceUri = L"ms-appx:///UWPPackage/GroupBox_Resource.xaml";
#endif
    private:
        winrt::hstring m_header;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct GroupBox : GroupBoxT<GroupBox, implementation::GroupBox>
    {
    };
}
 