#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/base.h>
#include "IteratorBase.hpp"
#include "VectorViewBase.hpp"
#include <vector>
#include <algorithm>
#include <concepts>
#include <type_traits>

//Base providing IVector<ProjectedElementType> + IIterable<ProjectedElementType> on top of an
//owned `std::vector<ElementType>` (exposed as the public member m_data).
//Default conversions are provided when `ElementType` is `ProjectedElementType` or `winrt::com_ptr<Impl>`.
//For custom `ElementType`, the derived type needs to define:
//  static ProjectedElementType to_projected(ElementType const&);
//  static ElementType to_stored(ProjectedElementType const&);
//  static bool is_same(ElementType const&, ProjectedElementType const&);
template <typename ProjectedElementType, typename ElementType = ProjectedElementType>
class VectorBase
{
	template <typename T>
	struct is_com_ptr : std::false_type {};

	template <typename T>
	struct is_com_ptr<winrt::com_ptr<T>> : std::true_type
	{
		using implementation_type = T;
	};

	static constexpr bool has_default_conversion = std::same_as<ProjectedElementType, ElementType> || is_com_ptr<ElementType>::value;

public:
	std::vector<ElementType> m_data;

	static decltype(auto) to_projected(ElementType const& stored) noexcept 
		requires has_default_conversion
	{
		if constexpr (std::same_as<ProjectedElementType, ElementType>)
			return stored;
		else
			return stored ? ProjectedElementType{ *stored } : ProjectedElementType{ nullptr };
	}

	static ElementType to_stored(ProjectedElementType const& value)
		requires has_default_conversion
	{
		if constexpr (std::same_as<ProjectedElementType, ElementType>)
			return value;
		else
			return value ? winrt::get_self<typename is_com_ptr<ElementType>::implementation_type>(value)->get_strong() : nullptr;
	}

	static bool is_same(ElementType const& stored, ProjectedElementType const& value)
		requires has_default_conversion
	{
		if constexpr (std::same_as<ProjectedElementType, ElementType>)
			return stored == value;
		else
			return stored.get() == (value ? winrt::get_self<typename is_com_ptr<ElementType>::implementation_type>(value) : nullptr);
	}

	winrt::Windows::Foundation::Collections::IIterator<ProjectedElementType> First(this auto& self)
	{
		return winrt::make<Iterator<std::remove_reference_t<decltype(self)>, ProjectedElementType>>(self.get_strong());
	}

	template <typename Derived>
	ProjectedElementType GetAt(this Derived const& self, uint32_t index)
	{
		if (index >= self.m_data.size())
			throw winrt::hresult_out_of_bounds();
		return Derived::to_projected(self.m_data[index]);
	}

	uint32_t Size() const noexcept
	{
		return static_cast<uint32_t>(m_data.size());
	}

	winrt::Windows::Foundation::Collections::IVectorView<ProjectedElementType> GetView(this auto& self)
	{
		if constexpr (std::convertible_to<decltype(self), winrt::Windows::Foundation::Collections::IVectorView<ProjectedElementType>>)
			return self;
		else
			return winrt::make<VectorView<std::remove_reference_t<decltype(self)>, ProjectedElementType>>(self.get_strong());
	}

	template<typename Derived>
	bool IndexOf(this Derived const& self, ProjectedElementType const& value, uint32_t& index)
	{
		auto const it = std::ranges::find_if(
			self.m_data,
			[&value](auto const& entry) { return Derived::is_same(entry, value); }
		);
		if (it == self.m_data.end())
		{
			index = 0;
			return false;
		}
		index = static_cast<uint32_t>(std::distance(self.m_data.begin(), it));
		return true;
	}

	template<typename Derived>
	void SetAt(this Derived& self, uint32_t index, ProjectedElementType const& value)
	{
		if (index >= self.m_data.size())
			throw winrt::hresult_out_of_bounds();
		self.m_data[index] = Derived::to_stored(value);
	}

	template<typename Derived>
	void InsertAt(this Derived& self, uint32_t index, ProjectedElementType const& value)
	{
		if (index > self.m_data.size())
			throw winrt::hresult_out_of_bounds();
		self.m_data.insert(self.m_data.begin() + index, Derived::to_stored(value));
	}

	void RemoveAt(uint32_t index)
	{
		if (index >= m_data.size())
			throw winrt::hresult_out_of_bounds();
		m_data.erase(m_data.begin() + index);
	}

	template<typename Derived>
	void Append(this Derived& self, ProjectedElementType const& value)
	{
		self.m_data.push_back(Derived::to_stored(value));
	}

	void RemoveAtEnd()
	{
		if (m_data.empty())
			throw winrt::hresult_out_of_bounds();
		m_data.pop_back();
	}

	void Clear() noexcept
	{
		m_data.clear();
	}

	template<typename Derived>
	uint32_t GetMany(this Derived const& self, uint32_t startIndex, winrt::array_view<ProjectedElementType> items)
	{
		if (startIndex >= self.m_data.size())
			return 0;
		auto const available = static_cast<uint32_t>(self.m_data.size()) - startIndex;
		auto const count = (std::min)(available, static_cast<uint32_t>(items.size()));
		for (uint32_t i = 0; i < count; ++i)
			items[i] = Derived::to_projected(self.m_data[startIndex + i]);
		return count;
	}

	template<typename Derived>
	void ReplaceAll(this Derived& self, winrt::array_view<ProjectedElementType const> items)
	{
		self.m_data.resize(items.size());
		std::ranges::transform(items, self.m_data.begin(), &Derived::to_stored);
	}
};
