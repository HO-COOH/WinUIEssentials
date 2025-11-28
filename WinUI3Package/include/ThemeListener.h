#pragma once
#include <list>
#include <functional>
#include <optional>
#include <winrt/Microsoft.UI.Xaml.h>
#include "ThemeListenerMessageWindow.h"
#include "Handler.hpp"

/**
 * @brief static class for listening to Windows system theme changes that really works
 * @usage Save an instance of `Token` returned by `ThemeListener::Add(...)`
 */
class ThemeListener
{
	inline static std::optional<ThemeListener>& get();
	inline static ThemeListener& getOrCreate();

	//std::list<std::function<void(winrt::Microsoft::UI::Xaml::ApplicationTheme)>> m_handlers;
	Signal<void> m_handlers;

	ThemeListenerMessageWindow m_messageWindow;
public:
	inline ThemeListener();


	friend class Token;

	template<typename Iter>
	static void Remove(Iter iter)
	{
		auto& handlers = get()->m_handlers;
		handlers.erase(iter);
		if (!handlers.size())
			get().reset();
	}


	class Token
	{
		std::optional<std::remove_reference_t<decltype(m_handlers.end()) >> m_iter{};
	public:
		Token() = default;

		Token(decltype(m_handlers.end()) iter) : m_iter{ iter }
		{
		}

		Token(Token&& rhs) noexcept : m_iter{ std::move(rhs.m_iter) }
		{
			rhs.m_iter.reset();
		}

		Token& operator=(Token&& rhs) noexcept
		{
			m_iter.swap(rhs.m_iter);
			return *this;
		}

		auto get()
		{
			return *m_iter;
		}

		~Token()
		{
			if (m_iter)
				ThemeListener::Remove(*m_iter);
		}
	};

	/**
	 * @brief Add an event handler for theme change
	 * 
	 * @param f Should have a signature of `void(winrt::Microsoft::UI::Xaml::ApplicationTheme)`
	 * @return a `Token` that automatically unregister this handler when it is destructed
	 */
	template<typename Func>
	[[nodiscard]] static Token Add(Func&& f)
	{
		auto& handlers = getOrCreate().m_handlers;
		handlers.emplace_back(std::forward<Func>(f));
		return Token{ --handlers.end() };
	}


	static void Remove(Token token)
	{
		Remove(token.get());
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
