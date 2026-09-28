#pragma once
class ReverseConverterBase
{
public:
	constexpr bool Reverse() noexcept
	{
		return m_reverse;
	}
	constexpr void Reverse(bool value) noexcept
	{
		m_reverse = value;
	}
private:
	bool m_reverse{};
};