#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.Collections.h>

template <typename Owner, typename ProjectedElementType>
class VectorView : public winrt::implements<
	VectorView<Owner, ProjectedElementType>,
	winrt::Windows::Foundation::Collections::IVectorView<ProjectedElementType>,
	winrt::Windows::Foundation::Collections::IIterable<ProjectedElementType>
>
{
	winrt::com_ptr<Owner> m_owner;
public:
	VectorView(winrt::com_ptr<Owner> owner) : m_owner{ std::move(owner) } 
	{
	}

	ProjectedElementType GetAt(uint32_t index) 
	{ 
		return m_owner->GetAt(index); 
	}

	uint32_t Size() 
	{ 
		return m_owner->Size(); 
	}

	bool IndexOf(ProjectedElementType const& value, uint32_t& index) 
	{ 
		return m_owner->IndexOf(value, index); 
	}

	uint32_t GetMany(uint32_t startIndex, winrt::array_view<ProjectedElementType> const& items)
	{ 
		return m_owner->GetMany(startIndex, items); 
	}

	winrt::Windows::Foundation::Collections::IIterator<ProjectedElementType> First() 
	{ 
		return m_owner->First(); 
	}
};
