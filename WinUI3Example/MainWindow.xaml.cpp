// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <HwndHelper.hpp>
#include <wil/cppwinrt.h>
#include <LayoutUpdateAwaiter.hpp>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Windows.System.h>
#include <commctrl.h>
#pragma comment (lib, "comctl32.lib")

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	HWND MainWindow::Hwnd;

	LRESULT CALLBACK MainWindow::subclassProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR ref)
	{
		auto& self = *reinterpret_cast<MainWindow*>(ref);

		switch (msg)
		{
		case WM_WINDOWPOSCHANGING:
			/*
				Clearing this flag is the only way to refuse a show: the window stays hidden and,
				unlike ShowWindow(SW_HIDE), Windows still thinks it has never been shown. That matters
				because the open animation is played on a window's first appearance only, so refusing
				it here is what saves it for later.
			*/
			if (!self.m_allowShow)
				reinterpret_cast<WINDOWPOS*>(lp)->flags &= ~SWP_SHOWWINDOW;
			break;

		case WM_CLOSE:
			/*
				Letting WinUI have this means waiting out a teardown that throws its way through a
				long run of internal exceptions, and the window sits on screen for most of a second
				while it does. None of that work matters to a process that is about to end, so take
				the close over instead and never pass the message down.
			*/
			self.exitNow();
			return 0;
		}

		return DefSubclassProc(hwnd, msg, wp, lp);
	}

	MainWindow::MainWindow()
	{
		Hwnd = GetHwnd(Window());

		/*
			WinUI puts the window on screen before XAML has composed anything into it. The window
			surface starts out black, and since the system fades a new window in, what the user
			sees is a black window fading in and only then filling with content.

			So hold the window back here - the first point where the handle is known and Activate()
			has not run yet - and show it once XAML has actually drawn. The window then appears with
			its content already on it, and because this is still its first appearance, the system
			plays the usual open animation over the finished content.

			The same proc also takes over closing, which is slow for reasons of its own, so it stays
			in place for as long as the window does.
		*/
		SetWindowSubclass(Hwnd, subclassProc, 1, reinterpret_cast<DWORD_PTR>(this));

		m_renderingToken = winrt::Microsoft::UI::Xaml::Media::CompositionTarget::Rendering(
			[strong = get_strong()](auto&&...) { strong->onRendering(); });

		/*a window nobody can see may never be told to draw, so cap how long the wait can last*/
		m_revealTimer = DispatcherQueue().CreateTimer();
		m_revealTimer.Interval(std::chrono::milliseconds{ 100 });
		m_revealTimerToken = m_revealTimer.Tick([strong = get_strong()](auto&&...) { strong->onRevealTimerTick(); });
		m_revealTimer.Start();
	}

	void MainWindow::NavigationView_SelectionChanged(
		winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender,
		winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		if (args.IsSettingsSelected())
		{
			ContentFrame().Navigate(winrt::xaml_typename<WinUI3Example::AboutPage>());
			ComponentsList().ItemsSource(nullptr);
			return;
		}

		if (auto tag = args.SelectedItemContainer().Tag())
			ContentFrame().Navigate(winrt::unbox_value<winrt::Windows::UI::Xaml::Interop::TypeName>(tag));
	}

	void winrt::WinUI3Example::implementation::MainWindow::ExitItem_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		/*same slow teardown as the close button, so the same way out*/
		exitNow();
	}

	void MainWindow::WindowEx_Closed(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::WindowEventArgs const&)
	{
		MainIcon().Remove();
	}

	void MainWindow::WindowEx_Activated(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args)
	{
		TitleBarTextBlock().Opacity(args.WindowActivationState() == winrt::Microsoft::UI::Xaml::WindowActivationState::Deactivated ? 0.5f : 1.0f);
	}

	void MainWindow::FooterMenuItemsHost_Loaded(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		auto itemsRepeater = sender.as<winrt::Microsoft::UI::Xaml::Controls::ItemsRepeater>();
		auto items = itemsRepeater.ItemsSource().as<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>>();
		auto settingsButton = items.GetAt(1).as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
		settingsButton.Content(winrt::box_value(L"About"));
	}


	winrt::Windows::Foundation::IAsyncAction MainWindow::MoreButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		auto target = PageSourceContentButton();
		auto button = MoreButton();

		button.IsHitTestVisible(false);
		target.IsHitTestVisible(false);

		button.ReleasePointerCaptures();
		winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(button, L"Normal", false);
		winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(target, L"Normal", false);

		if (target.Visibility() == winrt::Microsoft::UI::Xaml::Visibility::Collapsed)
		{
			target.Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
			co_await LayoutUpdateAwaiter{ target };
		}

		m_sourceButtonAnimations.CreateForwardPass(button, target);
		m_sourceButtonAnimations.Play();
	}

	void MainWindow::PageSourceContentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	winrt::Windows::Foundation::Uri MainWindow::GetXamlUrl(winrt::hstring const& name)
	{
		return winrt::Windows::Foundation::Uri{ std::format(L"https://github.com/HO-COOH/WinUIEssentials/blob/master/WinUI3Package/{}.xaml", name) };
	}


	void MainWindow::onRendering()
	{
		/*
			Rendering fires before the frame it announces is composed, so a tick only means XAML is
			about to draw. The first few frames of a cold start still go out half empty, so let a
			handful through before showing the window.
		*/
		if (++m_renderedFrames < 2)
			return;

		showWindow();
	}

	void MainWindow::onRevealTimerTick()
	{
		/*
			A second in, show the window whether or not frames are coming. This is only a backstop
			against never being told about a frame, so it stays well behind the normal path, which
			gets there in about half a second.
		*/
		if (++m_ticks < 10)
			return;

		showWindow();
	}

	void MainWindow::showWindow()
	{
		if (std::exchange(m_shown, true))
			return;

		if (auto const token = std::exchange(m_renderingToken, {}))
			winrt::Microsoft::UI::Xaml::Media::CompositionTarget::Rendering(token);

		if (auto const timer = std::exchange(m_revealTimer, nullptr))
		{
			timer.Stop();
			timer.Tick(std::exchange(m_revealTimerToken, {}));
		}

		m_allowShow = true;
		ShowWindow(Hwnd, SW_SHOW);

		/*Activate() asked for the foreground while the window was still hidden, so ask again*/
		SetForegroundWindow(Hwnd);
	}

	void MainWindow::exitNow()
	{
		/*the window goes away first, so the click is answered before anything slower is attempted*/
		ShowWindow(Hwnd, SW_HIDE);

		/*
			The shell holds on to a tray icon until it is told to drop it, or until it next happens to
			notice the owning process is gone, so this is the one piece of shutdown that still has to
			run. A window proc must not throw, and an icon that will not come off is no reason to stay
			open, so failure here is nothing to act on.
		*/
		try
		{
			MainIcon().Remove();
		}
		catch (...)
		{
		}

		/*
			TerminateProcess, rather than Application::Exit() or ExitProcess: those run the teardown
			this exists to skip - Exit() the XAML side of it, ExitProcess the DLL detach handlers that
			follow. Nothing in this app is waiting to be written, so there is nothing to run out.
		*/
		TerminateProcess(GetCurrentProcess(), 0);
	}

	void MainWindow::RootGrid_Loaded(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		auto const timeDiffMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - AppStartTime);
		TitleBarTextBlock().Text(winrt::hstring{ std::format(L"{}   StartTime: {}", WindowTitle(), timeDiffMilliseconds) });
	}

	void MainWindow::GithubFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::Windows::System::Launcher::LaunchUriAsync(winrt::Windows::Foundation::Uri{ L"https://github.com/HO-COOH/WinUIEssentials" });
	}

	void MainWindow::StoreFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::Windows::System::Launcher::LaunchUriAsync(winrt::Windows::Foundation::Uri{ L"ms-windows-store://pdp/?productid=9PCC690BCMT9" });
	}

	void MainWindow::AutoSuggestBox_QuerySubmitted(
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const&,
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs const& args)
	{
		m_navigationHelper.OnAutoSuggestBoxQuerySubmitted(args, NavView());
	}

	void MainWindow::AutoSuggestBox_TextChanged(
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender,
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
	{
		if (args.Reason() != winrt::Microsoft::UI::Xaml::Controls::AutoSuggestionBoxTextChangeReason::UserInput)
			return;

		m_navigationHelper.OnAutoSuggestBoxTextChanged(sender);
	}

}
