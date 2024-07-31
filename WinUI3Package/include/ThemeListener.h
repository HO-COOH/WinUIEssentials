#pragma once
#include <list>
#include <functional>
#include <optional>
#include <winrt/Microsoft.UI.Xaml.h>
#include "ThemeListenerMessageWindow.h"

class ThemeListener
{
	inline static std::optional<ThemeListener>& get();
	inline static ThemeListener& getOrCreate();

	std::list<std::function<void(winrt::Microsoft::UI::Xaml::ApplicationTheme)>> m_handlers;
	ThemeListenerMessageWindow m_messageWindow;
public:
	inline ThemeListener();

	class Token
	{
		std::optional<std::remove_reference_t<decltype(m_handlers.end())>> m_iter{};
	public:
		Token() = default;

		inline Token(decltype(m_handlers.end()) iter);

		Token(Token&& rhs) noexcept : m_iter{ std::move(rhs.m_iter) } 
		{ 
			rhs.m_iter.reset(); 
		}

		Token& operator=(Token&& rhs) noexcept
		{
			m_iter.swap(rhs.m_iter);
			return *this;
		}

		operator decltype(m_iter)(){ return *m_iter; }
		inline ~Token();

		friend class ThemeListener;
	};

	friend class Token;

	template<typename Func>
	static Token Add(Func&& f)
	{
		auto& handlers = getOrCreate().m_handlers;
		handlers.emplace_back(std::forward<Func>(f));
		return Token{ --handlers.end() };
	}

	inline static void Remove(Token token);

	template<typename Iter>
	static void Remove(Iter iter)
	{
		auto& handlers = get()->m_handlers;
		handlers.erase(iter);
		if (!handlers.size())
			get().reset();
	}

	friend class ThemeListenerMessageWindow;
};


ThemeListener::ThemeListener() : m_messageWindow{ this }
{
}

std::optional<ThemeListener>& ThemeListener::get()
{
	static std::optional<ThemeListener> s_instance{ std::in_place };
	return s_instance;
}

ThemeListener& ThemeListener::getOrCreate()
{
	auto& instance = get();
	if (!instance.has_value())
		instance.emplace();
	return *instance;
}

void ThemeListener::Remove(Token token)
{
	Remove(*token.m_iter);
}

ThemeListener::Token::Token(decltype(m_handlers.end()) iter) : m_iter{ iter }
{
}

ThemeListener::Token::~Token()
{
	if (m_iter)
		ThemeListener::Remove(*m_iter);
}
