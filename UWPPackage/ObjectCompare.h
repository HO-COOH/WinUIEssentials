#pragma once
#include <winrt/Windows.Foundation.h>

namespace internal
{
    /**
	 * @brief Check if two types can be compared as strings.
     */
    bool IsStringComparable(
        winrt::Windows::Foundation::PropertyType type1,
        winrt::Windows::Foundation::PropertyType type2
    );

    /**
	 * @brief Check if two objects are equal by comparing their string representations.
     */
    bool IsStringCompareEqual(
        winrt::Windows::Foundation::IInspectable object1,
        winrt::Windows::Foundation::IInspectable object2,
        winrt::Windows::Foundation::PropertyType type1,
        winrt::Windows::Foundation::PropertyType type2
    );

    /**
	 * @brief Compare two boxed values.
     */
    bool ConvertTypeEquals(
        winrt::Windows::Foundation::IInspectable value1,
        winrt::Windows::Foundation::IInspectable value2
    );
}
