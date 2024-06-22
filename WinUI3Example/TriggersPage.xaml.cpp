// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "TriggersPage.xaml.h"
#if __has_include("TriggersPage.g.cpp")
#include "TriggersPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    TriggersPage::TriggersPage()
    {
        InitializeComponent();
    }

	void TriggersPage::AddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		if (OurList())
		{
			OurList().Items().Append(winrt::box_value(L"Item"));
		}
	}


	void TriggersPage::RemoveButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		if (OurList())
		{
			OurList().Items().RemoveAt(0);
		}
	}
}
