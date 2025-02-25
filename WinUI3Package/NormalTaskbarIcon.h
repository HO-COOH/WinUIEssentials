#pragma once
#include "TaskbarIconBase.h"

class NormalTaskbarIcon : public TaskbarIconBase
{
public:
	NormalTaskbarIcon& Icon(HICON value);
};
