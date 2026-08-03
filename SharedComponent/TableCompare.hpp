#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>

//Best-effort string form of a cell for lexical comparison.
inline winrt::hstring GetString(winrt::Windows::Foundation::IInspectable const& value)
{
    if (!value)
        return {};
    if (auto const str = value.try_as<winrt::hstring>())
        return *str;
    if (auto const pv = value.try_as<winrt::Windows::Foundation::IPropertyValue>(); pv && pv.Type() == winrt::Windows::Foundation::PropertyType::String)
        return pv.GetString();
    return {};
}

inline std::partial_ordering compareObject(
    winrt::Windows::Foundation::IInspectable const& lhs,
    winrt::Windows::Foundation::IInspectable const& rhs)
{
    auto const lhsValue = lhs.as<winrt::Windows::Foundation::IPropertyValue>();
    auto const rhsValue = rhs.as<winrt::Windows::Foundation::IPropertyValue>();

    switch (lhsValue.Type())
    {
        case winrt::Windows::Foundation::PropertyType::Int16: return lhsValue.GetInt16() <=> rhsValue.GetInt16();
        case winrt::Windows::Foundation::PropertyType::Int32: return lhsValue.GetInt32() <=> rhsValue.GetInt32();
        case winrt::Windows::Foundation::PropertyType::Int64: return lhsValue.GetInt64() <=> rhsValue.GetInt64();
        case winrt::Windows::Foundation::PropertyType::UInt8: return lhsValue.GetUInt8() <=> rhsValue.GetUInt8();
        case winrt::Windows::Foundation::PropertyType::UInt16: return lhsValue.GetUInt16() <=> rhsValue.GetUInt16();
        case winrt::Windows::Foundation::PropertyType::UInt32: return lhsValue.GetUInt32() <=> rhsValue.GetUInt32();
        case winrt::Windows::Foundation::PropertyType::UInt64: return lhsValue.GetUInt64() <=> rhsValue.GetUInt64();
        case winrt::Windows::Foundation::PropertyType::Single: return lhsValue.GetSingle() <=> rhsValue.GetSingle();
        case winrt::Windows::Foundation::PropertyType::Double: return lhsValue.GetDouble() <=> rhsValue.GetDouble();
        case winrt::Windows::Foundation::PropertyType::Boolean: return lhsValue.GetBoolean() <=> rhsValue.GetBoolean();
        case winrt::Windows::Foundation::PropertyType::String:
            return std::wstring_view{ GetString(lhs) } <=> std::wstring_view{ GetString(rhs) };
        default:
            throw std::invalid_argument("Unsupported property type for comparison");
    }
}