#pragma once
#include "NotifyIconData.h"
#include <string_view>
class TaskbarIconBase
{
protected:
	NotifyIconData m_iconData;
public:
	TaskbarIconBase();

	TaskbarIconBase& ToolTip(std::wstring_view value);
	
	void Show();
	void Remove();
	
	~TaskbarIconBase();
};
