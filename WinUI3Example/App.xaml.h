// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "App.xaml.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct App : AppT<App>
    {
        App();

        static inline App* AppInstance{};

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

		winrt::WinUI3Example::MainWindow window{ nullptr };
    };
}
