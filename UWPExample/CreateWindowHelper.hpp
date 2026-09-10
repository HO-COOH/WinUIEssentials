#pragma once
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.UI.Core.h>

template<typename Page>
void CreateWindowWithPage()
{
	auto newView = winrt::Windows::ApplicationModel::Core::CoreApplication::CreateNewView();
	newView.Dispatcher().RunAsync({}, [] {
		auto window = winrt::Windows::UI::Xaml::Window::Current();
		window.Content(Page{});
		window.Activate();

		winrt::Windows::UI::ViewManagement::ApplicationViewSwitcher::TryShowAsStandaloneAsync(
			winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Id()
		);
	});
}

template<typename F>
void CreateWindowWithFactory(F&& factory)
{
	auto newView = winrt::Windows::ApplicationModel::Core::CoreApplication::CreateNewView();
	newView.Dispatcher().RunAsync({}, [factory = std::move(factory)] {
		auto window = winrt::Windows::UI::Xaml::Window::Current();
		window.Content(factory());
		window.Activate();

		winrt::Windows::UI::ViewManagement::ApplicationViewSwitcher::TryShowAsStandaloneAsync(
			winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().Id()
		);
	});
}