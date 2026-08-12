// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "CursorControllerPage.xaml.h"
#if __has_include("CursorControllerPage.g.cpp")
#include "CursorControllerPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<CursorControllerPage> s_tags{ L"cursorcontroller", L"cursor", L"mouse", L"extension" };
}
