#include "pch.h"
#include "WindowedContentDialog.h"
#if __has_include("WindowedContentDialog.g.cpp")
#include "WindowedContentDialog.g.cpp"
#endif


#include <winrt/Microsoft.UI.Windowing.h>

#include "ContentDialogUtils.h"

namespace winrt::WinUI3Package::implementation
{



	winrt::Microsoft::UI::Xaml::DependencyProperty WindowedContentDialog::_IsPrimaryButtonEnabledProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsPrimaryButtonEnabled",
			xaml_typename<bool>(),
			xaml_typename<WinUI3Package::WindowedContentDialog>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, OnIsPrimaryButtonEnabledChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowedContentDialog::_IsSecondaryButtonEnabledProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsSecondaryButtonEnabled",
			xaml_typename<bool>(),
			xaml_typename<WinUI3Package::WindowedContentDialog>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, OnIsSecondaryButtonEnabledChangedStatic });

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowedContentDialog::_ContentFlowDirectionProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"ContentFlowDirection",
			xaml_typename<winrt::Microsoft::UI::Xaml::FlowDirection>(),
			xaml_typename<WinUI3Package::WindowedContentDialog>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				winrt::box_value(winrt::Microsoft::UI::Xaml::FlowDirection::LeftToRight),
				[](winrt::Microsoft::UI::Xaml::DependencyObject const& obj, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
				{
					auto self = winrt::get_self<WindowedContentDialog>(obj.as<WinUI3Package::WindowedContentDialog>());

					auto m_ContentDialogContent = self->m_ContentDialogWindow.ContentDialogContent();

					if (m_ContentDialogContent) {

						m_ContentDialogContent.FlowDirection(args.NewValue().as<winrt::Microsoft::UI::Xaml::FlowDirection>());
					}
				}
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowedContentDialog::_ContentMinWidthProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"ContentMinWidth",
			xaml_typename<double>(),
			xaml_typename<WinUI3Package::WindowedContentDialog>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				winrt::box_value(double(320.0f)),
				[](winrt::Microsoft::UI::Xaml::DependencyObject const& obj, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
				{
					auto self = winrt::get_self<WindowedContentDialog>(obj.as<WinUI3Package::WindowedContentDialog>());

					auto m_ContentDialogContent = self->m_ContentDialogWindow.ContentDialogContent();

					if (m_ContentDialogContent) {

						m_ContentDialogContent.MinWidth(args.NewValue().as<double>());
					}
				}
			}
		);


	WindowedContentDialog::WindowedContentDialog() {


		m_ContentDialogWindow = WinUI3Package::ContentDialogWindow();

		IsPrimaryButtonEnabled(true);
		IsSecondaryButtonEnabled(true);

		RequestedTheme(Microsoft::UI::Xaml::ElementTheme::Default);
		//SystemBackdrop(Microsoft::UI::Xaml::Media::MicaBackdrop());

		//BackdropType(WinUI3Package::BackdropType::Mica);

		PrimaryButtonText(L"");
		SecondaryButtonText(L"");
		CloseButtonText(L"");

		Underlay(WinUI3Package::UnderlayMode::SmokeLayer);

		UnderlaySystemBackdrop(WinUI3Package::UnderlaySystemBackdropOptions());
		//UnderlaySmokeLayer(WinUI3Package::UnderlaySmokeLayerOptions());

		CenterInParent(true);


		PrimaryButtonStyle(ContentDialogUtils::DefaultButtonStyle());
		SecondaryButtonStyle(ContentDialogUtils::DefaultButtonStyle());
		CloseButtonStyle(ContentDialogUtils::DefaultButtonStyle());
		HasTitleBar(true);

	}

	WindowedContentDialog::~WindowedContentDialog() {


		//Close();

		if (OwnerWindow()) OwnerWindow().SizeChanged(m_OnOwnerWindowSizeChanged);

		OwnerWindow(nullptr);
	}

	void WindowedContentDialog::Close()
	{
		if (m_ContentDialogWindow) {

			m_ContentDialogWindow.Close();
			m_ContentDialogWindow = nullptr;
		}

	}

	void WindowedContentDialog::InitializeContentDialogWindow()
	{

		if (HeaderImage()) m_ContentDialogWindow.HeaderImage(HeaderImage());
		if (!HeaderImageUri().empty()) m_ContentDialogWindow.HeaderImageUri(HeaderImageUri());

		m_ContentDialogWindow.Title(WindowTitle());
		m_ContentDialogWindow.DialogTitle(Title());
		m_ContentDialogWindow.DialogContent(Content());
		m_ContentDialogWindow.HasTitleBar(HasTitleBar());
		m_ContentDialogWindow.IsResizable(IsResizable());

		m_ContentDialogWindow.TitleTemplate(TitleTemplate());
		m_ContentDialogWindow.ContentTemplate(ContentTemplate());


		m_ContentDialogWindow.PrimaryButtonText(PrimaryButtonText());
		m_ContentDialogWindow.SecondaryButtonText(SecondaryButtonText());
		m_ContentDialogWindow.CloseButtonText(CloseButtonText());
		m_ContentDialogWindow.DefaultButton(DefaultButton());
		m_ContentDialogWindow.IsPrimaryButtonEnabled(IsPrimaryButtonEnabled());
		m_ContentDialogWindow.IsSecondaryButtonEnabled(IsSecondaryButtonEnabled());

		m_ContentDialogWindow.PrimaryButtonStyle(PrimaryButtonStyle());
		m_ContentDialogWindow.SecondaryButtonStyle(SecondaryButtonStyle());
		m_ContentDialogWindow.CloseButtonStyle(CloseButtonStyle());

		m_ContentDialogWindow.SystemBackdrop(SystemBackdrop());

		m_ContentDialogWindow.RequestedTheme(RequestedTheme());



		m_ContentDialogWindow.PrimaryButtonClick([this](auto& sender, auto& args) {


			m_PrimaryButtonClick(*this, args);

		});
		m_ContentDialogWindow.SecondaryButtonClick([this](auto& sender, auto& args) {


			m_SecondaryButtonClick(*this, args);

		});
		m_ContentDialogWindow.CloseButtonClick([this](auto& sender, auto& args) {


			m_CloseButtonClick(*this, args);

		});

		//m_ContentDialogWindow.ContentRightTapped();

		m_ContentDialogWindow.ContentRightTapped([this](auto& sender, auto& args) {


			m_ContentRightTapped(*this, args);

		});

		//m_ContentDialogWindow.ContentRightTapped({this, &WindowedContentDialog::m_ContentRightTapped });

		//Content().as<winrt::Microsoft::UI::Xaml::UIElement>().RightTapped(winrt::Microsoft::UI::Xaml::Input::RightTappedEventHandler());

		//m_dialogWindow.SecondaryButtonClick({ this, &WindowedContentDialog::m_SecondaryButtonClick });
		//m_dialogWindow.CloseButtonClick({ this, &WindowedContentDialog::m_CloseButtonClick });

	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> WindowedContentDialog::ShowAsync()
	{
		co_return co_await ShowAsync(true);
	}

	winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> WindowedContentDialog::ShowAsync(bool isModal)
	{

		InitializeContentDialogWindow();
		m_ContentDialogWindow.SetParent(OwnerWindow(), isModal, CenterInParent());
		SetUnderlay(m_ContentDialogWindow);

		//winrt::awaitable_event DialogEvent = {};

		winrt::event_token WindowLoadedEvent;
		winrt::event_token WindowClosedEvent;

		WindowLoadedEvent = m_ContentDialogWindow.Loaded([&](WinUI3Package::ContentDialogWindow const& Window, winrt::Windows::Foundation::IInspectable const& args)
		{

			m_Loaded(*this, args);

		});

		WindowClosedEvent = m_ContentDialogWindow.Closed([&](Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args) ->winrt::Windows::Foundation::IAsyncAction
		{

			m_Closed(*this, args);

			co_return;
		});

		auto Result = co_await m_ContentDialogWindow.ShowAsync();;

		//OwnerWindow(nullptr);

		//auto Result = m_ContentDialogWindow.Result();

		m_ContentDialogWindow.Loaded(WindowLoadedEvent);
		m_ContentDialogWindow.Closed(WindowClosedEvent);


		//m_ContentDialogWindow.Opened(m_onPopupOpened);
		//m_ContentDialogWindow.Loaded(m_onPopupLoaded);
		//m_ContentDialogWindow.Closed(m_onPopupClosed);

		//if (OwnerWindow()) OwnerWindow().SizeChanged(m_OnOwnerWindowSizeChanged);

		//OwnerWindow(nullptr);

		//m_ContentDialogWindow = nullptr;

		co_return Result;

	}

	void WindowedContentDialog::UpdateWindowSize() {

		//m_dialogWindow.DialogContent();

	}

	void WindowedContentDialog::SetUnderlay(WinUI3Package::ContentDialogWindow const& dialogWindow)
	{

		if (!OwnerWindow() || !OwnerWindow().Content() || !OwnerWindow().Content().XamlRoot())
		{
			return;
		}

		switch (Underlay())
		{
			case UnderlayMode::SmokeLayer:
				HandleSmokeLayer(dialogWindow);
				break;

			case UnderlayMode::SystemBackdrop:
				HandleSystemBackdrop(dialogWindow);
				break;
		}
	}

	void WindowedContentDialog::HandleSmokeLayer(WinUI3Package::ContentDialogWindow const& dialogWindow)
	{

		if (OwnerWindow() == nullptr || OwnerWindow().Content() == nullptr || OwnerWindow().Content().XamlRoot() == nullptr)
			return;

		//if (!UnderlaySmokeLayer() ||
		//	UnderlaySmokeLayer().SmokeLayerKind() == WindowedContentDialogSmokeLayerKind::None)
		//{
		//	return;
		//}

		//DisableOwnerEvents(dialogWindow);

		//Microsoft::UI::Xaml::Controls::Primitives::Popup popup = {};

		m_Popup = Microsoft::UI::Xaml::Controls::Primitives::Popup();

		m_Popup.XamlRoot(OwnerWindow().Content().XamlRoot());
		m_Popup.RequestedTheme(RequestedTheme());


		Microsoft::UI::Xaml::Shapes::Rectangle darkLayer = {};
		darkLayer.Opacity(0.0);
		//darkLayer.OpacityTransition(UnderlaySmokeLayer().OpacityTransition());

		auto Transition = Microsoft::UI::Xaml::ScalarTransition();
		Transition.Duration(std::chrono::milliseconds(250));
		darkLayer.OpacityTransition(Transition);

		Microsoft::UI::Xaml::Media::SolidColorBrush brush = {};
		brush.Color(ContentDialogUtils::SmokeFillColor());
		darkLayer.Fill(brush);


		SizeToXamlRoot(darkLayer, OwnerWindow());

		m_Popup.Child(darkLayer);
		SmokeLayerCache(darkLayer);


		dialogWindow.Opened(m_onPopupOpened);
		m_onPopupOpened = dialogWindow.Opened({ this, &WindowedContentDialog::DialogWindow_Opened });

		dialogWindow.Closed(m_onPopupClosed);
		m_onPopupClosed = dialogWindow.Closed({ this, &WindowedContentDialog::DialogWindow_Closed });

		//AttachPopupLifecycle(dialogWindow, m_Popup, true);
	}

	void WindowedContentDialog::HandleSystemBackdrop(WinUI3Package::ContentDialogWindow const& dialogWindow)
	{
		//if (UnderlaySystemBackdrop() == nullptr || UnderlaySystemBackdrop().Backdrop() == WinUI3Package::BackdropType::None)
		//	return;


		if (OwnerWindow() == nullptr || OwnerWindow().Content() == nullptr || OwnerWindow().Content().XamlRoot() == nullptr)
			return;

		//DisableOwnerEvents(dialogWindow);

		// Create the popup with helper
		m_Popup = ContentDialogUtils::CreatePopup(
			OwnerWindow().Content().XamlRoot(),
			UnderlaySystemBackdrop().CoverMode() == UnderlayCoverMode::Full,
			GetTitleBarOffset());

		// Store the backdrop layer
		BackdropLayerCache(m_Popup.Child().try_as<Microsoft::UI::Xaml::Controls::Border>());
		if (BackdropLayerCache())
		{
			BackdropLayerCache().OpacityTransition(UnderlaySystemBackdrop().OpacityTransition());
		}



		dialogWindow.Loaded(m_onPopupOpened);
		m_onPopupOpened = dialogWindow.Loaded({ this, &WindowedContentDialog::DialogWindow_Opened });

		dialogWindow.Closed(m_onPopupClosed);
		m_onPopupClosed = dialogWindow.Closed({ this, &WindowedContentDialog::DialogWindow_Closed });

		//AttachPopupLifecycle(dialogWindow, m_Popup, false);
	}

	void WindowedContentDialog::DisableOwnerEvents(WinUI3Package::ContentDialogWindow const& dialogWindow)
	{
		dialogWindow.Opened(m_DialogWindow_Opened);
		dialogWindow.Closed(m_DialogWindow_Closed);

		m_DialogWindow_Opened = dialogWindow.Opened({ this, &WindowedContentDialog::DialogWindow_Opened });
		m_DialogWindow_Closed = dialogWindow.Closed({ this, &WindowedContentDialog::DialogWindow_Closed });

	}

	void WindowedContentDialog::AttachPopupLifecycle(WinUI3Package::ContentDialogWindow const& dialogWindow, Microsoft::UI::Xaml::Controls::Primitives::Popup const& popup, bool isSmokeLayer)
	{

		//auto OnDialogWindowOpened = [&](WinUI3Package::ContentDialogWindow const& Window, winrt::Windows::Foundation::IInspectable const& args) {

		//	m_Popup.IsOpen(true);
		//	m_Popup.Child().Opacity(1.0f);

		//	OwnerWindow().SizeChanged(m_OnOwnerWindowSizeChanged);
		//	m_OnOwnerWindowSizeChanged = OwnerWindow().SizeChanged({ this, &WindowedContentDialog::OnOwnerWindowSizeChanged });

		//};

		//auto DialogWindow_ClosedPopup = [&](Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args) ->Windows::Foundation::IAsyncAction {


		//	m_Popup.Child().Opacity(0.f);

		//	m_Popup.IsOpen(false);

		//	m_Popup.Child(nullptr);

		//	OwnerWindow().SizeChanged(m_OnOwnerWindowSizeChanged);

		//	co_return;
		//};

		//if (isSmokeLayer)
		//{
		//	dialogWindow.Opened(m_onPopupOpened);
		//	m_onPopupOpened = dialogWindow.Opened(OnDialogWindowOpened);
		//}
		//else {

		//	dialogWindow.Loaded(m_onPopupLoaded);
		//	m_onPopupLoaded = dialogWindow.Loaded(OnDialogWindowOpened);
		//}

		//dialogWindow.Closed(m_onPopupClosed);
		//m_onPopupClosed = dialogWindow.Closed(DialogWindow_ClosedPopup);



	}

	void WindowedContentDialog::SizeToXamlRoot(Microsoft::UI::Xaml::FrameworkElement element, Microsoft::UI::Xaml::Window window)
	{

		element.Width(window.Content().XamlRoot().Size().Width);

		switch (Underlay())
		{
			case WinUI3Package::UnderlayMode::SmokeLayer:
				element.Height(window.Content().XamlRoot().Size().Height);
				break;

			case WinUI3Package::UnderlayMode::SystemBackdrop:
				element.Height(UnderlaySystemBackdrop().CoverMode() == WinUI3Package::UnderlayCoverMode::Full ? window.Content().XamlRoot().Size().Height : window.Content().XamlRoot().Size().Height - GetTitleBarOffset());
				break;
		}
	}

	int WindowedContentDialog::GetTitleBarOffset()
	{

		if (!OwnerWindow() || !OwnerWindow().AppWindow() || !OwnerWindow().AppWindow().TitleBar())
		{
			return 0;
		}

		auto heightOption = OwnerWindow().AppWindow().TitleBar().PreferredHeightOption();

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

	//void WindowedContentDialog::DialogWindow_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e)
	//{
	//	if (auto popup = sender.try_as<Microsoft::UI::Xaml::Controls::Primitives::Popup>()) {

	//		popup.IsOpen(true);
	//		popup.Child().Opacity(1.0f);
	//		m_OnOwnerWindowSizeChanged_Loaded = OwnerWindow().SizeChanged({this, &WindowedContentDialog::OnOwnerWindowSizeChanged});
	//	
	//	}

	//}

	void WindowedContentDialog::DialogWindow_Opened(WinUI3Package::ContentDialogWindow const& sender, winrt::Windows::Foundation::IInspectable const& e)
	{

		m_Popup.IsOpen(true);
		m_Popup.Child().Opacity(1.0f);

		if (OwnerWindow()) {

			OwnerWindow().SizeChanged(m_OnOwnerWindowSizeChanged);
			m_OnOwnerWindowSizeChanged = OwnerWindow().SizeChanged({ this, &WindowedContentDialog::OnOwnerWindowSizeChanged });
		}


		/*	if (auto control = OwnerWindow().Content().try_as<Microsoft::UI::Xaml::Controls::Control>())
				control.IsEnabled(false);*/
	}

	void WindowedContentDialog::DialogWindow_Closed(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& e)
	{


		m_Popup.Child().Opacity(0.f);

		m_Popup.IsOpen(false);

		m_Popup.Child(nullptr);

		if (OwnerWindow()) OwnerWindow().SizeChanged(m_OnOwnerWindowSizeChanged);

		//if (auto control = OwnerWindow().Content().try_as<Microsoft::UI::Xaml::Controls::Control>())
		//	control.IsEnabled(true);
	}

	void WindowedContentDialog::DialogWindow_ClosedPopup(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& e)
	{

		//if (auto popup = sender.try_as<Microsoft::UI::Xaml::Controls::Primitives::Popup>()) {

		//	popup.Child.Opacity = 0.0;
		//	await Task.Delay(popup.Child.OpacityTransition ? .Duration ? ? new TimeSpan(0));
		//	popup.IsOpen = false;
		//	popup.Child = null;
		//	OwnerWindow.SizeChanged -= OnOwnerWindowSizeChanged;
		//}
	}

	void WindowedContentDialog::OnOwnerWindowSizeChanged(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args)
	{

		switch (Underlay())
		{
			case WinUI3Package::UnderlayMode::SmokeLayer:
				SizeToXamlRoot(SmokeLayerCache(), OwnerWindow());
				break;

			case WinUI3Package::UnderlayMode::SystemBackdrop:
				SizeToXamlRoot(BackdropLayerCache(), OwnerWindow());
				break;
		}

	}

	winrt::event_token WindowedContentDialog::PrimaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_PrimaryButtonClick.add(handler);
	}

	void WindowedContentDialog::PrimaryButtonClick(winrt::event_token const& token)
	{
		m_PrimaryButtonClick.remove(token);
	}

	winrt::event_token WindowedContentDialog::SecondaryButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_SecondaryButtonClick.add(handler);
	}

	void WindowedContentDialog::SecondaryButtonClick(winrt::event_token const& token)
	{
		m_SecondaryButtonClick.remove(token);
	}

	winrt::event_token WindowedContentDialog::CloseButtonClick(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, WinUI3Package::ContentDialogWindowButtonClickEventArgs> const& handler)
	{
		return m_CloseButtonClick.add(handler);
	}

	void WindowedContentDialog::CloseButtonClick(winrt::event_token const& token)
	{
		m_CloseButtonClick.remove(token);
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> WindowedContentDialog::PrimaryButtonKeyboardAccelerators()
	{
		return m_ContentDialogWindow.PrimaryButtonKeyboardAccelerators();
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> WindowedContentDialog::SecondaryButtonKeyboardAccelerators()
	{
		return m_ContentDialogWindow.SecondaryButtonKeyboardAccelerators();
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> WindowedContentDialog::CloseButtonKeyboardAccelerators()
	{
		return m_ContentDialogWindow.CloseButtonKeyboardAccelerators();
	}

	winrt::event_token WindowedContentDialog::Opened(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Windows::Foundation::IInspectable> const& handler)
	{
		return m_Loaded.add(handler);
	}

	void WindowedContentDialog::Opened(winrt::event_token const& token)
	{
		m_Loaded.remove(token);
	}

	winrt::event_token WindowedContentDialog::Closed(Windows::Foundation::TypedEventHandler<WinUI3Package::WindowedContentDialog, Microsoft::UI::Xaml::WindowEventArgs> const& handler)
	{
		return m_Closed.add(handler);
	}

	void WindowedContentDialog::Closed(winrt::event_token const& token)
	{
		m_Closed.remove(token);
	}

	winrt::event_token WindowedContentDialog::ContentRightTapped(Windows::Foundation::TypedEventHandler<Windows::Foundation::IInspectable, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs> const& handler)
	{
		return m_ContentRightTapped.add(handler);
	}

	void WindowedContentDialog::ContentRightTapped(winrt::event_token const& token)
	{
		m_ContentRightTapped.remove(token);
	}

	void WindowedContentDialog::OnContentRightTapped(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::RightTappedRoutedEventArgs const& e)
	{

	}


}
