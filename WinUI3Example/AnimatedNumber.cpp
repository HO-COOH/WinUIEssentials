#include "pch.h"
#include "AnimatedNumber.h"
#if __has_include("AnimatedNumber.g.cpp")
#include "AnimatedNumber.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	winrt::hstring AnimatedNumber::Value()
	{
		return m_value;
	}

	void AnimatedNumber::Value(winrt::hstring const& value)
	{
		m_value = value;
		if (m_rootPanel == 0)
			return;

		auto const digitCount = value.size();

		auto splitted = m_rootPanel.Children();
		auto childCount = splitted.Size();
		while (digitCount > childCount)
		{
			splitted.InsertAt(0, AnimatedDigit{});
			++childCount;
		}

		while (digitCount < childCount)
		{
			splitted.RemoveAt(0);
			--childCount;
		}

		for (auto i = 0; i < digitCount; ++i)
		{
			auto digit = splitted.GetAt(i).as<AnimatedDigit>();
			if (value[i] != digit.Value())
				digit.Value(value[i]);
		}
	}

	void AnimatedNumber::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		m_rootPanel = GetTemplateChild(L"RootPanel").as<winrt::Microsoft::UI::Xaml::Controls::Panel>();
		if (!m_value.empty())
			Value(m_value);
	}
}
