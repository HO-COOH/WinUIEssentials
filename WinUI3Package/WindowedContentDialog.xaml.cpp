#include "pch.h"
#include "WindowedContentDialog.xaml.h"
#if __has_include("WindowedContentDialog.g.cpp")
#include "WindowedContentDialog.g.cpp"
#endif
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include "ContentDialogUtils.h"
#include "ContentDialogContent.h"


namespace winrt::WinUI3Package::implementation
{
	WindowedContentDialog::WindowedContentDialog() {

		InitializeComponent();

		ExtendsContentIntoTitleBar(true);

		_presenter = Microsoft::UI::Windowing::OverlappedPresenter::CreateForDialog();

		_presenter.IsResizable(true);

		auto appWindow = AppWindow();
		appWindow.SetPresenter(_presenter);

		m_windowWorkaround = {};
		m_windowWorkaround.IsMaximizable(false);
		m_windowWorkaround.Window(*this);

		auto content = ContentDialogContent();
		auto contentImpl = winrt::get_self<struct ContentDialogContent>(content);

		contentImpl->m_closeRequestCallback =
			[this](Microsoft::UI::Xaml::Controls::ContentDialogResult result) {
				CloseByButtonAction(result);
			};

		contentImpl->m_imageSizeChangedCallback =
			[this]() {
				updateWindowSize();
			};

		m_underlaySystemBackdrop = WinUI3Package::UnderlaySystemBackdropOptions();

		m_ActualThemeChanged = content.ActualThemeChanged([&](auto&, auto&) {
			determineTitleBarButtonForegroundColor();
			});

		m_Closing = appWindow.Closing([this](auto&, auto& args) {
			args.Cancel(true);
			AppWindow().Closing(m_Closing);

			Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);
			onClosingRequestedBySystem();

			m_windowWorkaround = nullptr;
			DispatcherQueue().TryEnqueue([this] {
				Close();
				});
			});

		m_Closed = Closed([this](auto&, auto&) {

			Closed(m_Closed);

			auto content = ContentDialogContent();
			auto contentImpl = winrt::get_self<struct ContentDialogContent>(content);
			content.ActualThemeChanged(m_ActualThemeChanged);
			contentImpl->m_closeRequestCallback = nullptr;
			contentImpl->m_imageSizeChangedCallback = nullptr;

			CleanupUnderlay();

			Content(nullptr);

			Deferral.Complete();

			});

		content.Loaded({ this, &WindowedContentDialog::OnContentLoaded });

	}

	winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> WindowedContentDialog::ShowAsync()
	{

		Deferral = AsyncEventArgs->GetDeferral();

		co_await AsyncEventArgs->wait_for_deferrals();

		co_return Result();

		co_return{};

	}

	void WindowedContentDialog::updateWindowSize() 
	{
		auto content = ContentDialogContent();
		auto appWindow = AppWindow();
		auto desiredSize = content.DesiredSize();

		int baseWidth = (int)(desiredSize.Width + 1);
		int baseHeight = (int)(desiredSize.Height - 30);

		float scale = (float)content.XamlRoot().RasterizationScale();

		Windows::Graphics::SizeInt32 const windowSize
		{
			(int)(baseWidth * scale) + 1,
			(int)((baseHeight + 32) * scale) + 1
		};

		if (auto parent = m_parent.get())
		{
			auto parentAppWindow = parent.AppWindow();
			auto parentPos = parentAppWindow.Position();
			auto parentSize = parentAppWindow.Size();
			appWindow.MoveAndResize(Windows::Graphics::RectInt32
			{
				parentPos.X + (parentSize.Width - windowSize.Width) / 2,
				parentPos.Y + (parentSize.Height - windowSize.Height) / 2,
				windowSize.Width,
				windowSize.Height 
			});
		}
		else
		{
			auto displayArea = Microsoft::UI::Windowing::DisplayArea::GetFromWindowId(appWindow.Id(), Microsoft::UI::Windowing::DisplayAreaFallback::Primary);
			auto outerBounds = displayArea.OuterBounds();
			appWindow.MoveAndResize(Windows::Graphics::RectInt32
			{
				(outerBounds.Width - windowSize.Width) / 2,
				(outerBounds.Height - windowSize.Height) / 2,
				windowSize.Width,
				windowSize.Height 
			});
		}

	}

	void WindowedContentDialog::OnContentLoaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		updateWindowSize();

		auto content = ContentDialogContent();
		auto systemBackdrop = SystemBackdrop();

		SetTitleBar(content.TitleArea());

		if (systemBackdrop == nullptr)
		{
			auto requestedTheme = content.RequestedTheme();

			switch (requestedTheme)
			{
			case Microsoft::UI::Xaml::ElementTheme::Light:
				content.Background(Microsoft::UI::Xaml::Media::SolidColorBrush(Microsoft::UI::Colors::White()));
				break;
			case Microsoft::UI::Xaml::ElementTheme::Dark:
				content.Background(Microsoft::UI::Xaml::Media::SolidColorBrush(
					Windows::UI::ColorHelper::FromArgb(0xFF, 0x20, 0x20, 0x20)));
				break;
			default:
				content.Background(nullptr);
				break;
			}
		}

		if (systemBackdrop == nullptr || systemBackdrop.try_as<Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop>() != nullptr)
		{
			content.CommandSpace().Background().Opacity(1.0);
		}
		else
		{
			content.CommandSpace().Background().Opacity(0.5);
		}

		determineTitleBarButtonForegroundColor();
		open();
	}

	void WindowedContentDialog::open()
	{
		AppWindow().Show();

		if (m_Popup)
		{
			m_Popup.IsOpen(true);
			m_Popup.Child().Opacity(1.0f);

			if (auto parent = m_parent.get())
			{
				m_OnOwnerWindowSizeChanged = parent.SizeChanged({ this, &WindowedContentDialog::OnOwnerWindowSizeChanged });
			}
		}
		
		m_Opened(*this, nullptr);
	}

	void WindowedContentDialog::onClosingRequestedBySystem()
	{
		if (auto parent = m_parent.get()) {
			parent.Activate();
		}
		if (auto appWindow = AppWindow()) appWindow.Hide();
	}

	void WindowedContentDialog::onClosingRequstedByCode()
	{
		if (auto parent = m_parent.get()) {
			parent.Activate();
		}

		if (auto appWindow = AppWindow()) appWindow.Hide();
	}

	void WindowedContentDialog::determineTitleBarButtonForegroundColor()
	{
		auto titleBar = AppWindow().TitleBar();
		switch (ContentDialogContent().ActualTheme())
		{
		case Microsoft::UI::Xaml::ElementTheme::Light: {
			titleBar.ButtonForegroundColor(Microsoft::UI::Colors::Black());
			break;
		}

		case Microsoft::UI::Xaml::ElementTheme::Dark: {
			titleBar.ButtonForegroundColor(Microsoft::UI::Colors::White());
			break;
		}
		}
	}

	void WindowedContentDialog::CloseByButtonAction(Microsoft::UI::Xaml::Controls::ContentDialogResult result)
	{
		Result(result);

		AppWindow().Closing(m_Closing);

		onClosingRequstedByCode();

		m_windowWorkaround = nullptr;
		DispatcherQueue().TryEnqueue([this] {
			Close();
		});
	}

	Microsoft::UI::Xaml::Controls::ContentDialogResult WindowedContentDialog::Result() const
	{
		return _Result;
	}

	winrt::WinUI3Package::ContentDialogContent WindowedContentDialog::ContentDialogContent()
	{
		return ContentDialogContentControl();
	}

	void WindowedContentDialog::Result(const Microsoft::UI::Xaml::Controls::ContentDialogResult& value)
	{
		_Result = value;
	}

	// ShowAsync with parent
	winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> WindowedContentDialog::ShowAsync(Microsoft::UI::Xaml::Window const& parent)
	{
		SetModal(parent);
		SetupUnderlay();
		co_return co_await ShowAsync();
	}

	// Underlay management
	void WindowedContentDialog::SetupUnderlay()
	{
		auto parent = m_parent.get();
		if (!parent) return;

		switch (m_underlay)
		{
		case WinUI3Package::UnderlayMode::SmokeLayer:
			SetupSmokeLayer();
			break;
		case WinUI3Package::UnderlayMode::SystemBackdrop:
			SetupSystemBackdrop();
			break;
		}
	}

	void WindowedContentDialog::SetupSmokeLayer()
	{
		auto owner = m_parent.get();
		if (!owner) return;

		auto ownerContent = owner.Content();
		if (!ownerContent) return;

		m_Popup = Microsoft::UI::Xaml::Controls::Primitives::Popup();
		m_Popup.XamlRoot(ownerContent.XamlRoot());
		m_Popup.RequestedTheme(ContentDialogContent().RequestedTheme());

		Microsoft::UI::Xaml::Shapes::Rectangle darkLayer{};
		darkLayer.Opacity(0.0);

		auto transition = Microsoft::UI::Xaml::ScalarTransition();
		transition.Duration(std::chrono::milliseconds(250));
		darkLayer.OpacityTransition(transition);

		Microsoft::UI::Xaml::Media::SolidColorBrush brush{};
		brush.Color(ContentDialogUtils::SmokeFillColor());
		darkLayer.Fill(brush);

		SizeToXamlRoot(darkLayer, owner);

		m_Popup.Child(darkLayer);
		m_SmokeLayerCache = darkLayer;
	}

	void WindowedContentDialog::SetupSystemBackdrop()
	{
		auto owner = m_parent.get();
		if (!owner) return;

		auto ownerContent = owner.Content();
		if (!ownerContent) return;

		m_Popup = ContentDialogUtils::CreatePopup(
			ownerContent.XamlRoot(),
			m_underlaySystemBackdrop.CoverMode() == WinUI3Package::UnderlayCoverMode::Full,
			GetTitleBarOffset());

		m_BackdropLayerCache = m_Popup.Child().try_as<Microsoft::UI::Xaml::Controls::Border>();
		if (m_BackdropLayerCache)
		{
			m_BackdropLayerCache.OpacityTransition(m_underlaySystemBackdrop.OpacityTransition());
		}
	}

	void WindowedContentDialog::CleanupUnderlay()
	{
		if (m_Popup)
		{
			m_Popup.Child().Opacity(0.f);
			m_Popup.IsOpen(false);
			m_Popup.Child(nullptr);

			if (auto parent = m_parent.get())
				parent.SizeChanged(m_OnOwnerWindowSizeChanged);

			m_Popup = nullptr;
			m_SmokeLayerCache = nullptr;
			m_BackdropLayerCache = nullptr;
		}
	}

	void WindowedContentDialog::SizeToXamlRoot(Microsoft::UI::Xaml::FrameworkElement element, Microsoft::UI::Xaml::Window window)
	{
		if (!window || !window.Content() || !window.Content().XamlRoot()) return;

		element.Width(window.Content().XamlRoot().Size().Width);

		switch (m_underlay)
		{
		case WinUI3Package::UnderlayMode::SmokeLayer:
			element.Height(window.Content().XamlRoot().Size().Height);
			break;
		case WinUI3Package::UnderlayMode::SystemBackdrop:
			element.Height(
				m_underlaySystemBackdrop.CoverMode() == WinUI3Package::UnderlayCoverMode::Full
				? window.Content().XamlRoot().Size().Height
				: window.Content().XamlRoot().Size().Height - GetTitleBarOffset());
			break;
		}
	}

	int WindowedContentDialog::GetTitleBarOffset()
	{
		auto parent = m_parent.get();
		if (!parent) return 0;

		auto const heightOption = parent.AppWindow().TitleBar().PreferredHeightOption();

		switch (heightOption)
		{
		case Microsoft::UI::Windowing::TitleBarHeightOption::Standard:
			return 32;
		case Microsoft::UI::Windowing::TitleBarHeightOption::Tall:
			return 48;
		default:
			return 0;
		}
	}

	void WindowedContentDialog::OnOwnerWindowSizeChanged(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args)
	{
		auto parent = m_parent.get();
		if (!parent) return;

		if (m_SmokeLayerCache)
		{
			SizeToXamlRoot(m_SmokeLayerCache, parent);
		}
		else if (m_BackdropLayerCache)
		{
			SizeToXamlRoot(m_BackdropLayerCache, parent);
		}
	}

	WinUI3Package::UnderlayMode WindowedContentDialog::Underlay() const
	{
		return m_underlay;
	}

	void WindowedContentDialog::Underlay(WinUI3Package::UnderlayMode const& value)
	{
		m_underlay = value;
	}

	WinUI3Package::UnderlaySystemBackdropOptions WindowedContentDialog::UnderlaySystemBackdrop() const
	{
		return m_underlaySystemBackdrop;
	}

	void WindowedContentDialog::UnderlaySystemBackdrop(WinUI3Package::UnderlaySystemBackdropOptions const& value)
	{
		m_underlaySystemBackdrop = value;
	}
}
