#include "pch.h"
#include "AnimatedNumber.h"
#if __has_include("AnimatedNumber.g.cpp")
#include "AnimatedNumber.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	winrt::Windows::Foundation::Collections::IObservableVector<int> AnimatedNumber::Digits()
	{
		return m_digits;
	}

	void AnimatedNumber::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
	}


}
