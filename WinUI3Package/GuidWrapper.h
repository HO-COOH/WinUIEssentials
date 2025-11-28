/*****************************************************************//**
 * \file   GuidWrapper.h
 * \brief  This class automatically generate a unique GUID upon construction
 *
 * \author Peter
 * \date   August 2024
 *********************************************************************/
#pragma once

/**
 * Automatically generate a unique GUID upon construction and implicitly convert to a `GUID`
 */
struct GuidWrapper : public GUID
{
	GuidWrapper();
};
