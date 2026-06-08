#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/base.h>
#include "IteratorBase.hpp"
#include "VectorViewBase.hpp"
#include <vector>
#include <algorithm>

//CRTP base providing IVector<ProjectedElementType> + IIterable<ProjectedElementType> on top of an
//owned `std::vector<ElementType>` (exposed as the public member m_data).
//Derived type needs to define these 3 functions:
//  static ProjectedElementType to_projected(ElementType const&);
//  static ElementType to_stored(ProjectedElementType const&);
//  static bool is_same(ElementType const&, ProjectedElementType const&);

template <typename Derived, typename ProjectedElementType, typename ElementType>
class VectorBase
{
	Derived& self() { return *static_cast<Derived*>(this); }
public:
	std::vector<ElementType> m_data;

	winrt::Windows::Foundation::Collections::IIterator<ProjectedElementType> First()
	{
		return winrt::make<Iterator<Derived, ProjectedElementType>>(self().get_strong());
	}

	ProjectedElementType GetAt(uint32_t index)
	{
		if (index >= m_data.size())
			throw winrt::hresult_out_of_bounds();
		return Derived::to_projected(m_data[index]);
	}

	uint32_t Size()
	{
		return static_cast<uint32_t>(m_data.size());
	}

	winrt::Windows::Foundation::Collections::IVectorView<ProjectedElementType> GetView()
	{
		return winrt::make<VectorView<Derived, ProjectedElementType>>(self().get_strong());
	}

	bool IndexOf(ProjectedElementType const& value, uint32_t& index)
	{
		auto const it = std::ranges::find_if(
			m_data,
			[&value](auto const& entry) { return Derived::is_same(entry, value); }
		);
		if (it == m_data.end())
		{
			index = 0;
			return false;
		}
		index = static_cast<uint32_t>(std::distance(m_data.begin(), it));
		return true;
	}

	void SetAt(uint32_t index, ProjectedElementType const& value)
	{
		if (index >= m_data.size())
			throw winrt::hresult_out_of_bounds();
		m_data[index] = Derived::to_stored(value);
	}

	void InsertAt(uint32_t index, ProjectedElementType const& value)
	{
		if (index > m_data.size())
			throw winrt::hresult_out_of_bounds();
		m_data.insert(m_data.begin() + index, Derived::to_stored(value));
	}

	void RemoveAt(uint32_t index)
	{
		if (index >= m_data.size())
			throw winrt::hresult_out_of_bounds();
		m_data.erase(m_data.begin() + index);
	}

	void Append(ProjectedElementType const& value)
	{
		m_data.push_back(Derived::to_stored(value));
	}

	void RemoveAtEnd()
	{
		if (m_data.empty())
			throw winrt::hresult_out_of_bounds();
		m_data.pop_back();
	}

	void Clear()
	{
		m_data.clear();
	}

	uint32_t GetMany(uint32_t startIndex, winrt::array_view<ProjectedElementType> items)
	{
		if (startIndex >= m_data.size())
			return 0;
		auto const available = static_cast<uint32_t>(m_data.size()) - startIndex;
		auto const count = (std::min)(available, static_cast<uint32_t>(items.size()));
		for (uint32_t i = 0; i < count; ++i)
			items[i] = Derived::to_projected(m_data[startIndex + i]);
		return count;
	}

	void ReplaceAll(winrt::array_view<ProjectedElementType const> items)
	{
		m_data.resize(items.size());
		std::ranges::transform(items, m_data.begin(), &Derived::to_stored);
	}
};
