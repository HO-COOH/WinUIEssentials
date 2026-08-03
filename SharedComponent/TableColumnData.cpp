#include "pch.h"
#include "TableColumnData.h"

bool TableColumnData::HasContent() const noexcept
{
	if (auto const& str = std::get_if<winrt::hstring>(&m_content))
		return !str->empty();
	else
		return static_cast<bool>(std::get<winrt::Windows::Foundation::IInspectable>(m_content));
}