#include "pch.h"
#include "HighResTimer.h"
#include <timeapi.h>

HighResTimer& HighResTimer::operator=(bool value)
{
	if (m_enabled != value)
	{
		value ? timeBeginPeriod(1) : timeEndPeriod(1);
		m_enabled = value;
	}
	return *this;
}

HighResTimer::~HighResTimer()
{
	*this = false;
}
