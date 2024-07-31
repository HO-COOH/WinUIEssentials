#include "pch.h"
#include "ThemeListener.h"

ThemeListener::~ThemeListener()
{
}

std::optional<ThemeListener>& ThemeListener::get()
{
	static std::optional<ThemeListener> s_instance;
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
	auto& handlers = get()->m_handlers;
	handlers.erase(token);
	if (!handlers.size())
		get().reset();
}
