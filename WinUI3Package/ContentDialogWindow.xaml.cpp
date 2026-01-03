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

		NonMaximizableWindowWorkaround m_windowWorkaround = {};

		m_windowWorkaround.IsMaximizable(false);
		m_windowWorkaround.Window(*this);


		//HWND hwnd = (HWND)WindowHelper::GetWindowHandle(*this);

		//SetWindowLongPtr(hwnd, GWL_STYLE, GetWindowLongPtr(hwnd, GWL_STYLE) & ~WS_DLGFRAME);

		//Result(Microsoft::UI::Xaml::Controls::ContentDialogResult::None);

		//auto hWnd = (HWND)WinUI3Package::WindowHelper::GetWindowHandle(*this);

		//auto controlsHwnd = FindWindowEx(hWnd, 0, L"ReunionWindowingCaptionControls", L"ReunionCaptionControlsWindow");

		//if (controlsHwnd != nullptr) DestroyWindow(controlsHwnd);

		//m_Activated = Activated({ this, &ContentDialogWindow::OnActivated });;


		m_OnPrimaryButtonClick = this->ContentDialogContent().PrimaryButtonClick({ this, &ContentDialogWindow::OnPrimaryButtonClick });
		m_OnSecondaryButtonClick = this->ContentDialogContent().SecondaryButtonClick({ this, &ContentDialogWindow::OnSecondaryButtonClick });
		m_OnCloseButtonClick = this->ContentDialogContent().CloseButtonClick({ this, &ContentDialogWindow::OnCloseButtonClick });

		this->ContentDialogContent().ContentRightTapped({ this, &ContentDialogWindow::OnContentRightTapped });

		//this->ContentDialogContent().Loaded([&](auto&, auto&) {
		//	DetermineTitleBarButtonForegroundColor();
		//});

		m_ActualThemeChanged = this->ContentDialogContent().ActualThemeChanged([&](auto&, auto&) {
			DetermineTitleBarButtonForegroundColor();
		});

		//Microsoft::UI::Xaml::Media::ImageSource ImageSource = {};

		//Microsoft::UI::Xaml::Media::Imaging::BitmapImage bitmapImage = {};
		//bitmapImage.UriSource(Windows::Foundation::Uri(L"https://shared.fastly.steamstatic.com/store_item_assets/steam/apps/1364780/header.jpg"));

		//WindowImage().Source(bitmapImage);


		m_Closing = AppWindow().Closing([&](auto&, auto&) {

			AppWindow().Closing(m_Closing);

			OnClosingRequestedBySystem();

			//OutputDebugStringA("11111\r\n");

			//RemoveWindowSubclass(
			//	(HWND)WindowHelper::GetWindowHandle(*this),  // 窗口句柄
			//	TitleBarSubclassProc,                        // 子类过程函数
			//	0xFF69B4                                             // 子类ID（与SetWindowSubclass时的参数一致）
			//);
		});

		m_Closed = Closed([&](auto&, auto&) {

			Closed(m_Closed);

			if (_parent != nullptr) 	_parent.Closed(m_OnParentClosed);

			WindowImage().ImageOpened(m_ImageOpened);

			this->ContentDialogContent().PrimaryButtonClick(m_OnPrimaryButtonClick);
			this->ContentDialogContent().SecondaryButtonClick(m_OnSecondaryButtonClick);
			this->ContentDialogContent().CloseButtonClick(m_OnCloseButtonClick);
			this->ContentDialogContent().ActualThemeChanged(m_ActualThemeChanged);

			Deferral.Complete();

		});

		//SetWindowSubclass((HWND)WindowHelper::GetWindowHandle(*this), TitleBarSubclassProc, 0xFF69B4, 0);

		//this->ContentDialogContent() = WinUI3Package::ContentDialogthis->ContentDialogContent();
		this->ContentDialogContent().Loaded({ this, &ContentDialogWindow::OnContentLoaded });;

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

	ContentDialogWindow::~ContentDialogWindow() {

		//Closed(m_Closed);
		//if (_parent != nullptr) _parent.Closed(m_OnParentClosed);

		//this->ContentDialogContent().PrimaryButtonClick(m_OnPrimaryButtonClick);
		//this->ContentDialogContent().SecondaryButtonClick(m_OnSecondaryButtonClick);
		//this->ContentDialogContent().CloseButtonClick(m_OnCloseButtonClick);
	}

	void ContentDialogWindow::InitializeContentDialog(WinUI3Package::ContentDialogContent& component)
	{

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
			(int)(this->ContentDialogContent().DesiredSize().Width + 1);

		// 计算基础窗口高度（未应用缩放）
		int baseHeight =
			(int)(this->ContentDialogContent().DesiredSize().Height - 30) +
			(int)ImageGrid().Height();

		// 获取缩放比例
		float scale = (float)this->ContentDialogContent().XamlRoot().RasterizationScale();

		// 在ResizeClient中应用缩放比例
		AppWindow().ResizeClient(Windows::Graphics::SizeInt32(
			(int)(baseWidth * scale) + 1,
			(int)(baseHeight * scale) + 1
		));


		//AppWindow().ResizeClient(Windows::Graphics::SizeInt32(
		//	((int)((this->ContentDialogContent().DesiredSize().Width + 1) * this->ContentDialogContent().XamlRoot().RasterizationScale()) + 1) + ImageGrid().Width(),
		//	((int)((this->ContentDialogContent().DesiredSize().Height - 30) * this->ContentDialogContent().XamlRoot().RasterizationScale()) + 1) + ImageGrid().Height()));


		if (_center)
		{
			if (_parent != nullptr)
			{
				AppWindow().Move(Windows::Graphics::PointInt32(
					_parent.AppWindow().Position().X + (_parent.AppWindow().Size().Width - AppWindow().Size().Width) / 2,
					_parent.AppWindow().Position().Y + (_parent.AppWindow().Size().Height - AppWindow().Size().Height) / 2));
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

		SetTitleBar(this->ContentDialogContent().TitleArea());


		if (SystemBackdrop() == nullptr)
		{
			auto requestedTheme = RequestedTheme();

			// 根据主题设置不同的背景色
			switch (requestedTheme)
			{
				case Microsoft::UI::Xaml::ElementTheme::Light:
					Background(Microsoft::UI::Xaml::Media::SolidColorBrush(Microsoft::UI::Colors::White()));
					break;
				case Microsoft::UI::Xaml::ElementTheme::Dark:
					// ARGB值: 0xFF (不透明), 0x20, 0x20, 0x20 (深灰色)
					Background(Microsoft::UI::Xaml::Media::SolidColorBrush(
						Windows::UI::ColorHelper::FromArgb(0xFF, 0x20, 0x20, 0x20)));
					break;
				default:
					Background(nullptr);
					break;
			}
		}

		if (SystemBackdrop() == nullptr || SystemBackdrop().try_as<Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop>() != nullptr)
		{
			// 如果系统背景为空或为DesktopAcrylicBackdrop，将透明度设为1.0
			this->ContentDialogContent().CommandSpace().Background().Opacity(1.0);
		}
		else
		{
			// 其他情况透明度设为0.5
			this->ContentDialogContent().CommandSpace().Background().Opacity(0.5);
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
		//sizeChangedToken = this->ContentDialogContent().SizeChanged([&](auto&, auto&) {


		//	InitializeWindow();


		//});
		//this->ContentDialogContent().SizeChanged([&](auto&, auto&) {

		//	UpdateWindowSize();
		//});
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
		if (_parent) {
			_parent.Activate();
			//_parent.Closed(m_OnParentClosed);
		}
		if (AppWindow()) AppWindow().Hide();

		//Close();
	}

	void ContentDialogWindow::OnClosingRequstedByCode()
	{
		if (_parent) {
			_parent.Activate();
			//_parent.Closed(m_OnParentClosed);
		}

		if (AppWindow()) AppWindow().Hide();

		//Close();
	}

	void ContentDialogWindow::OnParentClosed(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs args)
	{
		//if (_parent != nullptr) _parent.Closed(m_OnParentClosed);

		_parent = nullptr;

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
		switch (this->ContentDialogContent().ActualTheme())
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

		OnClosingRequstedByCode();


		this->DispatcherQueue().TryEnqueue([this] {

			Close();
		});

	}

	void ContentDialogWindow::SetParent(Microsoft::UI::Xaml::Window const& parent, bool modal /*= true*/, bool center /*= true*/)
	{
		_center = center;

		if (_parent == parent) return;

		if (_parent != nullptr) _parent.Closed(m_OnParentClosed);

		_parent = parent;

		if (_parent != nullptr) m_OnParentClosed = _parent.Closed({ this, &ContentDialogWindow::OnParentClosed });;

		HWND ownerHwnd = parent ?
			winrt::Microsoft::UI::GetWindowFromWindowId(parent.AppWindow().Id()) :
			nullptr;
		HWND ownedHwnd = GetWindowFromWindowId(AppWindow().Id());

		if (ownedHwnd)
		{
			SetWindowLongPtr(ownedHwnd, -8, reinterpret_cast<LONG_PTR>(ownerHwnd));
		}

		_presenter.IsModal(parent && modal);
	}

	void ContentDialogWindow::Foreground(Microsoft::UI::Xaml::Media::Brush const& brush) {

		this->ContentDialogContent().Foreground(brush);
	}
	Microsoft::UI::Xaml::Media::Brush ContentDialogWindow::Foreground() {

		return this->ContentDialogContent().Foreground();
	}

	void ContentDialogWindow::Background(Microsoft::UI::Xaml::Media::Brush const& brush) {

		this->ContentDialogContent().Background(brush);
	}
	Microsoft::UI::Xaml::Media::Brush ContentDialogWindow::Background() {

		return this->ContentDialogContent().Background();
	}

	void ContentDialogWindow::BorderBrush(Microsoft::UI::Xaml::Media::Brush const& brush) {

		this->ContentDialogContent().BorderBrush(brush);
	}
	Microsoft::UI::Xaml::Media::Brush ContentDialogWindow::BorderBrush() {

		return this->ContentDialogContent().BorderBrush();
	}


	void ContentDialogWindow::BorderThickness(Microsoft::UI::Xaml::Thickness const& thickness) {
		this->ContentDialogContent().BorderThickness(thickness);
	}
	Microsoft::UI::Xaml::Thickness ContentDialogWindow::BorderThickness() {

		return this->ContentDialogContent().BorderThickness();
	}

	void ContentDialogWindow::FlowDirection(Microsoft::UI::Xaml::FlowDirection const& direction) {
		this->ContentDialogContent().FlowDirection(direction);
	}
	Microsoft::UI::Xaml::FlowDirection ContentDialogWindow::FlowDirection() {
		return this->ContentDialogContent().FlowDirection();
	}

	void ContentDialogWindow::TitleTemplate(Microsoft::UI::Xaml::DataTemplate const& value) {
		this->ContentDialogContent().TitleTemplate(value);
	}
	Microsoft::UI::Xaml::DataTemplate ContentDialogWindow::TitleTemplate() {
		return this->ContentDialogContent().TitleTemplate();
	}

	void ContentDialogWindow::ContentTemplate(Microsoft::UI::Xaml::DataTemplate const& value) {
		this->ContentDialogContent().ContentTemplate(value);
	}
	Microsoft::UI::Xaml::DataTemplate ContentDialogWindow::ContentTemplate() {
		return this->ContentDialogContent().ContentTemplate();
	}

	void ContentDialogWindow::PrimaryButtonText(winrt::hstring const& text) {
		this->ContentDialogContent().PrimaryButtonText(text);
	}
	winrt::hstring ContentDialogWindow::PrimaryButtonText() {
		return this->ContentDialogContent().PrimaryButtonText();
	}

	void ContentDialogWindow::SecondaryButtonText(winrt::hstring const& text) {
		this->ContentDialogContent().SecondaryButtonText(text);
	}
	winrt::hstring ContentDialogWindow::SecondaryButtonText() {
		return this->ContentDialogContent().SecondaryButtonText();
	}

	void ContentDialogWindow::CloseButtonText(winrt::hstring const& text) {
		this->ContentDialogContent().CloseButtonText(text);
	}
	winrt::hstring ContentDialogWindow::CloseButtonText() {
		return this->ContentDialogContent().CloseButtonText();
	}

	void ContentDialogWindow::IsPrimaryButtonEnabled(bool enabled) {
		this->ContentDialogContent().IsPrimaryButtonEnabled(enabled);

	}
	bool ContentDialogWindow::IsPrimaryButtonEnabled() {
		return this->ContentDialogContent().IsPrimaryButtonEnabled();
	}

	void ContentDialogWindow::IsSecondaryButtonEnabled(bool enabled) {
		this->ContentDialogContent().IsSecondaryButtonEnabled(enabled);
	}
	bool ContentDialogWindow::IsSecondaryButtonEnabled() {
		return this->ContentDialogContent().IsSecondaryButtonEnabled();
	}

	void ContentDialogWindow::DefaultButton(Microsoft::UI::Xaml::Controls::ContentDialogButton button) {
		this->ContentDialogContent().DefaultButton(button);
	}
	Microsoft::UI::Xaml::Controls::ContentDialogButton ContentDialogWindow::DefaultButton() {
		return this->ContentDialogContent().DefaultButton();
	}

	void ContentDialogWindow::PrimaryButtonStyle(Microsoft::UI::Xaml::Style const& style) {
		this->ContentDialogContent().PrimaryButtonStyle(style);
	}
	Microsoft::UI::Xaml::Style ContentDialogWindow::PrimaryButtonStyle() {
		return this->ContentDialogContent().PrimaryButtonStyle();
	}

	void ContentDialogWindow::SecondaryButtonStyle(Microsoft::UI::Xaml::Style const& style) {
		this->ContentDialogContent().SecondaryButtonStyle(style);
	}
	Microsoft::UI::Xaml::Style ContentDialogWindow::SecondaryButtonStyle() {
		return this->ContentDialogContent().SecondaryButtonStyle();
	}

	void ContentDialogWindow::CloseButtonStyle(Microsoft::UI::Xaml::Style const& style) {
		this->ContentDialogContent().CloseButtonStyle(style);
	}
	Microsoft::UI::Xaml::Style ContentDialogWindow::CloseButtonStyle() {
		return this->ContentDialogContent().CloseButtonStyle();
	}

	void ContentDialogWindow::DialogTitle(winrt::Windows::Foundation::IInspectable const& title) {
		this->ContentDialogContent().Title(title);
	}
	winrt::Windows::Foundation::IInspectable ContentDialogWindow::DialogTitle() {
		return this->ContentDialogContent().Title();
	}

	void ContentDialogWindow::DialogContent(winrt::Windows::Foundation::IInspectable const& Value) {
		this->ContentDialogContent().Content(Value);
	}
	winrt::Windows::Foundation::IInspectable ContentDialogWindow::DialogContent() {
		return this->ContentDialogContent().Content();
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

	void ContentDialogWindow::RequestedTheme(Microsoft::UI::Xaml::ElementTheme theme) {
		this->ContentDialogContent().RequestedTheme(theme);
	}
	Microsoft::UI::Xaml::ElementTheme ContentDialogWindow::RequestedTheme() {
		return this->ContentDialogContent().RequestedTheme();
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
				this->ContentDialogContent().IsHeaderImage(true);
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

			this->ContentDialogContent().IsHeaderImage(true);
		}
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> ContentDialogWindow::PrimaryButtonKeyboardAccelerators() {

		return this->ContentDialogContent().PrimaryButtonKeyboardAccelerators();
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> ContentDialogWindow::SecondaryButtonKeyboardAccelerators() {

		return this->ContentDialogContent().SecondaryButtonKeyboardAccelerators();
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> ContentDialogWindow::CloseButtonKeyboardAccelerators() {

		return this->ContentDialogContent().CloseButtonKeyboardAccelerators();
	}



	void ContentDialogWindow::OnContentRightTapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs const& e)
	{
		m_ContentRightTapped(*this, e);
	}

}
