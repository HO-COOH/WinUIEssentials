#pragma once
#include <winrt/base.h>
#include "TableRow.h"
#include "VectorBase.hpp"

struct TableRowCollection : 
	winrt::implements<
		TableRowCollection,
		winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::TableRow>,
		winrt::Windows::Foundation::Collections::IVectorView<winrt::PackageRoot::TableRow>
	>, 
	VectorBase<
		winrt::PackageRoot::TableRow, 
		winrt::com_ptr<winrt::PackageRoot::implementation::TableRow>
	>
{
};
