#pragma once
#include <list>
#include <functional>
#include <optional>
#include <winrt/Microsoft.UI.Xaml.h>

class ThemeListener
{
	ThemeListener() = default;

	~ThemeListener();

	static std::optional<ThemeListener>& get();
	static ThemeListener& getOrCreate();

	std::list<std::function<void(winrt::Microsoft::UI::Xaml::ApplicationTheme)>> m_handlers;
public:

	using Token = decltype(m_handlers.end());

	template<typename Func>
	static Token Add(Func&& f)
	{
		auto& handlers = getOrCreate().m_handlers;
		handlers.emplace_back(std::forward<Func>(f));
		return --m_handlers.end();
	}

	static void Remove(Token token);
};
