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

#include <windows.h>
#include <commctrl.h>

#include "ContentDialogWindowButtonClickEventArgs.h"

namespace winrt::WinUI3Package::implementation
{
	LRESULT CALLBACK TitleBarSubclassProc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam,
		UINT_PTR uIdSubclass,
		DWORD_PTR dwRefData
	)
	{
		// 拦截非客户区双击消息
		if (uMsg == WM_NCLBUTTONDBLCLK)
		{
			// 只在标题栏区域拦截双击
			if (wParam == HTCAPTION)
			{
				// 返回 0 表示已处理，阻止默认行为
				return 0;
			}
		}
		else if ((uMsg == WM_NCRBUTTONDOWN || uMsg == WM_NCRBUTTONUP) && wParam == HTCAPTION)
		{
			// 返回 0 表示已处理，阻止系统菜单弹出
			return 0;
		}
		// 其他消息传递给默认窗口过程
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	ContentDialogWindow::ContentDialogWindow() {

		InitializeComponent();

		ExtendsContentIntoTitleBar(true);

		_presenter = Microsoft::UI::Windowing::OverlappedPresenter::CreateForDialog();

		_presenter.IsResizable(true);
		//_presenter.IsAlwaysOnTop(true);
		//_presenter.SetBorderAndTitleBar(true, false);

		AppWindow().SetPresenter(_presenter);

		m_windowWorkaround = {};
		m_windowWorkaround.IsMaximizable(false);
		m_windowWorkaround.Window(*this);

		//HWND hwnd = (HWND)WindowHelper::GetWindowHandle(*this);

		//SetWindowLongPtr(hwnd, GWL_STYLE, GetWindowLongPtr(hwnd, GWL_STYLE) & ~WS_DLGFRAME);

		//Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);

		//auto hWnd = (HWND)WinUI3Package::WindowHelper::GetWindowHandle(*this);

		//auto controlsHwnd = FindWindowEx(hWnd, 0, L"ReunionWindowingCaptionControls", L"ReunionCaptionControlsWindow");

		//if (controlsHwnd != nullptr) DestroyWindow(controlsHwnd);

		//m_Activated = Activated({ this, &ContentDialogWindow::OnActivated });;


		m_OnPrimaryButtonClick = ContentDialogContent().PrimaryButtonClick({ this, &ContentDialogWindow::OnPrimaryButtonClick });
		m_OnSecondaryButtonClick = ContentDialogContent().SecondaryButtonClick({ this, &ContentDialogWindow::OnSecondaryButtonClick });
		m_OnCloseButtonClick = ContentDialogContent().CloseButtonClick({ this, &ContentDialogWindow::OnCloseButtonClick });

		ContentDialogContent().ContentRightTapped({ this, &ContentDialogWindow::OnContentRightTapped });

		m_ActualThemeChanged = ContentDialogContent().ActualThemeChanged([&](auto&, auto&) {
			DetermineTitleBarButtonForegroundColor();
		});

		//Microsoft::UI::Xaml::Media::ImageSource ImageSource = {};

		//Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage = {};
		//bitmapImage.UriSource(Windows::Foundation::Uri(L"https://shared.fastly.steamstatic.com/store_item_assets/steam/apps/1364780/header.jpg"));

		//WindowImage().Source(bitmapImage);


		m_Closing = AppWindow().Closing([this](auto&, auto& args) {
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

			ContentDialogContent().PrimaryButtonClick(m_OnPrimaryButtonClick);
			ContentDialogContent().SecondaryButtonClick(m_OnSecondaryButtonClick);
			ContentDialogContent().CloseButtonClick(m_OnCloseButtonClick);
			ContentDialogContent().ActualThemeChanged(m_ActualThemeChanged);

			Content(nullptr);

			Deferral.Complete();

		});


		ContentDialogContent().Loaded({ this, &ContentDialogWindow::OnContentLoaded });;

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

		Deferral = AsyncEventArgs.GetDeferral();

		//Open();

		co_await AsyncEventArgs.wait_for_deferrals();

		co_return Result();

		co_return{};

	}

	void ContentDialogWindow::UpdateWindowSize() {


		// 计算基础窗口宽度（未应用缩放）
		int baseWidth = ImageGrid().Width() ?
			(int)ImageGrid().Width() :
			(int)(ContentDialogContent().DesiredSize().Width + 1);

		// 计算基础窗口高度（未应用缩放）
		int baseHeight =
			(int)(ContentDialogContent().DesiredSize().Height - 30) +
			(int)ImageGrid().Height();

		// 获取缩放比例
		float scale = (float)ContentDialogContent().XamlRoot().RasterizationScale();

		// 在ResizeClient中应用缩放比例
		AppWindow().ResizeClient(Windows::Graphics::SizeInt32(
			(int)(baseWidth * scale) + 1,
			(int)(baseHeight * scale) + 1
		));


		if (_center)
		{
			if (auto parent = m_parent.get())
			{
				AppWindow().Move(Windows::Graphics::PointInt32(
					parent.AppWindow().Position().X + (parent.AppWindow().Size().Width - AppWindow().Size().Width) / 2,
					parent.AppWindow().Position().Y + (parent.AppWindow().Size().Height - AppWindow().Size().Height) / 2));
			}
			else
			{
				auto displayArea = Microsoft::UI::Windowing::DisplayArea::GetFromWindowId(AppWindow().Id(), Microsoft::UI::Windowing::DisplayAreaFallback::Primary);
				AppWindow().Move(Windows::Graphics::PointInt32(
					(displayArea.OuterBounds().Width - AppWindow().Size().Width) / 2,
					(displayArea.OuterBounds().Height - AppWindow().Size().Height) / 2));
			}
		}

	}

	void ContentDialogWindow::OnContentLoaded(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		//SetForegroundWindow((HWND)WinUI3Package::WindowHelper::GetWindowHandle(*this));

		UpdateWindowSize();

		SetTitleBar(ContentDialogContent().TitleArea());


		if (SystemBackdrop() == nullptr)
		{
			auto requestedTheme = ContentDialogContent().RequestedTheme();

			switch (requestedTheme)
			{
				case Microsoft::UI::Xaml::ElementTheme::Light:
					ContentDialogContent().Background(Microsoft::UI::Xaml::Media::SolidColorBrush(Microsoft::UI::Colors::White()));
					break;
				case Microsoft::UI::Xaml::ElementTheme::Dark:
					ContentDialogContent().Background(Microsoft::UI::Xaml::Media::SolidColorBrush(
						Windows::UI::ColorHelper::FromArgb(0xFF, 0x20, 0x20, 0x20)));
					break;
				default:
					ContentDialogContent().Background(nullptr);
					break;
			}
		}

		if (SystemBackdrop() == nullptr || SystemBackdrop().try_as<Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop>() != nullptr)
		{
			// 如果系统背景为空或为DesktopAcrylicBackdrop，将透明度设为1.0
			ContentDialogContent().CommandSpace().Background().Opacity(1.0);
		}
		else
		{
			// 其他情况透明度设为0.5
			ContentDialogContent().CommandSpace().Background().Opacity(0.5);
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

	void ContentDialogWindow::OnActivated(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowActivatedEventArgs args)
	{
		//if (!this->ContentDialogContent().IsLoaded()) return;

		//if (args.WindowActivationState() == Microsoft::UI::Xaml::WindowActivationState::Deactivated)
		//{
		//	this->ContentDialogContent().AfterLostFocus();
		//}
		//else
		//{
		//	this->ContentDialogContent().AfterGotFocus();
		//}
	}

	void ContentDialogWindow::OnClosingRequestedBySystem()
	{
		if (auto parent = m_parent.get()) {
			parent.Activate();
			//_parent.Closed(m_OnParentClosed);
		}
		if (AppWindow()) AppWindow().Hide();

		//Close();
	}

	void ContentDialogWindow::OnClosingRequstedByCode()
	{
		if (auto parent = m_parent.get()) {
			parent.Activate();
			//_parent.Closed(m_OnParentClosed);
		}

		if (AppWindow()) AppWindow().Hide();

		//Close();
	}

	void ContentDialogWindow::OnParentClosed(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs args)
	{
		//if (_parent != nullptr) _parent.Closed(m_OnParentClosed);

		//m_parent = nullptr;

		//DispatcherQueue().TryEnqueue([&] {

		//	Close();
		//});
	}

	winrt::Windows::Foundation::IAsyncAction ContentDialogWindow::OnPrimaryButtonClick(winrt::Windows::Foundation::IInspectable const& sender, WinUI3Package::ContentDialogWindowButtonClickEventArgs const& args)
	{
		if (args.Handled()) co_return;

		args.Handled(true);

		auto ButtonDeferral = args.GetDeferral();

		Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary);

		auto Args = WinUI3Package::ContentDialogWindowButtonClickEventArgs();

		m_PrimaryButtonClick(*this, Args);

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

		m_SecondaryButtonClick(*this, Args);

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

		m_CloseButtonClick(*this, Args);

		co_await Args.wait_for_deferrals();

		AfterCommandSpaceButtonClick(Args);

		ButtonDeferral.Complete();

	}

	void ContentDialogWindow::DetermineTitleBarButtonForegroundColor()
	{
		switch (ContentDialogContent().ActualTheme())
		{
			case Microsoft::UI::Xaml::ElementTheme::Light: {
				AppWindow().TitleBar().ButtonForegroundColor(Microsoft::UI::Colors::Black());
				break;
			}

			case Microsoft::UI::Xaml::ElementTheme::Dark: {
				AppWindow().TitleBar().ButtonForegroundColor(Microsoft::UI::Colors::White());
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

	//void ContentDialogWindow::Result(Microsoft::UI::Xaml::Controls::ContentDialogResult result) {
	//	_content.Result(result);
	//}
	//Microsoft::UI::Xaml::Controls::ContentDialogResult ContentDialogWindow::Result() {
	//	return _content.Result();
	//}

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

	winrt::event_token ContentDialogWindow::PrimaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_PrimaryButtonClick.add(handler);
	}
	void ContentDialogWindow::PrimaryButtonClick(winrt::event_token const& token)
	{
		m_PrimaryButtonClick.remove(token);
	}

	winrt::event_token ContentDialogWindow::SecondaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_SecondaryButtonClick.add(handler);
	}
	void ContentDialogWindow::SecondaryButtonClick(winrt::event_token const& token)
	{
		m_SecondaryButtonClick.remove(token);
	}

	winrt::event_token ContentDialogWindow::CloseButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::ContentDialogWindow, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_CloseButtonClick.add(handler);
	}
	void ContentDialogWindow::CloseButtonClick(winrt::event_token const& token)
	{
		m_CloseButtonClick.remove(token);
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

	winrt::WinUI3Package::ContentDialogContent ContentDialogWindow::ContentDialogContent()
	{
		return ContentDialogContentControl();
	}

	void ContentDialogWindow::OnContentRightTapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs const& e)
	{
		m_ContentRightTapped(*this, e);
	}

}
