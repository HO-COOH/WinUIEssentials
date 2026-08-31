#include "pch.h"
#include "WindowEx.h"
#if __has_include("WindowEx.g.cpp")
#include "WindowEx.g.cpp"
#endif

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Microsoft.UI.Input.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include "WindowsVersion.hpp"
#include <windowsx.h> //For GET_X_LPARAM and GET_Y_LPARAM
#include <cmath>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")
// Compiles with -lntdll
#include <winrt/Microsoft.UI.Content.h>
#include <wil/resource.h>

/*
	std::clamp is UB when lo > hi, which a caller setting MinWidth > MaxWidth would do.
	Written out longhand because windows.h defines min/max as macros here.
*/
constexpr int safeClamp(int value, int lo, int hi)
{
	if (value > hi)
		value = hi;
	if (value < lo)
		value = lo;
	return value;
}

/*
	FrameworkElement's size properties are doubles, and use NaN (Width/Height),
	0 (MinWidth/MinHeight) and +infinity (MaxWidth/MaxHeight) to mean "not set".
	Fold all of those onto the empty optional.
*/
tiny::optional<int, -1> safeSize(double value)
{
	if (!std::isfinite(value) || value <= 0.0)
		return {};

	if (value > static_cast<double>(INT_MAX))
		return INT_MAX;

	return static_cast<int>(value);
}

namespace winrt::WinUI3Package::implementation
{

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_titleProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_extendsContentIntoTitleBarProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_systemBackdropProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_isMinimizableProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_isMaximizableProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_isResizableProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_isAlwaysOnTopProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_isShownInSwitcherProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_hasBorderProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_hasTitleBarProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_iconProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_contextMenuProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_titleBarHeightProperty = nullptr;
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_nonClientRegionKindProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
		L"NonClientRegionKind",
		winrt::xaml_typename<winrt::Microsoft::UI::Input::NonClientRegionKind>(),
		winrt::xaml_typename<class_type>(),
		winrt::Microsoft::UI::Xaml::PropertyMetadata{
			winrt::box_value(winrt::Microsoft::UI::Input::NonClientRegionKind::Passthrough),
			&WindowEx::onNonClientRegionKindChanged
		}
	);
	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::s_rootWindowProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
		L"RootWindow",
		winrt::xaml_typename<uint64_t>(),
		winrt::xaml_typename<class_type>(),
		nullptr
	);

	std::unordered_map<HWND, winrt::event_token> WindowEx::s_windowResizeRevokers;

	void WindowEx::EnsureDependencyProperties()
	{
		if (s_titleProperty)
			return;

		s_titleProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Title",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::hstring{}), &WindowEx::onTitleChanged }
		);

		s_extendsContentIntoTitleBarProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"ExtendsContentIntoTitleBar",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(false), &WindowEx::onExtendsContentIntoTitleBarChanged }
		);

		s_systemBackdropProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"SystemBackdrop",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Media::SystemBackdrop>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &WindowEx::onSystemBackdropChanged }
		);

		s_isMinimizableProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsMinimizable",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(true), &WindowEx::onIsMinimizableChanged }
		);

		s_isMaximizableProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsMaximizable",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(true), &WindowEx::onIsMaximizableChanged }
		);

		s_isResizableProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsResizable",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(true), &WindowEx::onIsResizableChanged }
		);

		s_isAlwaysOnTopProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsAlwaysOnTop",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(false), &WindowEx::onIsAlwaysOnTopChanged }
		);

		s_isShownInSwitcherProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsShownInSwitcher",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(true), &WindowEx::onIsShownInSwitcherChanged }
		);

		s_hasBorderProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"HasBorder",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(true), &WindowEx::onHasBorderChanged }
		);

		s_hasTitleBarProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"HasTitleBar",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(true), &WindowEx::onHasTitleBarChanged }
		);

		s_iconProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Icon",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(winrt::hstring{}), &WindowEx::onIconChanged }
		);

		s_contextMenuProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"ContextMenu",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::MenuFlyout>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &WindowEx::onContextMenuChanged }
		);

		s_titleBarHeightProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"TitleBarHeight",
			winrt::xaml_typename<winrt::Microsoft::UI::Windowing::TitleBarHeightOption>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata
			{
				winrt::box_value(winrt::Microsoft::UI::Windowing::TitleBarHeightOption::Standard),
				&WindowEx::onTitleBarHeightChanged
			}
		);
	}

	HWND WindowEx::getHwndFromElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
	{
		auto xamlRoot = element.XamlRoot();
		if (!xamlRoot)
			return {};

		auto contentIslandEnv = xamlRoot.ContentIslandEnvironment();
		if (!contentIslandEnv)
			return{};

		auto appWindowId = contentIslandEnv.AppWindowId();
		return reinterpret_cast<HWND>(appWindowId.Value);
	}

	winrt::Microsoft::UI::Windowing::AppWindow WindowEx::getAppWindowFromElement(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
	{
		return winrt::Microsoft::UI::Windowing::AppWindow::GetFromWindowId(winrt::Microsoft::UI::GetWindowIdFromWindow(getHwndFromElement(element)));
	}

	WindowEx::WindowEx()
	{
		HorizontalContentAlignment(winrt::Microsoft::UI::Xaml::HorizontalAlignment::Stretch);
		VerticalContentAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Stretch);
		m_windowClosedToken = m_window.Closed(winrt::auto_revoke, [this](auto&&...)
		{
			revokeAppWindowChanged();
		});

		//Keeps RawWidth/RawHeight following the window, so they are usable as binding sources
		m_appWindowChangedToken = m_appWindow.Changed({ this, &WindowEx::onAppWindowChanged });

		addFrameworkPropertyCallbacks();
		syncWindowStateToProperties();

		m_constructed = true;
	}

	WindowEx::~WindowEx()
	{
		revokeAppWindowChanged();
	}

	void WindowEx::attachToWindow()
	{
		/*
			Setting the content is what makes the window keep a reference to us, so refuse while
			the constructor is still running, no matter who asks. See the constructor.
		*/
		if (!m_constructed || std::exchange(m_attachedToWindow, true))
			return;

		m_window.Content(*this);
	}

	void WindowEx::prepareToShow()
	{
		attachToWindow();

		/*
			Startup runs in one call stack, nothing has pumped yet, so the queued layout pass
			would only happen after the window is already on screen. Do it now instead.
		*/
		if (m_attachedToWindow)
			UpdateLayout();
	}

	void WindowEx::revokeAppWindowChanged() noexcept
	{
		if (!m_appWindowChangedToken)
			return;

		try
		{
			m_appWindow.Changed(std::exchange(m_appWindowChangedToken, {}));
		}
		catch (...)
		{
		}
	}

	void WindowEx::addFrameworkPropertyCallbacks()
	{
		RegisterPropertyChangedCallback(winrt::Microsoft::UI::Xaml::Controls::ContentControl::ContentProperty(), { this, &WindowEx::onContentChanged });
		RegisterPropertyChangedCallback(winrt::Microsoft::UI::Xaml::FrameworkElement::WidthProperty(), { this, &WindowEx::onFrameworkWidthChanged });
		RegisterPropertyChangedCallback(winrt::Microsoft::UI::Xaml::FrameworkElement::HeightProperty(), { this, &WindowEx::onFrameworkHeightChanged });
		RegisterPropertyChangedCallback(winrt::Microsoft::UI::Xaml::FrameworkElement::MinWidthProperty(), { this, &WindowEx::onFrameworkMinWidthChanged });
		RegisterPropertyChangedCallback(winrt::Microsoft::UI::Xaml::FrameworkElement::MaxWidthProperty(), { this, &WindowEx::onFrameworkMaxWidthChanged });
		RegisterPropertyChangedCallback(winrt::Microsoft::UI::Xaml::FrameworkElement::MinHeightProperty(), { this, &WindowEx::onFrameworkMinHeightChanged });
		RegisterPropertyChangedCallback(winrt::Microsoft::UI::Xaml::FrameworkElement::MaxHeightProperty(), { this, &WindowEx::onFrameworkMaxHeightChanged });
	}

	void WindowEx::syncWindowStateToProperties()
	{
		/*
			Seed the properties from the window we just created, so a read before the first
			write reports reality rather than the registered default.
		*/
		m_syncingSizeFromWindow = true;
		auto const size = windowSizeInPixels();
		m_syncingSizeFromWindow = false;

		SetValue(s_isMinimizableProperty, winrt::box_value(m_overlappedPresenter.IsMinimizable()));
		SetValue(s_isMaximizableProperty, winrt::box_value(m_overlappedPresenter.IsMaximizable()));
		SetValue(s_isResizableProperty, winrt::box_value(m_overlappedPresenter.IsResizable()));
		SetValue(s_isAlwaysOnTopProperty, winrt::box_value(m_overlappedPresenter.IsAlwaysOnTop()));
		SetValue(s_isShownInSwitcherProperty, winrt::box_value(m_appWindow.IsShownInSwitchers()));
	}

	winrt::Microsoft::UI::Xaml::Window WindowEx::Window()
	{
		//The earliest point a XAML declared window touches us, x:Bind runs it from InitializeComponent
		attachToWindow();
		return m_window;
	}


#pragma region WindowForwarding
	winrt::hstring WindowEx::Title()
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(s_titleProperty));
	}

	void WindowEx::Title(winrt::hstring const& value)
	{
		SetValue(s_titleProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::TitleProperty()
	{
		return s_titleProperty;
	}

	bool WindowEx::ExtendsContentIntoTitleBar()
	{
		return winrt::unbox_value<bool>(GetValue(s_extendsContentIntoTitleBarProperty));
	}

	void WindowEx::ExtendsContentIntoTitleBar(bool value)
	{
		SetValue(s_extendsContentIntoTitleBarProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::ExtendsContentIntoTitleBarProperty()
	{
		return s_extendsContentIntoTitleBarProperty;
	}

	winrt::Microsoft::UI::Xaml::Media::SystemBackdrop WindowEx::SystemBackdrop()
	{
		return GetValue(s_systemBackdropProperty).try_as<winrt::Microsoft::UI::Xaml::Media::SystemBackdrop>();
	}

	void WindowEx::SystemBackdrop(winrt::Microsoft::UI::Xaml::Media::SystemBackdrop const& value)
	{
		SetValue(s_systemBackdropProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::SystemBackdropProperty()
	{
		return s_systemBackdropProperty;
	}

	void WindowEx::Activate()
	{
		prepareToShow();
		m_window.Activate();
	}

	void WindowEx::Close()
	{
		m_window.Close();
	}

	void WindowEx::SetTitleBar(winrt::Microsoft::UI::Xaml::UIElement const& titleBar)
	{
		//The element only counts as a title bar while it is inside the window content
		attachToWindow();
		m_window.SetTitleBar(titleBar);
	}

	winrt::event_token WindowEx::Activated(winrt::Windows::Foundation::TypedEventHandler<
		winrt::Windows::Foundation::IInspectable,
		winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs> const& handler)
	{
		return m_window.Activated(handler);
	}

	void WindowEx::Activated(winrt::event_token const& token)
	{
		m_window.Activated(token);
	}

	winrt::event_token WindowEx::Closed(winrt::Windows::Foundation::TypedEventHandler<
		winrt::Windows::Foundation::IInspectable,
		winrt::Microsoft::UI::Xaml::WindowEventArgs> const& handler)
	{
		return m_window.Closed(handler);
	}

	void WindowEx::Closed(winrt::event_token const& token)
	{
		m_window.Closed(token);
	}

	winrt::event_token WindowEx::VisibilityChanged(winrt::Windows::Foundation::TypedEventHandler<
		winrt::Windows::Foundation::IInspectable,
		winrt::Microsoft::UI::Xaml::WindowVisibilityChangedEventArgs> const& handler)
	{
		return m_window.VisibilityChanged(handler);
	}

	void WindowEx::VisibilityChanged(winrt::event_token const& token)
	{
		m_window.VisibilityChanged(token);
	}
#pragma endregion


#pragma region Size
	/*
		Read the live window rather than a cached copy, so a read straight after a Resize is
		not stale. onAppWindowChanged raises PropertyChanged so bindings keep up.
	*/
	int WindowEx::RawWidth()
	{
		return windowSizeInPixels().Width;
	}

	int WindowEx::RawHeight()
	{
		return windowSizeInPixels().Height;
	}

	int WindowEx::LeftInset()
	{
		return unscaleForDpi(LeftInsetRaw(), Dpi());
	}
	int WindowEx::LeftInsetRaw()
	{
		return m_appWindowTitleBar.LeftInset();
	}
	int WindowEx::RightInset()
	{
		return unscaleForDpi(RightInsetRaw(), Dpi());
	}
	int WindowEx::RightInsetRaw()
	{
		return m_appWindowTitleBar.RightInset();
	}
	unsigned int WindowEx::Dpi()
	{
		return GetDpiForWindow(m_hwnd);
	}

	winrt::Windows::Graphics::SizeInt32 WindowEx::windowSizeInPixels()
	{
		RECT rect{};
		if (!GetWindowRect(m_hwnd, &rect))
			return m_appWindow.Size();

		return {
			static_cast<int32_t>(rect.right - rect.left),
			static_cast<int32_t>(rect.bottom - rect.top)
		};
	}

	void WindowEx::resizeWindowInPixels(int widthInPixels, int heightInPixels)
	{
		SetWindowPos(
			m_hwnd,
			nullptr,
			0,
			0,
			widthInPixels,
			heightInPixels,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE
		);
	}

	int WindowEx::currentWidth()
	{
		return unscaleForDpi(windowSizeInPixels().Width, Dpi());
	}

	int WindowEx::currentHeight()
	{
		return unscaleForDpi(windowSizeInPixels().Height, Dpi());
	}

	void WindowEx::resizeWindow(int widthInDips, int heightInDips)
	{
		auto const dpi = Dpi();
		resizeWindowInPixels(
			scaleForDpi(safeClamp(widthInDips, m_minMaxSize.MinWidth(), m_minMaxSize.MaxWidth()), dpi),
			scaleForDpi(safeClamp(heightInDips, m_minMaxSize.MinHeight(), m_minMaxSize.MaxHeight()), dpi)
		);
	}

	winrt::Windows::Foundation::Size WindowEx::clientSizeInDips()
	{
		//The island fills the client area, and XamlRoot reports it in DIPs already
		if (auto const xamlRoot = XamlRoot())
			return xamlRoot.Size();

		RECT client{};
		if (!GetClientRect(m_hwnd, &client))
			return {};

		auto const dpi = static_cast<float>(Dpi());
		return {
			(client.right - client.left) * 96.f / dpi,
			(client.bottom - client.top) * 96.f / dpi
		};
	}

	winrt::Windows::Foundation::Size WindowEx::layoutSize(winrt::Windows::Foundation::Size const& availableSize)
	{
		/*
			Width/Height size the whole window, frame included, so laying out against them
			would push the content under the frame. Lay out in the client area instead, and
			fall back to what the framework offered while the client area is empty (minimized).
		*/
		auto const client = clientSizeInDips();
		return {
			client.Width > 0.f ? client.Width : availableSize.Width,
			client.Height > 0.f ? client.Height : availableSize.Height
		};
	}

	winrt::Windows::Foundation::Size WindowEx::MeasureOverride(winrt::Windows::Foundation::Size availableSize)
	{
		auto const size = layoutSize(availableSize);
		base_type::MeasureOverride(size);
		return size;
	}

	winrt::Windows::Foundation::Size WindowEx::ArrangeOverride(winrt::Windows::Foundation::Size finalSize)
	{
		auto const size = layoutSize(finalSize);
		base_type::ArrangeOverride(size);
		return size;
	}
#pragma endregion

#pragma region CaptionButton
	bool WindowEx::IsMinimizable()
	{
		return winrt::unbox_value<bool>(GetValue(s_isMinimizableProperty));
	}

	void WindowEx::IsMinimizable(bool value)
	{
		SetValue(s_isMinimizableProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::IsMinimizableProperty()
	{
		return s_isMinimizableProperty;
	}

	bool WindowEx::IsMaximizable()
	{
		return winrt::unbox_value<bool>(GetValue(s_isMaximizableProperty));
	}

	void WindowEx::IsMaximizable(bool value)
	{
		SetValue(s_isMaximizableProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::IsMaximizableProperty()
	{
		return s_isMaximizableProperty;
	}

	bool WindowEx::IsResizable()
	{
		return winrt::unbox_value<bool>(GetValue(s_isResizableProperty));
	}

	void WindowEx::IsResizable(bool value)
	{
		SetValue(s_isResizableProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::IsResizableProperty()
	{
		return s_isResizableProperty;
	}

	bool WindowEx::IsAlwaysOnTop()
	{
		return winrt::unbox_value<bool>(GetValue(s_isAlwaysOnTopProperty));
	}

	void WindowEx::IsAlwaysOnTop(bool value)
	{
		SetValue(s_isAlwaysOnTopProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::IsAlwaysOnTopProperty()
	{
		return s_isAlwaysOnTopProperty;
	}

	bool WindowEx::IsShownInSwitcher()
	{
		return winrt::unbox_value<bool>(GetValue(s_isShownInSwitcherProperty));
	}

	void WindowEx::IsShownInSwitcher(bool value)
	{
		SetValue(s_isShownInSwitcherProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::IsShownInSwitcherProperty()
	{
		return s_isShownInSwitcherProperty;
	}
#pragma endregion


#pragma region Win32WindowStyle
	bool WindowEx::HasBorder()
	{
		return winrt::unbox_value<bool>(GetValue(s_hasBorderProperty));
	}

	void WindowEx::HasBorder(bool value)
	{
		SetValue(s_hasBorderProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::HasBorderProperty()
	{
		return s_hasBorderProperty;
	}

	bool WindowEx::HasTitleBar()
	{
		return winrt::unbox_value<bool>(GetValue(s_hasTitleBarProperty));
	}

	void WindowEx::HasTitleBar(bool value)
	{
		SetValue(s_hasTitleBarProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::HasTitleBarProperty()
	{
		return s_hasTitleBarProperty;
	}

	winrt::hstring WindowEx::Icon()
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(s_iconProperty));
	}

	void WindowEx::Icon(winrt::hstring const& value)
	{
		SetValue(s_iconProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::IconProperty()
	{
		return s_iconProperty;
	}

	winrt::Microsoft::UI::Xaml::Controls::MenuFlyout WindowEx::ContextMenu()
	{
		return GetValue(s_contextMenuProperty).try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyout>();
	}

	void WindowEx::ContextMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& value)
	{
		SetValue(s_contextMenuProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::ContextMenuProperty()
	{
		return s_contextMenuProperty;
	}

	winrt::Microsoft::UI::Windowing::TitleBarHeightOption WindowEx::TitleBarHeight()
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Windowing::TitleBarHeightOption>(GetValue(s_titleBarHeightProperty));
	}

	void WindowEx::TitleBarHeight(winrt::Microsoft::UI::Windowing::TitleBarHeightOption value)
	{
		SetValue(s_titleBarHeightProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::TitleBarHeightProperty()
	{
		return s_titleBarHeightProperty;
	}
#pragma endregion


	winrt::Microsoft::UI::Windowing::AppWindow WindowEx::AppWindow()
	{
		//AppWindow().Show() shows the window without going through us, so be ready for it
		prepareToShow();
		return m_appWindow;
	}

	uint64_t WindowEx::Hwnd()
	{
		//Same for whatever win32 does with it, ShowWindow included
		prepareToShow();
		return reinterpret_cast<uint64_t>(m_hwnd);
	}


	void WindowEx::Transparent(bool value)
	{
		if (value)
		{
			setSubClassIfNeeded();
			MARGINS margin{};
			DwmExtendFrameIntoClientArea(m_hwnd, &margin);
		}
		m_transparent = value;
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WindowEx::NonClientRegionKindProperty()
	{
		return s_nonClientRegionKindProperty;
	}

	void WindowEx::SetNonClientRegionKind(winrt::Microsoft::UI::Xaml::FrameworkElement const& element, winrt::Microsoft::UI::Input::NonClientRegionKind value)
	{
		element.SetValue(s_nonClientRegionKindProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Input::NonClientRegionKind WindowEx::GetNonClientRegionKind(winrt::Microsoft::UI::Xaml::FrameworkElement const& element)
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Input::NonClientRegionKind>(element.GetValue(s_nonClientRegionKindProperty));
	}


	void WindowEx::setWin32TitlebarTheme(BOOL isDark)
	{
		DwmSetWindowAttribute(
			m_hwnd,
			GetWindowsVersion().dwBuildNumber >= 19041 ? 20 : 19,
			&isDark,
			sizeof(isDark)
		);
	}

	/*Rounded, and in 64 bit, so that a size survives a scale/unscale round trip*/
	int WindowEx::scaleForDpi(int value, int dpi)
	{
		auto const scaled = (static_cast<long long>(value) * dpi + 48) / 96;
		return scaled > INT_MAX ? INT_MAX : static_cast<int>(scaled);
	}

	int WindowEx::unscaleForDpi(int value, int dpi)
	{
		if (dpi <= 0)
			return value;

		return static_cast<int>((static_cast<long long>(value) * 96 + dpi / 2) / dpi);
	}

	void WindowEx::setSubClassIfNeeded()
	{
		if (m_registered)
			return;


		if (SetWindowSubclass(m_hwnd, &subclassProc, SubClassId, reinterpret_cast<DWORD_PTR>(this)))
		{
			m_registered = true;
		}
	}

	LRESULT CALLBACK WindowEx::subclassProc(
		HWND hwnd,
		UINT msg,
		WPARAM wparam,
		LPARAM lparam,
		UINT_PTR uIdSubclass,
		DWORD_PTR dwRefData)
	{
		if (uIdSubclass != SubClassId)
			return DefSubclassProc(hwnd, msg, wparam, lparam);

		auto self = reinterpret_cast<WindowEx*>(dwRefData);
		switch (msg)
		{
			case WM_WINDOWPOSCHANGING:
				self->m_delayWindowShowHelper.OnWM_WindowPosChanging(*reinterpret_cast<WINDOWPOS*>(lparam));
				break;
			case WM_ERASEBKGND:
				if (self->clearBackground(hwnd, reinterpret_cast<HDC>(wparam)))
					return 1;
				break;
			case WM_CONTEXTMENU:
			{
				if (auto contextMenu = self->ContextMenu())
				{
					if (!self->m_contextMenuHost)
						self->m_contextMenuHost = {};
					self->m_contextMenuHost.Move({ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) });
					contextMenu.ShowAt(self->m_contextMenuHost);
					return 0;
				}
				break;
			}
			case WM_GETMINMAXINFO:
				return self->onGetMinMaxInfo(wparam, lparam);
			case WM_SYSCOMMAND:
				if (wparam == SC_MAXIMIZE && !self->m_overlappedPresenter.IsMaximizable())
					return 1;
				break;
		}
		return DefSubclassProc(hwnd, msg, wparam, lparam);
	}

	LRESULT WindowEx::onGetMinMaxInfo(WPARAM, LPARAM pMinMaxInfo)
	{
		if (!m_minMaxSize)
			return 1;

		auto pt = reinterpret_cast<MINMAXINFO*>(pMinMaxInfo);

		//The track sizes are window sizes, which is what Min/Max Width/Height already are
		auto const dpi = Dpi();
		if (m_minMaxSize.m_minWidth)
			pt->ptMinTrackSize.x = scaleForDpi(*m_minMaxSize.m_minWidth, dpi);
		if (m_minMaxSize.m_maxWidth)
			pt->ptMaxTrackSize.x = scaleForDpi(*m_minMaxSize.m_maxWidth, dpi);
		if (m_minMaxSize.m_minHeight)
			pt->ptMinTrackSize.y = scaleForDpi(*m_minMaxSize.m_minHeight, dpi);
		if (m_minMaxSize.m_maxHeight)
			pt->ptMaxTrackSize.y = scaleForDpi(*m_minMaxSize.m_maxHeight, dpi);
		return 0;
	}

	bool WindowEx::isLightTheme()
	{
		HKEY key{};
		RegOpenKeyEx(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)", 0, KEY_READ, &key);
		DWORD value{};
		DWORD bytes = sizeof(value);
		auto hr = RegGetValue(key, nullptr, LR"(AppsUseLightTheme)", RRF_RT_DWORD, nullptr, &value, &bytes);
		return static_cast<bool>(value);
	}

	void WindowEx::clampWindowSize()
	{
		//Min/Max Width/Height are in DIPs, so compare in DIPs
		auto const width = currentWidth();
		auto const height = currentHeight();

		auto const clampedWidth = safeClamp(width, m_minMaxSize.MinWidth(), m_minMaxSize.MaxWidth());
		auto const clampedHeight = safeClamp(height, m_minMaxSize.MinHeight(), m_minMaxSize.MaxHeight());
		if (width != clampedWidth || height != clampedHeight)
			resizeWindow(clampedWidth, clampedHeight);
	}

	void WindowEx::updateNonClientRegions(winrt::Microsoft::UI::Input::NonClientRegionKind kind, HWND hwnd)
	{
		auto const scale = GetDpiForWindow(hwnd);
		std::vector<winrt::Windows::Graphics::RectInt32> rectArray;
		for (auto controlRef : s_allWindows.at(hwnd))
		{
			if (auto strongControl = controlRef.get())
			{
				if (auto const kindValue = GetNonClientRegionKind(strongControl); kindValue == kind)
				{
					auto transform = strongControl.TransformToVisual(nullptr);
					auto rect = transform.TransformBounds(winrt::Windows::Foundation::Rect{
						0.f,
						0.f,
						static_cast<float>(strongControl.ActualWidth()),
						static_cast<float>(strongControl.ActualHeight())
						});
					rectArray.push_back(scaleRect(rect, scale));
				}
			}
		}

		winrt::Microsoft::UI::Input::InputNonClientPointerSource::GetForWindowId(winrt::Microsoft::UI::GetWindowIdFromWindow(hwnd))
			.SetRegionRects(kind, rectArray);
	}

	bool WindowEx::clearBackground(HWND hwnd, HDC hdc)
	{
		RECT rect{};
		if (GetClientRect(hwnd, &rect))
		{
			FillRect(hdc, &rect, m_backgroundBlackBrush);
			return true;
		}
		return true;
	}



#pragma region PropertyChangedHandlers
	void WindowEx::onTitleChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		GetSelf(d)->m_window.Title(winrt::unbox_value<winrt::hstring>(e.NewValue()));
	}

	void WindowEx::onExtendsContentIntoTitleBarChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		auto const value = winrt::unbox_value<bool>(e.NewValue());
		self->m_window.ExtendsContentIntoTitleBar(value);
		
		if (value)
			return;
		self->setWin32TitlebarTheme(self->ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Dark);
		
		if (self->m_themeChangedRevoker)
			return;

		self->m_themeChangedRevoker = self->ActualThemeChanged(winrt::auto_revoke, [self](auto&&...)
		{
			if (!self->ExtendsContentIntoTitleBar())
				self->setWin32TitlebarTheme(self->ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Dark);
		});
	}

	void WindowEx::onSystemBackdropChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto newValue = e.NewValue();
		GetSelf(d)->m_window.SystemBackdrop(
			newValue ? newValue.try_as<winrt::Microsoft::UI::Xaml::Media::SystemBackdrop>() : nullptr
		);
	}

	void WindowEx::onIsMinimizableChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		GetSelf(d)->m_overlappedPresenter.IsMinimizable(winrt::unbox_value<bool>(e.NewValue()));
	}

	void WindowEx::onIsMaximizableChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		auto const value = winrt::unbox_value<bool>(e.NewValue());
		//WM_SYSCOMMAND/SC_MAXIMIZE has to be swallowed for this to actually stick
		if (!value)
			self->setSubClassIfNeeded();
		self->m_overlappedPresenter.IsMaximizable(value);
	}

	void WindowEx::onIsResizableChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		GetSelf(d)->m_overlappedPresenter.IsResizable(winrt::unbox_value<bool>(e.NewValue()));
	}

	void WindowEx::onIsAlwaysOnTopChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		GetSelf(d)->m_overlappedPresenter.IsAlwaysOnTop(winrt::unbox_value<bool>(e.NewValue()));
	}

	void WindowEx::onIsShownInSwitcherChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		GetSelf(d)->m_appWindow.IsShownInSwitchers(winrt::unbox_value<bool>(e.NewValue()));
	}

	void WindowEx::onHasBorderChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		auto const hasBorder = winrt::unbox_value<bool>(e.NewValue());

		//A window without a border cannot have a title bar
		auto hasTitleBar = self->HasTitleBar();
		if (!hasBorder && hasTitleBar)
			hasTitleBar = false;

		self->m_overlappedPresenter.SetBorderAndTitleBar(hasBorder, hasTitleBar);
	}

	void WindowEx::onHasTitleBarChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		auto const hasTitleBar = winrt::unbox_value<bool>(e.NewValue());

		//A title bar requires a border
		auto hasBorder = self->HasBorder();
		if (hasTitleBar && !hasBorder)
			hasBorder = true;

		self->m_overlappedPresenter.SetBorderAndTitleBar(hasBorder, hasTitleBar);
	}

	void WindowEx::onIconChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto const value = winrt::unbox_value<winrt::hstring>(e.NewValue());
		//SetIcon throws on an empty path, and clearing the icon is not something it can express
		if (value.empty())
			return;

		GetSelf(d)->m_appWindow.SetIcon(value);
	}

	void WindowEx::onContextMenuChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto newValue = e.NewValue();
		if (!newValue)
			return;

		if (auto modernStandardMenu = newValue.try_as<WinUI3Package::ModernStandardWindowContextMenu>())
			modernStandardMenu.Window(GetSelf(d)->m_window);
	}

	void WindowEx::onTitleBarHeightChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		GetSelf(d)->m_appWindowTitleBar.PreferredHeightOption(winrt::unbox_value<winrt::Microsoft::UI::Windowing::TitleBarHeightOption>(e.NewValue()));
	}

	void WindowEx::onNonClientRegionKindChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto newValue = e.NewValue();
		if (!newValue)
			return;

		auto element = d.try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
		if (!element)
			return;

		element.LayoutUpdated([weakRef = winrt::make_weak(element), refAdded = false, lastBounds = winrt::Windows::Foundation::Rect{}](auto const& sender, auto...) mutable
		{
			if (auto element = weakRef.get())
			{
				auto const hwnd = getHwndFromElement(element);
				if (!hwnd || !element.IsLoaded())
					return;

				if (!refAdded)
				{
					s_allWindows[hwnd].push_back(winrt::make_weak(element));
					auto elementRefIter = --s_allWindows[hwnd].end();

					element.Unloaded([hwnd, elementRefIter](auto&&...) {
						auto& thisWindow = s_allWindows.at(hwnd);
						thisWindow.erase(elementRefIter);
						if (thisWindow.empty())
							s_allWindows.erase(hwnd);
					});

					refAdded = true;
				}

				auto transform = element.TransformToVisual(nullptr);
				auto const newBounds = transform.TransformBounds(winrt::Windows::Foundation::Rect{
					0.f,
					0.f,
					static_cast<float>(element.ActualWidth()),
					static_cast<float>(element.ActualHeight())
					});
				if (newBounds == lastBounds)
					return;

				lastBounds = newBounds;
				updateNonClientRegions(GetNonClientRegionKind(element), hwnd);
			}
		});
	}

	void WindowEx::onFrameworkWidthChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const&,
		winrt::Microsoft::UI::Xaml::DependencyProperty const&)
	{
		if (m_syncingSizeFromWindow)
			return;

		auto const value = Width();
		if (!std::isfinite(value))
			return;

		resizeWindow(static_cast<int>(value), currentHeight());
	}

	void WindowEx::onFrameworkHeightChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const&,
		winrt::Microsoft::UI::Xaml::DependencyProperty const&)
	{
		if (m_syncingSizeFromWindow)
			return;

		auto const value = Height();
		if (!std::isfinite(value))
			return;

		resizeWindow(currentWidth(), static_cast<int>(value));
	}

	void WindowEx::onFrameworkMinWidthChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const&,
		winrt::Microsoft::UI::Xaml::DependencyProperty const&)
	{
		setSubClassIfNeeded();
		m_minMaxSize.MinWidth(safeSize(MinWidth()));
		clampWindowSize();
	}

	void WindowEx::onFrameworkMaxWidthChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const&,
		winrt::Microsoft::UI::Xaml::DependencyProperty const&)
	{
		setSubClassIfNeeded();
		m_minMaxSize.MaxWidth(safeSize(MaxWidth()));
		clampWindowSize();
	}

	void WindowEx::onFrameworkMinHeightChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const&,
		winrt::Microsoft::UI::Xaml::DependencyProperty const&)
	{
		setSubClassIfNeeded();
		m_minMaxSize.MinHeight(safeSize(MinHeight()));
		clampWindowSize();
	}

	void WindowEx::onFrameworkMaxHeightChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const&,
		winrt::Microsoft::UI::Xaml::DependencyProperty const&)
	{
		setSubClassIfNeeded();
		m_minMaxSize.MaxHeight(safeSize(MaxHeight()));
		clampWindowSize();
	}
#pragma endregion

	void WindowEx::onAppWindowChanged(
		winrt::Microsoft::UI::Windowing::AppWindow const& sender,
		winrt::Microsoft::UI::Windowing::AppWindowChangedEventArgs const& args)
	{
		if (!args.DidSizeChange())
			return;

		raisePropertyChange(L"RawWidth");
		raisePropertyChange(L"RawHeight");
	}

	void WindowEx::onContentChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
		winrt::Microsoft::UI::Xaml::DependencyProperty const& property)
	{
		attachToWindow();
		if (!ExtendsContentIntoTitleBar())
			setWin32TitlebarTheme(ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Dark);

		m_themeChangedRevoker = ActualThemeChanged(winrt::auto_revoke, [this](auto&&...) 
		{
			if (!ExtendsContentIntoTitleBar())
				setWin32TitlebarTheme(ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Dark);
		});
	}
}
