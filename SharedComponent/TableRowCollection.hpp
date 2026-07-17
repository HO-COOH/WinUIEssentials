#pragma once
#include <winrt/base.h>
#include "VectorBase.hpp"

struct TableRowCollection : 
	winrt::implements<
		TableRowCollection,
		winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::TableRow>,
		winrt::Windows::Foundation::Collections::IVectorView<winrt::PackageRoot::TableRow>
	>, 
	VectorBase<
		TableRowCollection, 
		winrt::PackageRoot::TableRow, 
		winrt::com_ptr<winrt::PackageRoot::implementation::TableRow>
	>
{
	static winrt::PackageRoot::TableRow to_projected(winrt::com_ptr<winrt::PackageRoot::implementation::TableRow> const& stored)
	{
		return *stored;
	}

	static winrt::com_ptr<winrt::PackageRoot::implementation::TableRow> to_stored(winrt::PackageRoot::TableRow const& value)
	{
		return winrt::get_self<winrt::PackageRoot::implementation::TableRow>(value)->get_strong();
	}

	static bool is_same(winrt::com_ptr<winrt::PackageRoot::implementation::TableRow> const& stored, winrt::PackageRoot::TableRow const& value)
	{
		return stored.get() == winrt::get_self<winrt::PackageRoot::implementation::TableRow>(value);
	}
};
