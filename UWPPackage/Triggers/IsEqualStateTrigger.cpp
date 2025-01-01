#include "pch.h"
#include "IsEqualStateTrigger.h"
#if __has_include("IsEqualStateTrigger.g.cpp")
#include "IsEqualStateTrigger.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
	winrt::Windows::UI::Xaml::DependencyProperty IsEqualStateTrigger::m_valueProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<UWPPackage::IsEqualStateTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				nullptr, &IsEqualStateTrigger::onValuePropertyChanged }
	);

	winrt::Windows::UI::Xaml::DependencyProperty IsEqualStateTrigger::m_toProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"To",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<UWPPackage::IsEqualStateTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				nullptr, &IsEqualStateTrigger::onValuePropertyChanged }
	);


	winrt::Windows::Foundation::IInspectable IsEqualStateTrigger::Value()
	{
		return GetValue(m_valueProperty);
	}

	void IsEqualStateTrigger::Value(winrt::Windows::Foundation::IInspectable value)
	{
		SetValue(m_valueProperty, value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty IsEqualStateTrigger::ValueProperty()
	{
		return m_valueProperty;
	}

	winrt::Windows::Foundation::IInspectable IsEqualStateTrigger::To()
	{
		return GetValue(m_toProperty);
	}

	void IsEqualStateTrigger::To(winrt::Windows::Foundation::IInspectable value)
	{
		SetValue(m_toProperty, value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty IsEqualStateTrigger::ToProperty()
	{
		return m_toProperty;
	}

	void IsEqualStateTrigger::onValuePropertyChanged(
		winrt::Windows::UI::Xaml::DependencyObject d,
		winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<IsEqualStateTrigger>(d.as<UWPPackage::IsEqualStateTrigger>())->updateTrigger();
	}

	void IsEqualStateTrigger::updateTrigger()
	{
		bool isActive = false;

		auto value = Value();
		auto to = To();

		if (value && to)
		{
			isActive = convertTypeEquals(value, to);
		}
		else if (!value && !to)
		{
			isActive = true;
		}

		SetActive(isActive);
	}

	bool IsEqualStateTrigger::isStringComparable(
		winrt::Windows::Foundation::PropertyType type1,
		winrt::Windows::Foundation::PropertyType type2
	)
	{
		if (type1 != winrt::Windows::Foundation::PropertyType::String && type2 != winrt::Windows::Foundation::PropertyType::String)
			return false;
		//here only type1 or type2 is string

		//if type1 is string and type 2 is not, do a swap to check
		if(type1 == winrt::Windows::Foundation::PropertyType::String)
			return isStringComparable(type2, type1);

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

	bool IsEqualStateTrigger::isStringCompareEqual(
		winrt::Windows::Foundation::IInspectable object1,
		winrt::Windows::Foundation::IInspectable object2,
		winrt::Windows::Foundation::PropertyType type1,
		winrt::Windows::Foundation::PropertyType type2
	)
	{
		//here only type1 or type2 is string
		//if type1 is string and type 2 is not, do a swap to compare
		if (type1 == winrt::Windows::Foundation::PropertyType::String)
			return isStringCompareEqual(object2, object1, type2, type1);

		//now type1 is not string, type2 is string
		//we convert type1 to string then do the compare
		switch (type1)
		{
			case winrt::Windows::Foundation::PropertyType::Int64:  //1
				return winrt::to_hstring(winrt::unbox_value<int64_t>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::Double: //2
				return winrt::to_hstring(winrt::unbox_value<double>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::Single: //3
				return winrt::to_hstring(winrt::unbox_value<float>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::Char16: //4
				return winrt::to_hstring(winrt::unbox_value<char16_t>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::Int32:  //5
				return winrt::to_hstring(winrt::unbox_value<int32_t>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::Int16:  //6
				return winrt::to_hstring(winrt::unbox_value<int16_t>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			//case winrt::Windows::Foundation::PropertyType::Int8: there is no int8
			case winrt::Windows::Foundation::PropertyType::UInt64: //8
				return winrt::to_hstring(winrt::unbox_value<uint64_t>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::UInt8:  //9
				return winrt::to_hstring(winrt::unbox_value<uint8_t>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::UInt32: //10
				return winrt::to_hstring(winrt::unbox_value<uint32_t>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::UInt16: //11
				return winrt::to_hstring(winrt::unbox_value<uint16_t>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::Guid:   //12
				return winrt::to_hstring(winrt::unbox_value<winrt::guid>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::Boolean: //14
				return winrt::to_hstring(winrt::unbox_value<bool>(object1)) == winrt::unbox_value<winrt::hstring>(object2);
			default:
				assert(false);
		}
	}

	bool IsEqualStateTrigger::convertTypeEquals(
		winrt::Windows::Foundation::IInspectable object1,
		winrt::Windows::Foundation::IInspectable object2
	)
	{
		////try string
		//{
		//	auto object1Converted = object1.try_as<winrt::hstring>();
		//	auto object2Converted = object2.try_as<winrt::hstring>();
		//	if (object1Converted && object2Converted)
		//		return object1Converted == object2Converted;
		//}
		//{
		//	auto object1Converted = winrt::unbox_value<ContentAlignment>(object1);
		//	auto object2Converted = object2.try_as<winrt::hstring>();
		//	switch (object1Converted)
		//	{
		//	case winrt::UWPPackage::ContentAlignment::Right:
		//		return object2Converted == L"Right";
		//	case winrt::UWPPackage::ContentAlignment::Left:
		//		return object2Converted == L"Left";
		//	case winrt::UWPPackage::ContentAlignment::Vertical:
		//		return object2Converted == L"Vertical";
		//	default:
		//		false;
		//	}
		//}
		////try object comparison
		//{
		//	return object1 == object2;
		//}

		auto object1AsPropertyValue = object1.try_as<winrt::Windows::Foundation::IPropertyValue>();
		auto object2AsPropertyValue = object2.try_as<winrt::Windows::Foundation::IPropertyValue>();
		auto type1 = object1AsPropertyValue.Type();
		auto type2 = object2AsPropertyValue.Type();

		//check if any type is unsupported
		if (type1 == winrt::Windows::Foundation::PropertyType::OtherType || type2 == winrt::Windows::Foundation::PropertyType::OtherType)
		{
			//unsupported type maybe a enum, and can be unboxed to int32
			if (type1 == winrt::Windows::Foundation::PropertyType::OtherType && type2 == winrt::Windows::Foundation::PropertyType::OtherType)
			{
				auto tryEnumValue1 = object1.try_as<int32_t>();
				auto tryEnumValue2 = object2.try_as<int32_t>();
				if (tryEnumValue1 && tryEnumValue2)
					return *tryEnumValue1 == *tryEnumValue2;
			}
			return false;
		}

		//check if both are string
		if (type1 == winrt::Windows::Foundation::PropertyType::String && type2 == winrt::Windows::Foundation::PropertyType::String)
			return winrt::unbox_value<winrt::hstring>(object1) == winrt::unbox_value<winrt::hstring>(object2);

		//check if one type is string and another can be converted
		if (isStringComparable(type1, type2))
			return isStringCompareEqual(object1, object2, type1, type2);

		//now we need to ensure both type are same before unbox and compare
		if (type1 != type2)
			return false;

		//now both types are same and we do unbox and compare
		switch (type1)
		{
			case winrt::Windows::Foundation::PropertyType::Empty:
				return true;
			case winrt::Windows::Foundation::PropertyType::UInt8:
				return winrt::unbox_value<uint8_t>(object1) == winrt::unbox_value<uint8_t>(object2);
			case winrt::Windows::Foundation::PropertyType::Int16:
				return winrt::unbox_value<int16_t>(object1) == winrt::unbox_value<int16_t>(object2);
			case winrt::Windows::Foundation::PropertyType::UInt16:
				return winrt::unbox_value<uint16_t>(object1) == winrt::unbox_value<uint16_t>(object2);
			case winrt::Windows::Foundation::PropertyType::Int32:
				return winrt::unbox_value<int32_t>(object1) == winrt::unbox_value<int32_t>(object2);
			case winrt::Windows::Foundation::PropertyType::UInt32:
				return winrt::unbox_value<uint32_t>(object1) == winrt::unbox_value<uint32_t>(object2);
			case winrt::Windows::Foundation::PropertyType::Int64:
				return winrt::unbox_value<int64_t>(object1) == winrt::unbox_value<int64_t>(object2);
			case winrt::Windows::Foundation::PropertyType::UInt64:
				return winrt::unbox_value<uint64_t>(object1) == winrt::unbox_value<uint64_t>(object2);
			case winrt::Windows::Foundation::PropertyType::Single:
				return winrt::unbox_value<float>(object1) == winrt::unbox_value<float>(object2);
			case winrt::Windows::Foundation::PropertyType::Double:
				return winrt::unbox_value<double>(object1) == winrt::unbox_value<double>(object2);
			case winrt::Windows::Foundation::PropertyType::Char16:
				return winrt::unbox_value<char16_t>(object1) == winrt::unbox_value<char16_t>(object2);
			case winrt::Windows::Foundation::PropertyType::Boolean:
				return winrt::unbox_value<bool>(object1) == winrt::unbox_value<bool>(object2);
			case winrt::Windows::Foundation::PropertyType::String:
				return winrt::unbox_value<winrt::hstring>(object1) == winrt::unbox_value<winrt::hstring>(object2);
			case winrt::Windows::Foundation::PropertyType::Inspectable:
				return false;
			case winrt::Windows::Foundation::PropertyType::DateTime:
				return winrt::unbox_value<winrt::Windows::Foundation::DateTime>(object1) == winrt::unbox_value<winrt::Windows::Foundation::DateTime>(object2);
			case winrt::Windows::Foundation::PropertyType::TimeSpan:
				return winrt::unbox_value<winrt::Windows::Foundation::TimeSpan>(object1) == winrt::unbox_value<winrt::Windows::Foundation::TimeSpan>(object2);
			case winrt::Windows::Foundation::PropertyType::Guid:
				return winrt::unbox_value<winrt::guid>(object1) == winrt::unbox_value<winrt::guid>(object2);
			case winrt::Windows::Foundation::PropertyType::Point:
				return winrt::unbox_value<winrt::Windows::Foundation::Point>(object1) == winrt::unbox_value<winrt::Windows::Foundation::Point>(object2);
			case winrt::Windows::Foundation::PropertyType::Size:
				return winrt::unbox_value<winrt::Windows::Foundation::Size>(object1) == winrt::unbox_value<winrt::Windows::Foundation::Size>(object2);
			case winrt::Windows::Foundation::PropertyType::Rect:
				return winrt::unbox_value<winrt::Windows::Foundation::Rect>(object1) == winrt::unbox_value<winrt::Windows::Foundation::Rect>(object2);
			case winrt::Windows::Foundation::PropertyType::OtherType:
				return false;
			case winrt::Windows::Foundation::PropertyType::UInt8Array:
			case winrt::Windows::Foundation::PropertyType::Int16Array:
			case winrt::Windows::Foundation::PropertyType::UInt16Array:
			case winrt::Windows::Foundation::PropertyType::Int32Array:
			case winrt::Windows::Foundation::PropertyType::UInt32Array:
			case winrt::Windows::Foundation::PropertyType::Int64Array:
			case winrt::Windows::Foundation::PropertyType::UInt64Array:
			case winrt::Windows::Foundation::PropertyType::SingleArray:
			case winrt::Windows::Foundation::PropertyType::DoubleArray:
			case winrt::Windows::Foundation::PropertyType::Char16Array:
			case winrt::Windows::Foundation::PropertyType::BooleanArray:
			case winrt::Windows::Foundation::PropertyType::StringArray:
			case winrt::Windows::Foundation::PropertyType::InspectableArray:
			case winrt::Windows::Foundation::PropertyType::DateTimeArray:
			case winrt::Windows::Foundation::PropertyType::TimeSpanArray:
			case winrt::Windows::Foundation::PropertyType::GuidArray:
			case winrt::Windows::Foundation::PropertyType::PointArray:
			case winrt::Windows::Foundation::PropertyType::SizeArray:
			case winrt::Windows::Foundation::PropertyType::RectArray:
			case winrt::Windows::Foundation::PropertyType::OtherTypeArray:
			default:
				return false;
		}
	}
}
