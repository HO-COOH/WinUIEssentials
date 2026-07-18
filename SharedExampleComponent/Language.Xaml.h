#pragma once

namespace ColorCode
{
	namespace Xaml
	{
		constexpr static auto Comment = LR"(<!--[\s\S]*?-->)";
		constexpr static auto TextContent = LR"(>[^<]*)";
		constexpr static auto String = LR"("[^"{]*"|'[^'{]*')";
		constexpr static auto MarkupValueOpenQuote = LR"(["'](?=\{))";
		constexpr static auto MarkupValueCloseQuote = LR"(\}["'])";
		constexpr static auto Intrinsic = LR"(x:[A-Za-z][A-Za-z0-9]*)";
		constexpr static auto MarkupExtension = LR"(\{[A-Za-z_]*(?::[A-Za-z_][A-Za-z0-9_]*)?)";
		constexpr static auto Property = LR"([A-Za-z_][A-Za-z0-9_]*(?:[.:][A-Za-z_][A-Za-z0-9_]*)*(?=\s*=))";
		constexpr static auto UserType = LR"((?:[A-Za-z_][A-Za-z0-9_]*:)?[A-Z][A-Za-z0-9_]*(?:\.[A-Z][A-Za-z0-9_]*)?)";
		constexpr static auto Identifier = LR"([A-Za-z_][A-Za-z0-9_]*)";
	}
}
