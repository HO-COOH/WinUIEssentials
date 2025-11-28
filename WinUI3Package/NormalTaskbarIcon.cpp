#include "pch.h"
#include "NormalTaskbarIcon.h"

NormalTaskbarIcon& NormalTaskbarIcon::Icon(HICON value)
{
	m_iconData.hIcon(value);
	return *this;
}
