#pragma once
/*****************************************************************//**
 * \file   GuidWrapper.h
 * \brief  This class automatically generate a unique GUID upon construction
 * 
 * \author Peter
 * \date   August 2024
 *********************************************************************/
struct GuidWrapper : public GUID
{
	GuidWrapper();
};
