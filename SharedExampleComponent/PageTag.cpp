#include "pch.h"
#include "PageTag.h"

std::vector<PageTag>& PageTag::Registry()
{
	static std::vector<PageTag> s_registry;
	return s_registry;
}
