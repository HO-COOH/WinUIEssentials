// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MarqueeTextPage.xaml.h"
#if __has_include("MarqueeTextPage.g.cpp")
#include "MarqueeTextPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	WinUI3Package::MarqueeBehavior MarqueeTextPage::GetBehaviorFromIndex(int value)
	{
		switch (value)
		{
		case 0: return WinUI3Package::MarqueeBehavior::Ticker;
		case 1: return WinUI3Package::MarqueeBehavior::Looping;
		case 2: return WinUI3Package::MarqueeBehavior::Bouncing;
		}
	}

	WinUI3Package::MarqueeDirection MarqueeTextPage::GetDirectionFromIndex(int value)
	{
		switch (value)
		{
		case 0: return WinUI3Package::MarqueeDirection::Left;
		case 1: return WinUI3Package::MarqueeDirection::Right;
		case 2: return WinUI3Package::MarqueeDirection::Up;
		case 3: return WinUI3Package::MarqueeDirection::Down;
		}
	}
}
