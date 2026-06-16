#pragma once
#include "LanguageRule.h"
#include "Token.h"

namespace ColorCode
{
	class Language
	{
		std::vector<LanguageRule> m_rules;
		std::unordered_set<std::wstring_view> m_keywords;
		std::wregex m_combinedRule;
	public:
		Language(std::vector<LanguageRule> rules, std::unordered_set<std::wstring_view> keywords);
		static Language& Cpp();
		static Language& Xaml();

		static void Tokenize(std::wstring_view source, Language const& language, auto&& onToken)
		{
			if (source.empty())
				return;

			auto const data = source.data();
			auto const length = source.size();

			size_t pos{};
			size_t plainTextStart{};

			auto flushPlainText = [&](size_t end) 
			{
				if (end > plainTextStart)
					onToken(Token{ Scope::PlainText, plainTextStart, end - plainTextStart });
			};

			std::match_results<wchar_t const*> match;
			while (pos < source.size())
			{
				if (std::regex_search(data + pos, data + length, match, language.m_combinedRule, std::regex_constants::match_continuous))
				{
					bool matched{};
					for (size_t i = 1; i < match.size(); ++i)
					{
						//which rule is matched
						if (!match[i].matched || match[i].length() == 0)
							continue;

						auto const& rule = language.m_rules[i - 1];
						auto scope = rule.scope;

						//is this a keyword
						auto const length = static_cast<size_t>(match[i].length());
						std::wstring_view token{ match[i].first, length};
						if (auto iter = language.m_keywords.find(token); iter != language.m_keywords.end())
							scope = Scope::Keyword;
						
						flushPlainText(pos);
						onToken(Token{ scope, pos, length });
						pos += length;
						plainTextStart = pos;
						matched = true;
						break;
					}

					//there should at least one rule matched for C++, so this if should not hit
					if (!matched)
					{
						std::abort();
						++pos;
					}
				}
				else
				{
					//no match
					++pos;
				}
			}

			flushPlainText(pos);
		}
	};
}