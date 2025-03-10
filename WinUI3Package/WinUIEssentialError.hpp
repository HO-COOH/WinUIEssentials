#pragma once
#include <format>
#include <concepts>
#include <string_view>
/**
 * @brief Wrapper for unified errors in the whole WinUIEssential package
 * @details We want the library consumers are able to quickly search for errors through the 
 * output window in visual studio, so we need to have a unified formatting to error message
 * 
 * @tparam ErrorType Should be a winrt::hresult_error type
 */
template<typename ErrorType>
requires std::derived_from<ErrorType, winrt::hresult_error>
struct WinUIEssentialError : ErrorType
{
	WinUIEssentialError(std::wstring_view msg) :
		ErrorType
		{ 
			std::format(
				L"WinUIEssentials Error: {}. Please report or visit -> https://github.com/HO-COOH/WinUIEssentials "
				L"for documentation or reporting the bug.", 
				msg
			) 
		} 
	{
	}

};

struct GetterNotImplemented : WinUIEssentialError<winrt::hresult_not_implemented>
{
	GetterNotImplemented(std::wstring_view method) :
		WinUIEssentialError{ std::format(L"Getter of {} is not implemented. You should save the property you set in a member variable.", method) }
	{
	}
};