#pragma once
#include "App.xaml.g.h"
#include <ToastBuilder.hpp>

namespace winrt::UWPExample::implementation
{

    struct App : AppT<App>, ToastBuilder::ToastNotificationHandler
    {
        App();
        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
        void OnSuspending(IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);
        void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);

        using ToastBuilder::ToastNotificationHandler::OnActivated;
    };
}
