#include "pch.h"
#include "MarqueeContainerPage.h"
#if __has_include("MarqueeContainerPage.g.cpp")
#include "MarqueeContainerPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	UWPPackage::MarqueeBehavior MarqueeContainerPage::GetBehaviorFromIndex(int value)
	{
		switch (value)
		{
		case 0: return UWPPackage::MarqueeBehavior::Ticker;
		case 1: return UWPPackage::MarqueeBehavior::Looping;
		case 2: return UWPPackage::MarqueeBehavior::Bouncing;
		}
	}

	UWPPackage::MarqueeDirection MarqueeContainerPage::GetDirectionFromIndex(int value)
	{
		switch (value)
		{
		case 0: return UWPPackage::MarqueeDirection::Left;
		case 1: return UWPPackage::MarqueeDirection::Right;
		case 2: return UWPPackage::MarqueeDirection::Up;
		case 3: return UWPPackage::MarqueeDirection::Down;
		}
	}

}
