// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "DependentValuePage.xaml.h"
#if __has_include("DependentValuePage.g.cpp")
#include "DependentValuePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    void DependentValuePage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        DoubleValueAnimation().Begin();
    }
}
