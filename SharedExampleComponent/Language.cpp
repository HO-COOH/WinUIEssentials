#include "pch.h"
#include "Language.h"
#include <numeric>
#include "Language.Cpp.h"
#include "Language.Xaml.h"

namespace ColorCode
{
    static std::wregex combineRules(std::vector<LanguageRule> const& rules)
    {
        return std::wregex
        {
            std::accumulate(
                rules.begin(),
                rules.end(),
                std::wstring{},
                [](std::wstring result, LanguageRule const& current)
                {
                    return result += result.empty() ? std::format(L"({})", current.rawText) : std::format(L"|({})", current.rawText);
                }
            ),
            std::regex_constants::ECMAScript | std::regex_constants::optimize
        };
    }

    Language::Language(std::vector<LanguageRule> rules, std::unordered_set<std::wstring_view> keywords) : 
        m_rules{std::move(rules)}, 
        m_combinedRule{combineRules(m_rules) },
        m_keywords{std::move(keywords)}
    {
    }

    Language& Language::Cpp()
    {
        static auto cppLanguage = [] {
            Language language
            {
                {
					LanguageRule{Cpp::BlockComment, Scope::Comment},
                    LanguageRule{Cpp::LineComment, Scope::Comment},
                    LanguageRule{Cpp::Preprocessor, Scope::Preprocessor},
                    LanguageRule{Cpp::String, Scope::String},
                    LanguageRule{Cpp::Operator, Scope::Operator},
                    LanguageRule{Cpp::TemplateType, Scope::Type},
                    LanguageRule{Cpp::NamespaceQualifier, Scope::Namespace},
                    LanguageRule{Cpp::Function, Scope::Function},
                    LanguageRule{Cpp::UserType, Scope::Type},
                    LanguageRule{Cpp::Identifier, Scope::Identifier},
                },
                std::unordered_set<std::wstring_view>{ std::cbegin(Cpp::Keywords), std::cend(Cpp::Keywords) }
            };
            return language;
        }();
        return cppLanguage;
    }

    Language& Language::Xaml()
    {
        static auto xamlLanguage = [] {
            Language language
            {
                {
                    LanguageRule{Xaml::Comment, Scope::Comment},
                    LanguageRule{Xaml::MarkupValueOpenQuote, Scope::PlainText},
                    LanguageRule{Xaml::MarkupValueCloseQuote, Scope::PlainText},
                    LanguageRule{Xaml::String, Scope::String},
                    LanguageRule{Xaml::Intrinsic, Scope::Keyword},
                    LanguageRule{Xaml::MarkupExtension, Scope::Keyword},
                    LanguageRule{Xaml::Property, Scope::Identifier},
                    LanguageRule{Xaml::UserType, Scope::Type},
                    LanguageRule{Xaml::Identifier, Scope::Identifier},
                },
                std::unordered_set<std::wstring_view>{}
            };
            return language;
        }();
        return xamlLanguage;
    }
}
