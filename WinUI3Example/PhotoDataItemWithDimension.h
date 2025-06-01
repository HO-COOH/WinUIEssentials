#pragma once

#include "PhotoDataItemWithDimension.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct PhotoDataItemWithDimension : PhotoDataItemWithDimensionT<PhotoDataItemWithDimension>
    {
        PhotoDataItemWithDimension() = default;

        double Width();
		void Width(double value);

		double Height();
		void Height(double value);

        winrt::hstring Title();
		void Title(winrt::hstring const& value);

        winrt::hstring Category();
		void Category(winrt::hstring const& value);

        winrt::hstring Thumbnail();
		void Thumbnail(winrt::hstring const& value);

    private:
        double m_width{ 0.0 };
        double m_height{ 0.0 };
        winrt::hstring m_title;
        winrt::hstring m_category;
		winrt::hstring m_thumbnail;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct PhotoDataItemWithDimension : PhotoDataItemWithDimensionT<PhotoDataItemWithDimension, implementation::PhotoDataItemWithDimension>
    {
    };
}
