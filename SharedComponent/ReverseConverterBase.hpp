#pragma once
class ReverseConverterBase
{
public:
	bool Reverse()
	{
		return m_reverse;
	}
	void Reverse(bool value)
	{
		m_reverse = value;
	}
private:
	bool m_reverse{};
};