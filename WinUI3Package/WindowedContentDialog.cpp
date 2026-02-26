#include "pch.h"
#include "WindowedContentDialog.h"
#if __has_include("WindowedContentDialog.g.cpp")
#include "WindowedContentDialog.g.cpp"
#endif


#include <winrt/Microsoft.UI.Windowing.h>
#include "ContentDialogWindow.xaml.h"
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

					auto m_ContentDialogContent = self->m_contentDialogWindowImpl->ContentDialogContent();

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

					auto m_ContentDialogContent = self->m_contentDialogWindowImpl->ContentDialogContent();

					if (m_ContentDialogContent) {

						m_ContentDialogContent.MinWidth(args.NewValue().as<double>());
					}
				}
			}
		);


	WindowedContentDialog::WindowedContentDialog()
	{
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

		auto defaultButtonStyle = ContentDialogUtils::DefaultButtonStyle();
		PrimaryButtonStyle(defaultButtonStyle);
		SecondaryButtonStyle(defaultButtonStyle);
		CloseButtonStyle(defaultButtonStyle);
		HasTitleBar(true);

	}

	WindowedContentDialog::~WindowedContentDialog() 
	{
		Close();
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
		m_ContentDialogWindow.HasTitleBar(HasTitleBar());
		m_ContentDialogWindow.IsResizable(IsResizable());

		auto content = m_contentDialogWindowImpl->ContentDialogContent();
		content.Title(Title());
		content.Content(Content());
		content.TitleTemplate(TitleTemplate());
		content.ContentTemplate(ContentTemplate());
		content.PrimaryButtonText(PrimaryButtonText());
		content.SecondaryButtonText(SecondaryButtonText());
		content.CloseButtonText(CloseButtonText());
		content.DefaultButton(DefaultButton());
		content.IsPrimaryButtonEnabled(IsPrimaryButtonEnabled());
		content.IsSecondaryButtonEnabled(IsSecondaryButtonEnabled());
		content.PrimaryButtonStyle(PrimaryButtonStyle());
		content.SecondaryButtonStyle(SecondaryButtonStyle());
		content.CloseButtonStyle(CloseButtonStyle());
		content.RequestedTheme(RequestedTheme());

		m_ContentDialogWindow.SystemBackdrop(SystemBackdrop());

		//m_ContentDialogWindow.ContentRightTapped();

		m_ContentDialogWindow.ContentRightTapped([this](auto& sender, auto& args) {


			m_ContentRightTapped(*this, args);

		});

		//m_ContentDialogWindow.ContentRightTapped({this, &WindowedContentDialog::m_ContentRightTapped });

		//Content().as<winrt::Microsoft::UI::Xaml::UIElement>().RightTapped(winrt::Microsoft::UI::Xaml::Input::RightTappedEventHandler());

		//m_dialogWindow.SecondaryButtonClick({ this, &WindowedContentDialog::m_SecondaryButtonClick });
		//m_dialogWindow.CloseButtonClick({ this, &WindowedContentDialog::m_CloseButtonClick });

	}

	winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult> WindowedContentDialog::ShowAsync()
	{
		return winrt::Windows::Foundation::IAsyncOperation<Microsoft::UI::Xaml::Controls::ContentDialogResult>();
	}


	winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> WindowedContentDialog::ShowAsync(winrt::Microsoft::UI::Xaml::Window const& parent)
	{

		InitializeContentDialogWindow();
		m_ContentDialogWindow.SetParent(parent, CenterInParent());
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

		m_ContentDialogWindow = nullptr;

		//m_ContentDialogWindow.Opened(m_onPopupOpened);
		//m_ContentDialogWindow.Loaded(m_onPopupLoaded);
		//m_ContentDialogWindow.Closed(m_onPopupClosed);

		//if (OwnerWindow()) OwnerWindow().SizeChanged(m_OnOwnerWindowSizeChanged);

		//OwnerWindow(nullptr);

		//m_ContentDialogWindow = nullptr;

		co_return Result;

	}

	void WindowedContentDialog::SetUnderlay(WinUI3Package::ContentDialogWindow const& dialogWindow)
	{

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
		auto owner = ownerWindow();
		if (!owner)
			return;

		auto content = owner.Content();
		if (!content)
			return;

		m_Popup = Microsoft::UI::Xaml::Controls::Primitives::Popup();

		m_Popup.XamlRoot(content.XamlRoot());
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


		SizeToXamlRoot(darkLayer, owner);

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
		auto owner = ownerWindow();
		if (!owner)
			return;

		auto content = owner.Content();
		if (!content)
			return;

		m_Popup = ContentDialogUtils::CreatePopup(
			content.XamlRoot(),
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
	}

	void WindowedContentDialog::DisableOwnerEvents(WinUI3Package::ContentDialogWindow const& dialogWindow)
	{
		dialogWindow.Opened(m_DialogWindow_Opened);
		dialogWindow.Closed(m_DialogWindow_Closed);

		m_DialogWindow_Opened = dialogWindow.Opened({ this, &WindowedContentDialog::DialogWindow_Opened });
		m_DialogWindow_Closed = dialogWindow.Closed({ this, &WindowedContentDialog::DialogWindow_Closed });
	}


	void WindowedContentDialog::SizeToXamlRoot(Microsoft::UI::Xaml::FrameworkElement element, Microsoft::UI::Xaml::Window window)
	{
		if (!window || !window.Content() || !window.Content().XamlRoot()) return;

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
		auto owner = ownerWindow();
		if (!owner)
			return 0;

		auto const heightOption = owner.AppWindow().TitleBar().PreferredHeightOption();

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

	void WindowedContentDialog::DialogWindow_Opened(WinUI3Package::ContentDialogWindow const& sender, winrt::Windows::Foundation::IInspectable const& e)
	{

		m_Popup.IsOpen(true);
		m_Popup.Child().Opacity(1.0f);

		if (auto owner = ownerWindow()) 
		{
			owner.SizeChanged(m_OnOwnerWindowSizeChanged);
			m_OnOwnerWindowSizeChanged = owner.SizeChanged({ this, &WindowedContentDialog::OnOwnerWindowSizeChanged });
		}
	}

	void WindowedContentDialog::DialogWindow_Closed(winrt::Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& e)
	{


		m_Popup.Child().Opacity(0.f);

		m_Popup.IsOpen(false);

		m_Popup.Child(nullptr);

		if (auto owner = ownerWindow()) 
			owner.SizeChanged(m_OnOwnerWindowSizeChanged);

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
		if (!ownerWindow()) return;

		switch (Underlay())
		{
			case WinUI3Package::UnderlayMode::SmokeLayer:
				SizeToXamlRoot(SmokeLayerCache(), ownerWindow());
				break;

			case WinUI3Package::UnderlayMode::SystemBackdrop:
				SizeToXamlRoot(BackdropLayerCache(), ownerWindow());
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
		return m_contentDialogWindowImpl->ContentDialogContent().PrimaryButtonKeyboardAccelerators();
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> WindowedContentDialog::SecondaryButtonKeyboardAccelerators()
	{
		return m_contentDialogWindowImpl->ContentDialogContent().SecondaryButtonKeyboardAccelerators();
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator> WindowedContentDialog::CloseButtonKeyboardAccelerators()
	{
		return m_contentDialogWindowImpl->ContentDialogContent().CloseButtonKeyboardAccelerators();
	}

	winrt::Microsoft::UI::Xaml::Window WindowedContentDialog::ownerWindow()
	{
		return winrt::get_self<ContentDialogWindow>(m_ContentDialogWindow)->m_parent.get();
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

	double WindowedContentDialog::ContentMinWidth()
	{
		return winrt::unbox_value<double>(GetValue(ContentMinWidthProperty()));
	}

	void WindowedContentDialog::ContentMinWidth(double value)
	{
		SetValue(ContentMinWidthProperty(), winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowedContentDialog::ContentMinWidthProperty()
	{
		return _ContentMinWidthProperty;
	}

	winrt::Microsoft::UI::Xaml::FlowDirection WindowedContentDialog::ContentFlowDirection()
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Xaml::FlowDirection>(GetValue(ContentFlowDirectionProperty()));
	}

	void WindowedContentDialog::ContentFlowDirection(winrt::Microsoft::UI::Xaml::FlowDirection const& value)
	{
		SetValue(ContentFlowDirectionProperty(), winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowedContentDialog::ContentFlowDirectionProperty()
	{
		return _ContentFlowDirectionProperty;
	}

	WinUI3Package::ContentDialogWindow WindowedContentDialog::GetDialogWindow()
	{
		return m_ContentDialogWindow;
	}

	void WindowedContentDialog::OnIsPrimaryButtonEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		UNREFERENCED_PARAMETER(sender);
		UNREFERENCED_PARAMETER(e);
		auto self = get_self<WindowedContentDialog>(sender.as<winrt::WinUI3Package::WindowedContentDialog>());
		self->m_contentDialogWindowImpl->ContentDialogContent().IsPrimaryButtonEnabled(e.NewValue().as<bool>());
	}

	void WindowedContentDialog::OnIsSecondaryButtonEnabledChangedStatic(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e)
	{
		UNREFERENCED_PARAMETER(sender);
		UNREFERENCED_PARAMETER(e);
		auto self = get_self<WindowedContentDialog>(sender.as<winrt::WinUI3Package::WindowedContentDialog>());
		self->m_contentDialogWindowImpl->ContentDialogContent().IsSecondaryButtonEnabled(e.NewValue().as<bool>());
	}

	Microsoft::UI::Xaml::Media::Imaging::BitmapImage WindowedContentDialog::HeaderImage() const
	{
		return _HeaderImage;
	}

	void WindowedContentDialog::HeaderImage(const Microsoft::UI::Xaml::Media::Imaging::BitmapImage& value)
	{
		if (_HeaderImage != value)
		{
			_HeaderImage = value;
		}
	}

	winrt::hstring WindowedContentDialog::HeaderImageUri() const
	{
		return _HeaderImageUri;
	}

	void WindowedContentDialog::HeaderImageUri(const winrt::hstring& value)
	{
		if (_HeaderImageUri != value)
		{
			_HeaderImageUri = value;
		}
	}

	Microsoft::UI::Xaml::Shapes::Rectangle WindowedContentDialog::SmokeLayerCache() const
	{
		return _SmokeLayerCache;
	}

	void WindowedContentDialog::SmokeLayerCache(const Microsoft::UI::Xaml::Shapes::Rectangle& value)
	{
		if (_SmokeLayerCache != value)
		{
			_SmokeLayerCache = value;
		}
	}

	Microsoft::UI::Xaml::Controls::Border WindowedContentDialog::BackdropLayerCache() const
	{
		return _BackdropLayerCache;
	}

	void WindowedContentDialog::BackdropLayerCache(const Microsoft::UI::Xaml::Controls::Border& value)
	{
		if (_BackdropLayerCache != value)
		{
			_BackdropLayerCache = value;
		}
	}

	winrt::hstring WindowedContentDialog::WindowTitle() const
	{
		return _WindowTitle;
	}

	void WindowedContentDialog::WindowTitle(const winrt::hstring& value)
	{
		if (_WindowTitle != value)
		{
			_WindowTitle = value;
		}
	}

	winrt::Windows::Foundation::IInspectable WindowedContentDialog::Title() const
	{
		return _Title;
	}

	void WindowedContentDialog::Title(const winrt::Windows::Foundation::IInspectable& value)
	{
		if (_Title != value)
		{
			_Title = value;
		}
	}

	winrt::Windows::Foundation::IInspectable WindowedContentDialog::Content() const
	{
		return _Content;
	}

	void WindowedContentDialog::Content(const winrt::Windows::Foundation::IInspectable& value)
	{
		if (_Content != value)
		{
			_Content = value;
		}
	}

	Microsoft::UI::Xaml::ElementTheme WindowedContentDialog::RequestedTheme() const
	{
		return _RequestedTheme;
	}

	void WindowedContentDialog::RequestedTheme(const Microsoft::UI::Xaml::ElementTheme& value)
	{
		if (_RequestedTheme != value)
		{
			_RequestedTheme = value;
		}
	}

	Microsoft::UI::Xaml::Media::SystemBackdrop WindowedContentDialog::SystemBackdrop() const
	{
		return _SystemBackdrop;
	}

	void WindowedContentDialog::SystemBackdrop(const Microsoft::UI::Xaml::Media::SystemBackdrop& value)
	{
		if (_SystemBackdrop != value)
		{
			_SystemBackdrop = value;
		}
	}

	Microsoft::UI::Xaml::DataTemplate WindowedContentDialog::TitleTemplate() const
	{
		return _TitleTemplate;
	}

	void WindowedContentDialog::TitleTemplate(const Microsoft::UI::Xaml::DataTemplate& value)
	{
		if (_TitleTemplate != value)
		{
			_TitleTemplate = value;
		}
	}

	Microsoft::UI::Xaml::DataTemplate WindowedContentDialog::ContentTemplate() const
	{
		return _ContentTemplate;
	}

	void WindowedContentDialog::ContentTemplate(const Microsoft::UI::Xaml::DataTemplate& value)
	{
		if (_ContentTemplate != value)
		{
			_ContentTemplate = value;
		}
	}

	winrt::hstring WindowedContentDialog::PrimaryButtonText() const
	{
		return _PrimaryButtonText;
	}

	void WindowedContentDialog::PrimaryButtonText(const winrt::hstring& value)
	{
		if (_PrimaryButtonText != value)
		{
			_PrimaryButtonText = value;
		}
	}

	winrt::hstring WindowedContentDialog::SecondaryButtonText() const
	{
		return _SecondaryButtonText;
	}

	void WindowedContentDialog::SecondaryButtonText(const winrt::hstring& value)
	{
		if (_SecondaryButtonText != value)
		{
			_SecondaryButtonText = value;
		}
	}

	winrt::hstring WindowedContentDialog::CloseButtonText() const
	{
		return _CloseButtonText;
	}

	void WindowedContentDialog::CloseButtonText(const winrt::hstring& value)
	{
		if (_CloseButtonText != value)
		{
			_CloseButtonText = value;
		}
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowedContentDialog::IsPrimaryButtonEnabledProperty()
	{
		return _IsPrimaryButtonEnabledProperty;
	}

	bool WindowedContentDialog::IsPrimaryButtonEnabled() const
	{
		return winrt::unbox_value<bool>(GetValue(_IsPrimaryButtonEnabledProperty));
	}

	void WindowedContentDialog::IsPrimaryButtonEnabled(const bool& value)
	{
		SetValue(_IsPrimaryButtonEnabledProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowedContentDialog::IsSecondaryButtonEnabledProperty()
	{
		return _IsSecondaryButtonEnabledProperty;
	}

	bool WindowedContentDialog::IsSecondaryButtonEnabled() const
	{
		return winrt::unbox_value<bool>(GetValue(_IsSecondaryButtonEnabledProperty));
	}

	void WindowedContentDialog::IsSecondaryButtonEnabled(const bool& value)
	{
		SetValue(_IsSecondaryButtonEnabledProperty, winrt::box_value(value));
	}

	Microsoft::UI::Xaml::Controls::ContentDialogButton WindowedContentDialog::DefaultButton() const
	{
		return _DefaultButton;
	}

	void WindowedContentDialog::DefaultButton(const Microsoft::UI::Xaml::Controls::ContentDialogButton& value)
	{
		if (_DefaultButton != value)
		{
			_DefaultButton = value;
		}
	}

	WinUI3Package::UnderlayMode WindowedContentDialog::Underlay() const
	{
		return _Underlay;
	}

	void WindowedContentDialog::Underlay(const WinUI3Package::UnderlayMode& value)
	{
		if (_Underlay != value)
		{
			_Underlay = value;
		}
	}

	WinUI3Package::UnderlaySystemBackdropOptions WindowedContentDialog::UnderlaySystemBackdrop() const
	{
		return _UnderlaySystemBackdrop;
	}

	void WindowedContentDialog::UnderlaySystemBackdrop(const WinUI3Package::UnderlaySystemBackdropOptions& value)
	{
		if (_UnderlaySystemBackdrop != value)
		{
			_UnderlaySystemBackdrop = value;
		}
	}

	bool WindowedContentDialog::CenterInParent() const
	{
		return _CenterInParent;
	}

	void WindowedContentDialog::CenterInParent(const bool& value)
	{
		if (_CenterInParent != value)
		{
			_CenterInParent = value;
		}
	}

	Microsoft::UI::Xaml::Style WindowedContentDialog::PrimaryButtonStyle() const
	{
		return _PrimaryButtonStyle;
	}

	void WindowedContentDialog::PrimaryButtonStyle(const Microsoft::UI::Xaml::Style& value)
	{
		if (_PrimaryButtonStyle != value)
		{
			_PrimaryButtonStyle = value;
		}
	}

	Microsoft::UI::Xaml::Style WindowedContentDialog::SecondaryButtonStyle() const
	{
		return _SecondaryButtonStyle;
	}

	void WindowedContentDialog::SecondaryButtonStyle(const Microsoft::UI::Xaml::Style& value)
	{
		if (_SecondaryButtonStyle != value)
		{
			_SecondaryButtonStyle = value;
		}
	}

	Microsoft::UI::Xaml::Style WindowedContentDialog::CloseButtonStyle() const
	{
		return _CloseButtonStyle;
	}

	void WindowedContentDialog::CloseButtonStyle(const Microsoft::UI::Xaml::Style& value)
	{
		if (_CloseButtonStyle != value)
		{
			_CloseButtonStyle = value;
		}
	}

	bool WindowedContentDialog::HasTitleBar() const
	{
		return _HasTitleBar;
	}

	void WindowedContentDialog::HasTitleBar(const bool& value)
	{
		if (_HasTitleBar != value)
		{
			_HasTitleBar = value;
		}
	}

	bool WindowedContentDialog::IsResizable() const
	{
		return _IsResizable;
	}

	void WindowedContentDialog::IsResizable(const bool& value)
	{
		if (_IsResizable != value)
		{
			_IsResizable = value;
		}
	}

}
