#include "pch.h"
#include "TableColumnVectorView.h"

TableColumnVectorView::TableColumnVectorView(winrt::com_ptr<winrt::PackageRoot::implementation::TableColumnCollection> owner) :
	m_owner{ std::move(owner) }
{
}

winrt::PackageRoot::TableColumn TableColumnVectorView::GetAt(uint32_t index)
{
	return m_owner->GetAt(index);
}

uint32_t TableColumnVectorView::Size()
{
	return m_owner->Size();
}

bool TableColumnVectorView::IndexOf(winrt::PackageRoot::TableColumn const& value, uint32_t& index)
{
	return m_owner->IndexOf(value, index);
}

uint32_t TableColumnVectorView::GetMany(uint32_t startIndex, winrt::array_view<winrt::PackageRoot::TableColumn> items)
{
	return m_owner->GetMany(startIndex, items);
}

winrt::Windows::Foundation::Collections::IIterator<winrt::PackageRoot::TableColumn> TableColumnVectorView::First()
{
	return m_owner->First();
}
