#include "pch.h"
#include "GuidWrapper.h"

GuidWrapper::GuidWrapper()
{
	winrt::check_hresult(CoCreateGuid(this));
}
