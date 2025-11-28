#pragma once

class PopupMenu;

struct PopupMenuFlyoutItemImplBase
{
	PopupMenu* m_parentMenuPtr{};
	HMENU m_parentMenu{};
	int index{};
};
