#include "pch.h"
#include "GlyphsPage.h"
#if __has_include("GlyphsPage.g.cpp")
#include "GlyphsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> GlyphsPage::Glyphs()
	{
        auto dict = winrt::Windows::UI::Xaml::Application::Current().Resources().MergedDictionaries().GetAt(3);
        auto const size = dict.Size();
        std::vector<UWPExample::Icon> glyphs;
        glyphs.reserve(size);
        

        std::ranges::transform(dict, std::back_inserter(glyphs), [](winrt::Windows::Foundation::Collections::IKeyValuePair<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable> p)
        {
            return UWPExample::Icon{
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
