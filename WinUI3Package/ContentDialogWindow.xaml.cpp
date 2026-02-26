#include "pch.h"
#include "ContentDialogWindow.xaml.h"
#if __has_include("ContentDialogWindow.g.cpp")
#include "ContentDialogWindow.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Input.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <Microsoft.UI.Xaml.Window.h>

namespace winrt::WinUI3Package::implementation
{
	ContentDialogWindow::ContentDialogWindow() {

		InitializeComponent();

		ExtendsContentIntoTitleBar(true);

		_presenter = Microsoft::UI::Windowing::OverlappedPresenter::CreateForDialog();

		_presenter.IsResizable(true);
		//_presenter.IsAlwaysOnTop(true);
		//_presenter.SetBorderAndTitleBar(true, false);

		auto appWindow = AppWindow();
		appWindow.SetPresenter(_presenter);

		m_windowWorkaround = {};
		m_windowWorkaround.IsMaximizable(false);
		m_windowWorkaround.Window(*this);

		//HWND hwnd = (HWND)WindowHelper::GetWindowHandle(*this);

		//SetWindowLongPtr(hwnd, GWL_STYLE, GetWindowLongPtr(hwnd, GWL_STYLE) & ~WS_DLGFRAME);

		//Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);

		//auto hWnd = (HWND)WinUI3Package::WindowHelper::GetWindowHandle(*this);

		//auto controlsHwnd = FindWindowEx(hWnd, 0, L"ReunionWindowingCaptionControls", L"ReunionCaptionControlsWindow");

		//if (controlsHwnd != nullptr) DestroyWindow(controlsHwnd);


		auto content = ContentDialogContent();

		content.ContentRightTapped({ this, &ContentDialogWindow::OnContentRightTapped });

		m_ActualThemeChanged = content.ActualThemeChanged([&](auto&, auto&) {
			DetermineTitleBarButtonForegroundColor();
		});

		//Microsoft::UI::Xaml::Media::ImageSource ImageSource = {};

		//Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage = {};
		//bitmapImage.UriSource(Windows::Foundation::Uri(L"https://shared.fastly.steamstatic.com/store_item_assets/steam/apps/1364780/header.jpg"));

		//WindowImage().Source(bitmapImage);


		m_Closing = appWindow.Closing([this](auto&, auto& args) {
			args.Cancel(true);
			AppWindow().Closing(m_Closing);

			Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);
			OnClosingRequestedBySystem();

			m_windowWorkaround = nullptr;
			DispatcherQueue().TryEnqueue([this] {
				Close();
			});
		});

		m_Closed = Closed([this](auto&, auto&) {

			Closed(m_Closed);

			WindowImage().ImageOpened(m_ImageOpened);
			ContentDialogContent().ActualThemeChanged(m_ActualThemeChanged);

			Content(nullptr);

			Deferral.Complete();

		});


		content.Loaded({ this, &ContentDialogWindow::OnContentLoaded });;

		m_ImageOpened = WindowImage().ImageOpened([this](IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
		{
			auto image = sender.as<Microsoft::UI::Xaml::Controls::Image>();

			if (image)
			{
				// 获取图片源并转换为BitmapImage
				auto bitmapImage = image.Source().as<Microsoft::UI::Xaml::Media::Imaging::BitmapImage>();
				if (bitmapImage)
				{
					// 获取图片实际宽高（像素）
					double width = bitmapImage.PixelWidth();
					double height = bitmapImage.PixelHeight();


					if (auto parentGrid = image.Parent().as<Microsoft::UI::Xaml::Controls::Grid>())
					{
						parentGrid.Width(width);
						parentGrid.Height(height);
					}

					UpdateWindowSize();
				}
			}
		});

	}

	winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> ContentDialogWindow::ShowAsync()
	{

		Deferral = AsyncEventArgs->GetDeferral();

		//Open();

		co_await AsyncEventArgs->wait_for_deferrals();

		co_return Result();

		co_return{};

	}

	void ContentDialogWindow::UpdateWindowSize() {

		auto imageGrid = ImageGrid();
		auto content = ContentDialogContent();
		auto appWindow = AppWindow();
		auto desiredSize = content.DesiredSize();

		int baseWidth = imageGrid.Width() ?
			(int)imageGrid.Width() :
			(int)(desiredSize.Width + 1);

		int baseHeight =
			(int)(desiredSize.Height - 30) +
			(int)imageGrid.Height();

		float scale = (float)content.XamlRoot().RasterizationScale();

		appWindow.ResizeClient(Windows::Graphics::SizeInt32(
			(int)(baseWidth * scale) + 1,
			(int)(baseHeight * scale) + 1
		));

		if (_center)
		{
			auto selfSize = appWindow.Size();
			if (auto parent = m_parent.get())
			{
				auto parentAppWindow = parent.AppWindow();
				auto parentPos = parentAppWindow.Position();
				auto parentSize = parentAppWindow.Size();
				appWindow.Move(Windows::Graphics::PointInt32(
					parentPos.X + (parentSize.Width - selfSize.Width) / 2,
					parentPos.Y + (parentSize.Height - selfSize.Height) / 2));
			}
			else
			{
				auto displayArea = Microsoft::UI::Windowing::DisplayArea::GetFromWindowId(appWindow.Id(), Microsoft::UI::Windowing::DisplayAreaFallback::Primary);
				auto outerBounds = displayArea.OuterBounds();
				appWindow.Move(Windows::Graphics::PointInt32(
					(outerBounds.Width - selfSize.Width) / 2,
					(outerBounds.Height - selfSize.Height) / 2));
			}
		}

	}

	void ContentDialogWindow::OnContentLoaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		//SetForegroundWindow((HWND)WinUI3Package::WindowHelper::GetWindowHandle(*this));

		UpdateWindowSize();

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


		DetermineTitleBarButtonForegroundColor();

		//std::list<Microsoft::UI::Xaml::FrameworkElement> ElementsList = {};

		//ElementsList.push_back(_content.TitleArea().as<Microsoft::UI::Xaml::FrameworkElement>());

		//UpdateDragRegion(ElementsList);

		DispatcherQueue().TryEnqueue([this]()
		{
			// 触发 Loaded 事件（如果有订阅者）
			m_Loaded(*this, nullptr);
		});

		Open();

	}

	void ContentDialogWindow::Open()
	{
		AppWindow().Show();

		DispatcherQueue().TryEnqueue([this]()
		{
			// 触发 Loaded 事件（如果有订阅者）
			m_Opened(*this, nullptr);
		});
	}

	void ContentDialogWindow::Hide()
	{
		AppWindow().Hide();
	}

	void ContentDialogWindow::OnClosingRequestedBySystem()
	{
		if (auto parent = m_parent.get()) {
			parent.Activate();
			//_parent.Closed(m_OnParentClosed);
		}
		if (auto appWindow = AppWindow()) appWindow.Hide();

		//Close();
	}

	void ContentDialogWindow::OnClosingRequstedByCode()
	{
		if (auto parent = m_parent.get()) {
			parent.Activate();
			//_parent.Closed(m_OnParentClosed);
		}

		if (auto appWindow = AppWindow()) appWindow.Hide();

		//Close();
	}


	winrt::Windows::Foundation::IAsyncAction ContentDialogWindow::OnPrimaryButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& args)
	{
		if (args.Handled()) co_return;

		args.Handled(true);

		auto ButtonDeferral = args.GetDeferral();

		Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary);

		auto Args = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

		co_await Args.wait_for_deferrals();

		AfterCommandSpaceButtonClick(Args);

		ButtonDeferral.Complete();

	}

	winrt::Windows::Foundation::IAsyncAction ContentDialogWindow::OnSecondaryButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& args)
	{

		if (args.Handled()) co_return;

		args.Handled(true);

		auto ButtonDeferral = args.GetDeferral();

		Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::Secondary);

		auto Args = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

		co_await Args.wait_for_deferrals();

		AfterCommandSpaceButtonClick(Args);

		ButtonDeferral.Complete();
	}

	winrt::Windows::Foundation::IAsyncAction ContentDialogWindow::OnCloseButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& args)
	{


		if (args.Handled()) co_return;

		args.Handled(true);

		auto ButtonDeferral = args.GetDeferral();

		Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);

		auto Args = WinUI3Package::ContentDialogWindowButtonClickEventArgs();


		co_await Args.wait_for_deferrals();

		AfterCommandSpaceButtonClick(Args);

		ButtonDeferral.Complete();

	}

	void ContentDialogWindow::DetermineTitleBarButtonForegroundColor()
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

	void ContentDialogWindow::AfterCommandSpaceButtonClick(WinUI3Package::ContentDialogWindowButtonClickEventArgs const& args)
	{

		if (args.Cancel()) {


			//Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);
			return;

		}

		AppWindow().Closing(m_Closing);

		OnClosingRequstedByCode();

		m_windowWorkaround = nullptr;
		DispatcherQueue().TryEnqueue([this] {

			Close();
		});

	}

	void ContentDialogWindow::SetParent(Microsoft::UI::Xaml::Window const& parent, bool center /*= true*/)
	{
		_center = center;

		if (m_parent.get() == parent) return;

		SetModal(parent);
	}

	void ContentDialogWindow::HasTitleBar(bool value) {
		m_hasTitleBar = value;
		if (_presenter) _presenter.SetBorderAndTitleBar(true, value);
	}
	bool ContentDialogWindow::HasTitleBar() {
		return m_hasTitleBar;
	}

	void ContentDialogWindow::IsResizable(bool value) {
		m_isResizable = value;
		if (_presenter) _presenter.IsResizable(value);
	}
	bool ContentDialogWindow::IsResizable() {

		return m_isResizable;
	}


	winrt::event_token ContentDialogWindow::Loaded(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, Windows::Foundation::IInspectable> const& handler)
	{
		return m_Loaded.add(handler);
	}
	void ContentDialogWindow::Loaded(winrt::event_token const& token)
	{
		m_Loaded.remove(token);
	}

	winrt::event_token ContentDialogWindow::Opened(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, Windows::Foundation::IInspectable> const& handler)
	{
		return m_Opened.add(handler);
	}
	void ContentDialogWindow::Opened(winrt::event_token const& token)
	{
		m_Opened.remove(token);
	}


	winrt::event_token ContentDialogWindow::ContentRightTapped(Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs> const& handler)
	{
		return m_ContentRightTapped.add(handler);
	}

	void ContentDialogWindow::ContentRightTapped(winrt::event_token const& token)
	{
		m_ContentRightTapped.remove(token);
	}

	winrt::hstring ContentDialogWindow::HeaderImageUri()
	{
		return m_HeaderImageUri;
	}

	void ContentDialogWindow::HeaderImageUri(winrt::hstring const& Value)
	{
		if (m_HeaderImageUri != Value) {

			m_HeaderImageUri = Value;

			if (!Value.empty()) {

				Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage = {};
				bitmapImage.UriSource(Windows::Foundation::Uri(m_HeaderImageUri));
				WindowImage().Source(bitmapImage);
				ContentDialogContent().IsHeaderImage(true);
				ImageGrid().Visibility(Microsoft::UI::Xaml::Visibility::Visible);
			}
		}
	}

	winrt::Microsoft::UI::Xaml::Media::Imaging::BitmapImage ContentDialogWindow::HeaderImage()
	{
		return m_HeaderImage;
	}

	void ContentDialogWindow::HeaderImage(Microsoft::UI::Xaml::Media::Imaging::BitmapImage const& Value)
	{
		if (Value && m_HeaderImage != Value) {

			m_HeaderImage = Value;

			//Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage = {};
			//bitmapImage.UriSource(Windows::Foundation::Uri(L"https://shared.fastly.steamstatic.com/store_item_assets/steam/apps/1364780/header.jpg"));
			WindowImage().Source(Value);

			ContentDialogContent().IsHeaderImage(true);
		}
	}

	Microsoft::UI::Xaml::Controls::ContentDialogResult ContentDialogWindow::Result() const
	{
		return _Result;
	}

	winrt::WinUI3Package::ContentDialogContent ContentDialogWindow::ContentDialogContent()
	{
		return ContentDialogContentControl();
	}

	void ContentDialogWindow::Result(const Microsoft::UI::Xaml::Controls::ContentDialogResult& value)
	{
		_Result = value;
	}

	void ContentDialogWindow::OnContentRightTapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs const& e)
	{
		m_ContentRightTapped(*this, e);
	}

}
