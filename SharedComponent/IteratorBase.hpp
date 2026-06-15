#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.Collections.h>

template <typename Owner, typename ProjectedElementType>
struct Iterator : winrt::implements<
	Iterator<Owner, ProjectedElementType>,
	winrt::Windows::Foundation::Collections::IIterator<ProjectedElementType>
>
{
	Iterator(winrt::com_ptr<Owner> owner) : m_owner{ std::move(owner) } {}

	ProjectedElementType Current()
	{
		auto const& data = m_owner->m_data;
		if (m_index >= data.size())
			throw winrt::hresult_out_of_bounds();
		return Owner::to_projected(data[m_index]);
	}

	bool HasCurrent() const noexcept
	{
		return m_index < m_owner->m_data.size();
	}

	bool MoveNext() noexcept
	{
		auto const& data = m_owner->m_data;
		if (m_index < data.size())
			++m_index;
		return m_index < data.size();
	}

	uint32_t GetMany(winrt::array_view<ProjectedElementType> items)
	{
		auto const& data = m_owner->m_data;
		auto const size = static_cast<uint32_t>(data.size());
		if (m_index >= size)
			return 0;
		auto const count = (std::min)(size - m_index, static_cast<uint32_t>(items.size()));
		for (uint32_t i = 0; i < count; ++i)
			items[i] = Owner::to_projected(data[m_index + i]);
		m_index += count;
		return count;
	}

private:
	winrt::com_ptr<Owner> m_owner;
	uint32_t m_index{};
};