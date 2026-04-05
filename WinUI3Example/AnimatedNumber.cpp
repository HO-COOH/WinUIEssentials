#include "pch.h"
#include "AnimatedNumber.h"
#if __has_include("AnimatedNumber.g.cpp")
#include "AnimatedNumber.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void AnimatedNumber::Value(int32_t value)
	{
		m_value = value;
		if (m_rootPanel == 0)
			return;

		boost::container::small_vector<int, 10> result;
		if (value == 0)
			result.push_back(0);
		else
			getDigit(value, result);

		auto const digitCount = result.size();
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
			if (result[i] != digit.Value())
				digit.Value(result[i]);
		}
	}

	void AnimatedNumber::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		m_rootPanel = GetTemplateChild(L"RootPanel").as<winrt::Microsoft::UI::Xaml::Controls::Panel>();
		if (m_value)
			Value(*m_value);
	}
}
