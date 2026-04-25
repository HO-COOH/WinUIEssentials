#pragma once
#include <winrt/Windows.Foundation.h>

namespace internal
{
    /**
     * @brief Check if two types can be compared as strings.
     */
    constexpr bool IsStringComparable(
        winrt::Windows::Foundation::PropertyType type1,
        winrt::Windows::Foundation::PropertyType type2
    )
    {
		if (type1 != winrt::Windows::Foundation::PropertyType::String && type2 != winrt::Windows::Foundation::PropertyType::String)
			return false;
		//here only type1 or type2 is string

		//if type1 is string and type 2 is not, do a swap to check
		if (type1 == winrt::Windows::Foundation::PropertyType::String)
			return IsStringComparable(type2, type1);

		//now type1 is not string, type2 is string
		switch (type1)
		{
			/*
				There are 15 winrt::to_hstring overloads, so they are string comparable.
				They are: (copied from Visual Studio find definitions)
					1. winrt::to_hstrihng(int64_t)
					2. winrt::to_hstring(double)
					3. winrt::to_hstring(float)
					4. winrt::to_hstring(char16_t)
					5. winrt::to_hstring(int32_t)
					6. winrt::to_hstring(int16_t)
					7. winrt::to_hstring(int8_t)
					8. winrt::to_hstring(uint64_t)
					9. winrt::to_hstring(uint8_t)
					10. winrt::to_hstring(uint32_t)
					11. winrt::to_hstring(uint16_t)
					12. winrt::to_hstring(guid const&)
					13. winrt::to_hstring(hstring const&) // we don't need this

					14. template<typename T, std::enable_if<std::is_same_v<T, bool>, int> = 0>
						winrt::to_hstring<T>(T const)  //which basically means bool

					15. template<typename T, std::enabkle_if<std::convertible_v<T, std::string_view>, int> = 0>
						winrt::to_hstring<T>(T const&) //which basically means std::string_view, which we also don't need

			*/
			case winrt::Windows::Foundation::PropertyType::Int64:  //1
			case winrt::Windows::Foundation::PropertyType::Double: //2
			case winrt::Windows::Foundation::PropertyType::Single: //3
			case winrt::Windows::Foundation::PropertyType::Char16: //4
			case winrt::Windows::Foundation::PropertyType::Int32:  //5
			case winrt::Windows::Foundation::PropertyType::Int16:  //6
				//case winrt::Windows::Foundation::PropertyType::Int8: there is no int8
			case winrt::Windows::Foundation::PropertyType::UInt64: //8
			case winrt::Windows::Foundation::PropertyType::UInt8:  //9
			case winrt::Windows::Foundation::PropertyType::UInt32: //10
			case winrt::Windows::Foundation::PropertyType::UInt16: //11
			case winrt::Windows::Foundation::PropertyType::Guid:   //12
			case winrt::Windows::Foundation::PropertyType::Boolean: //14
				return true;
			default:
				return false;
		}
    }

    /**
     * @brief Check if two objects are equal by comparing their string representations.
     */
    bool IsStringCompareEqual(
        winrt::Windows::Foundation::IInspectable const& object1,
        winrt::Windows::Foundation::IInspectable const& object2,
        winrt::Windows::Foundation::PropertyType type1,
        winrt::Windows::Foundation::PropertyType type2
    );

    /**
     * @brief Compare two boxed values.
     */
    bool ConvertTypeEquals(
        winrt::Windows::Foundation::IInspectable const& value1,
        winrt::Windows::Foundation::IInspectable const& value2
    );
}
