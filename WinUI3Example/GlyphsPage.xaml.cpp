// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "GlyphsPage.xaml.h"
#if __has_include("GlyphsPage.g.cpp")
#include "GlyphsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> GlyphsPage::Glyphs()
    {
        auto dict = winrt::Microsoft::UI::Xaml::Application::Current().Resources().MergedDictionaries().GetAt(4);
        auto const size = dict.Size();
        std::vector<WinUI3Example::Icon> glyphs;
        glyphs.reserve(size);


        std::ranges::transform(dict, std::back_inserter(glyphs), [](winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable> p)
        {
            return WinUI3Example::Icon{
                .Glyph = winrt::unbox_value<winrt::hstring>(p.Value()),
                .Name = winrt::unbox_value<winrt::hstring>(p.Key())
            };
        });

        std::ranges::sort(glyphs, [](auto const& lhs, auto const& rhs)
        {
            return lhs.Name < rhs.Name;
        });

        std::vector<winrt::Windows::Foundation::IInspectable> boxed;
        boxed.reserve(size);
        std::ranges::transform(glyphs, std::back_inserter(boxed), [](auto const& icon) { return winrt::box_value(icon); });
        return winrt::single_threaded_vector(std::move(boxed));
    }
}
