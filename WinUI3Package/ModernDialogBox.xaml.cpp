#include "pch.h"
#include "ModernDialogBox.xaml.h"
#if __has_include("ModernDialogBox.g.cpp")
#include "ModernDialogBox.g.cpp"
#endif
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include "ContentDialogUtils.h"
#include "ModernDialogBoxContent.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Package::implementation
{
	ModernDialogBox::ModernDialogBox() {

		InitializeComponent();

		ExtendsContentIntoTitleBar(true);

		_presenter = Microsoft::UI::Windowing::OverlappedPresenter::CreateForDialog();

		_presenter.IsResizable(true);

		auto appWindow = AppWindow();
		appWindow.SetPresenter(_presenter);

		m_windowWorkaround = {};
		m_windowWorkaround.IsMaximizable(false);
		m_windowWorkaround.Window(*this);

		auto content = DialogContent();
		m_contentImpl = winrt::get_self<ModernDialogBoxContent>(content);

		m_contentImpl->m_closeRequestCallback =
			[this](Microsoft::UI::Xaml::Controls::ContentDialogResult result) {
			closeByButtonAction(result);
			};

		m_contentImpl->m_imageSizeChangedCallback =
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

			auto content = DialogContent();
			content.ActualThemeChanged(m_ActualThemeChanged);
			m_contentImpl->m_closeRequestCallback = nullptr;
			m_contentImpl->m_imageSizeChangedCallback = nullptr;

			cleanupUnderlay();

			Content(nullptr);

			Deferral.Complete();

			});

		content.Loaded({ this, &ModernDialogBox::OnContentLoaded });

	}

	winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ModernDialogBox::ShowAsync()
	{

		Deferral = AsyncEventArgs->GetDeferral();

		co_await AsyncEventArgs->wait_for_deferrals();

		co_return Result();

		co_return{};

	}

	void ModernDialogBox::updateWindowSize()
	{
		auto content = DialogContent();
		auto appWindow = AppWindow();

		constexpr float maxDimension = 100000.0f;
		content.Measure({ maxDimension, maxDimension });
		auto desiredSize = content.DesiredSize();

		float scale = (float)content.XamlRoot().RasterizationScale();

		int clientWidth = static_cast<int>(std::ceil(desiredSize.Width * scale));
		int clientHeight = static_cast<int>(std::ceil(desiredSize.Height * scale));

		Windows::Graphics::SizeInt32 const windowSize{ clientWidth, clientHeight };

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

	void ModernDialogBox::OnContentLoaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		updateWindowSize();

		auto content = DialogContent();
		auto systemBackdrop = SystemBackdrop();

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

		m_contentImpl->m_CommandSpace.Background().Opacity(systemBackdrop ? 0.5 : 1.0);

		determineTitleBarButtonForegroundColor();
		open();
	}

	void ModernDialogBox::open()
	{
		AppWindow().Show();

		if (m_Popup)
		{
			m_Popup.IsOpen(true);
			m_Popup.Child().Opacity(1.0f);

			if (auto parent = m_parent.get())
			{
				m_onOwnerWindowSizeChanged = parent.SizeChanged(winrt::auto_revoke, { this, &ModernDialogBox::onOwnerWindowSizeChanged });
			}
		}
	}

	void ModernDialogBox::onClosingRequestedBySystem()
	{
		if (auto parent = m_parent.get()) {
			parent.Activate();
		}
		if (auto appWindow = AppWindow()) appWindow.Hide();
	}

	void ModernDialogBox::onClosingRequstedByCode()
	{
		if (auto parent = m_parent.get()) {
			parent.Activate();
		}

		if (auto appWindow = AppWindow()) appWindow.Hide();
	}

	void ModernDialogBox::determineTitleBarButtonForegroundColor()
	{
		auto titleBar = AppWindow().TitleBar();
		switch (DialogContent().ActualTheme())
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

	void ModernDialogBox::closeByButtonAction(Microsoft::UI::Xaml::Controls::ContentDialogResult result)
	{
		Result(result);

		AppWindow().Closing(m_Closing);

		onClosingRequstedByCode();

		m_windowWorkaround = nullptr;
		DispatcherQueue().TryEnqueue([this] {
			Close();
			});
	}

	Microsoft::UI::Xaml::Controls::ContentDialogResult ModernDialogBox::Result() const
	{
		return _Result;
	}

	winrt::WinUI3Package::ModernDialogBoxContent ModernDialogBox::DialogContent()
	{
		return ContentDialogContentControl();
	}

	void ModernDialogBox::Result(const Microsoft::UI::Xaml::Controls::ContentDialogResult& value)
	{
		_Result = value;
	}

	// ShowAsync with parent
	winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ModernDialogBox::ShowAsync(Microsoft::UI::Xaml::Window const& parent)
	{
		SetModal(parent);
		setupUnderlay();
		co_return co_await ShowAsync();
	}

	// Underlay management
	void ModernDialogBox::setupUnderlay()
	{
		auto parent = m_parent.get();
		if (!parent) return;

		switch (m_underlay)
		{
		case WinUI3Package::UnderlayMode::SmokeLayer:
			setupSmokeLayer();
			break;
		case WinUI3Package::UnderlayMode::SystemBackdrop:
			setupSystemBackdrop();
			break;
		}
	}

	void ModernDialogBox::setupSmokeLayer()
	{
		auto owner = m_parent.get();
		if (!owner) return;

		auto ownerContent = owner.Content();
		if (!ownerContent) return;

		m_Popup = Microsoft::UI::Xaml::Controls::Primitives::Popup();
		m_Popup.XamlRoot(ownerContent.XamlRoot());
		m_Popup.RequestedTheme(DialogContent().RequestedTheme());

		Microsoft::UI::Xaml::Shapes::Rectangle darkLayer{};
		darkLayer.Opacity(0.0);

		auto transition = Microsoft::UI::Xaml::ScalarTransition();
		transition.Duration(std::chrono::milliseconds(250));
		darkLayer.OpacityTransition(transition);

		Microsoft::UI::Xaml::Media::SolidColorBrush brush{};
		brush.Color(ContentDialogUtils::SmokeFillColor());
		darkLayer.Fill(brush);

		sizeToXamlRoot(darkLayer, owner);

		m_Popup.Child(darkLayer);
		m_SmokeLayerCache = darkLayer;
	}

	void ModernDialogBox::setupSystemBackdrop()
	{
		auto owner = m_parent.get();
		if (!owner) return;

		auto ownerContent = owner.Content();
		if (!ownerContent) return;

		m_Popup = ContentDialogUtils::CreatePopup(
			ownerContent.XamlRoot(),
			m_underlaySystemBackdrop.CoverMode() == WinUI3Package::UnderlayCoverMode::Full,
			getTitleBarOffset());

		m_BackdropLayerCache = m_Popup.Child().try_as<Microsoft::UI::Xaml::Controls::Border>();
		if (m_BackdropLayerCache)
		{
			m_BackdropLayerCache.OpacityTransition(m_underlaySystemBackdrop.OpacityTransition());
		}
	}

	void ModernDialogBox::cleanupUnderlay()
	{
		if (m_Popup)
		{
			m_Popup.Child().Opacity(0.f);
			m_Popup.IsOpen(false);
			m_Popup.Child(nullptr);
			m_Popup = nullptr;
			m_SmokeLayerCache = nullptr;
			m_BackdropLayerCache = nullptr;
		}
	}

	void ModernDialogBox::sizeToXamlRoot(Microsoft::UI::Xaml::FrameworkElement element, Microsoft::UI::Xaml::Window window)
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
				: window.Content().XamlRoot().Size().Height - getTitleBarOffset());
			break;
		}
	}

	int ModernDialogBox::getTitleBarOffset()
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

	void ModernDialogBox::onOwnerWindowSizeChanged(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args)
	{
		auto parent = m_parent.get();
		if (!parent) return;

		if (m_SmokeLayerCache)
		{
			sizeToXamlRoot(m_SmokeLayerCache, parent);
		}
		else if (m_BackdropLayerCache)
		{
			sizeToXamlRoot(m_BackdropLayerCache, parent);
		}
	}

	WinUI3Package::UnderlayMode ModernDialogBox::Underlay() const
	{
		return m_underlay;
	}

	void ModernDialogBox::Underlay(WinUI3Package::UnderlayMode const& value)
	{
		m_underlay = value;
	}

	WinUI3Package::UnderlaySystemBackdropOptions ModernDialogBox::UnderlaySystemBackdrop() const
	{
		return m_underlaySystemBackdrop;
	}

	void ModernDialogBox::UnderlaySystemBackdrop(WinUI3Package::UnderlaySystemBackdropOptions const& value)
	{
		m_underlaySystemBackdrop = value;
	}
}
