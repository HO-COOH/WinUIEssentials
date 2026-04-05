#include "pch.h"
#include "AnimatedDigit.h"
#if __has_include("AnimatedDigit.g.cpp")
#include "AnimatedDigit.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void AnimatedDigit::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		m_currentDigit = GetTemplateChild(L"CurrentDigit").as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
		m_nextDigit = GetTemplateChild(L"NextDigit").as<winrt::Microsoft::UI::Xaml::FrameworkElement>();

		m_increaseCurrentAnim = GetTemplateChild(L"IncreaseCurrentDigitTranslateAnimation").try_as<winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation>();
		m_increaseNextAnim = GetTemplateChild(L"IncreaseNextDigitTranslateAnimation").try_as<winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation>();
		m_decreaseCurrentAnim = GetTemplateChild(L"DecreaseCurrentDigitTranslateAnimation").try_as<winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation>();
		m_decreaseNextAnim = GetTemplateChild(L"DecreaseNextDigitTranslateAnimation").try_as<winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation>();
	}

	void AnimatedDigit::Value(int value)
	{
		if (m_isFirst)
		{
			currentValue(value);
			m_isFirst = false;
		}
		else
		{
			double fontSize = FontSize();
			if (value > m_value)
			{
				if (m_increaseCurrentAnim)
				{
					m_increaseCurrentAnim.From(0.0);
					m_increaseCurrentAnim.To(-fontSize - 10);
				}
				if (m_increaseNextAnim)
				{
					m_increaseNextAnim.From(fontSize);
					m_increaseNextAnim.To(0.0);
				}

				currentValue(m_value);
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"Normal", true);
				nextValue(value);
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"IncreaseState", true);
			}
			else
			{
				if (m_decreaseCurrentAnim)
				{
					m_decreaseCurrentAnim.From(-fontSize - 10);
					m_decreaseCurrentAnim.To(0.0);
				}
				if (m_decreaseNextAnim)
				{
					m_decreaseNextAnim.From(0.0);
					m_decreaseNextAnim.To(fontSize);
				}

				nextValue(m_value);
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"Normal", true);
				currentValue(value);
				winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(*this, L"DecreaseState", true);
			}
		}
		m_value = value;
	}

	int AnimatedDigit::Value()
	{
		return m_value;
	}

	winrt::hstring AnimatedDigit::CurrentValue()
	{
		return m_currentValue == -1 ? L"" : winrt::to_hstring(m_currentValue);
	}

	winrt::hstring AnimatedDigit::NextValue()
	{
		return m_nextValue == -1 ? L"" : winrt::to_hstring(m_nextValue);
	}

	void AnimatedDigit::currentValue(int value)
	{
		if (m_currentValue == value)
			return;

		m_currentValue = value;
		raisePropertyChange(L"CurrentValue");
	}

	void AnimatedDigit::nextValue(int value)
	{
		if (m_nextValue == value)
			return;

		m_nextValue = value;
		raisePropertyChange(L"NextValue");
	}
}
