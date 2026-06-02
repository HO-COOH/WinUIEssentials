#pragma once

namespace ColorCode
{
	namespace Cpp
	{
		constexpr static auto BlockComment = LR"(\/\*[\s\S]*?\*\/)";
		constexpr static auto LineComment = LR"(\/\/[^\r\n]*)";
		constexpr static auto Preprocessor = LR"(#[^\r\n]*)";
		constexpr static wchar_t const* Keywords[]
		{
			L"alignas",
			L"alignof",
			L"and",
			L"and_eq",
			L"asm",
			L"atomic_cancel",
			L"atomic_commit",
			L"atomic_noexcept",
			L"auto",
			L"bitand ",
			L"bitor ",
			L"bool",
			L"break",
			L"case",
			L"catch",
			L"char",
			L"char8_t",
			L"char16_t",
			L"char32_t",
			L"class",
			L"compl",
			L"concept",
			L"const",
			L"consteval",
			L"constexpr",
			L"constinit ",
			L"const_cast",
			L"continue",
			L"contract_assert",
			L"co_await",
			L"co_return",
			L"co_yield",
			L"decltype",
			L"default",
			L"delete",
			L"do",
			L"double",
			L"dynamic_cast",
			L"else",
			L"enum",
			L"explicit",
			L"export",
			L"extern",
			L"false",
			L"float",
			L"for",
			L"friend",
			L"goto",
			L"if",
			L"inline",
			L"int",
			L"long",
			L"mutable",
			L"namespace",
			L"new",
			L"noexcept ",
			L"not",
			L"not_eq",
			L"nullptr",
			L"operator",
			L"or",
			L"or_eq ",
			L"private",
			L"protected",
			L"public",
			L"reflexpr",
			L"register",
			L"reinterpret_cast",
			L"requires",
			L"return",
			L"short",
			L"signed",
			L"sizeof",
			L"static",
			L"static_assert ",
			L"static_cast",
			L"struct",
			L"switch",
			L"synchronized",
			L"template",
			L"this",
			L"thread_local ",
			L"throw",
			L"true",
			L"try",
			L"typedef",
			L"typeid",
			L"typename",
			L"union",
			L"unsigned",
			L"using",
			L"virtual",
			L"void",
			L"volatile",
			L"wchar_t",
			L"while",
			L"xor",
			L"xor_eq"
		};

		//https://cppreference.com/cpp/language/operators
		constexpr static auto Operator = LR"([+\-*\/%^&|~!=<>,]|\+=|-=|\*=|\/=|%=|\^=|&=|\|=|<<|>>|>>=|<<=|==|!=|<=|>=|<=>|&&|\|\|\+\+|--|->|->*)";
		constexpr static auto Identifier = LR"([A-Za-z][A-Za-z0-9_]*)";
		constexpr static auto Function = LR"([A-Za-z][A-Za-z0-9_]*(?=\s*\())";
		constexpr static auto UserType = LR"([A-Z][A-Za-z0-9_]*)"; //only captital letter heuristics, might be incorrect, but good enough for coloring code
		constexpr static auto TemplateType = LR"([A-Za-z_][A-Za-z0-9_]*(?:::[A-Za-z_][A-Za-z0-9_]*)*<[^<>;{}()]*(?:<[^<>;{}()]*>[^<>;{}()]*)*>)";
		constexpr static auto NamespaceQualifier = LR"([A-Za-z_][A-Za-z0-9_]*(?=::))";
		constexpr static auto String = LR"((?:u8|u16|u32|[LuU])?"(?:\\(?:.|\n)|[^"\\])*")";
	}
}