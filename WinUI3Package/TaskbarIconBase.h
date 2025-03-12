#pragma once
#include "NotifyIconData.h"
#include <string_view>
#include <functional>
#include "PopupMenu.h"
#include "MenuFlyoutWrapper.h"
#include <variant>
#include <optional>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include "TaskbarIconMessageWindow.h"

#pragma region Forward Declaration
struct TaskbarIconXamlEvents;
struct TaskbarIconEvents;
#pragma endregion

/**
 * @brief This class provides basic functionality for implementing a Taskbar tray icon, including:
 *   1. Setting a tooltip
 *   2. Setting event callback for tray icon. See `TaskbarIconXamlEvents` for supported events
 *	 3. Setting right-click menu theme (and handles it automatically if menu is set)
 *	 4. Show/Remove this icon
 * @note This class is not intended to be used directly and in fact its constructor and destructor are `protected`.
 * Instantiate a derived class (i.e. `NormalTaskbarIcon` and `ThemeAdaptiveIcon`) instead.
 */
class TaskbarIconBase
{
protected:
	NotifyIconData m_iconData;
	std::variant<std::monostate, MenuFlyoutWrapper, PopupMenu> m_menu;
	TaskbarIconMessageWindow m_messageWindow;
	winrt::Microsoft::UI::Xaml::ElementTheme m_theme{ winrt::Microsoft::UI::Xaml::ElementTheme::Default };
	TaskbarIconXamlEvents* m_ptrXamlEvents{ nullptr };
	TaskbarIconEvents* m_ptrEvents{ nullptr };
	PopupMenu& getPopupMenu();
	TaskbarIconBase();
	~TaskbarIconBase();

	void OnWM_CONTEXTMENU(WPARAM wparam, LPARAM lparam);
	void OnWM_COMMAND(WPARAM wparam, LPARAM lparam);
public:


	constexpr static UINT CallbackMessage = 0x1001;

	TaskbarIconBase& ToolTip(std::wstring_view value);
	TaskbarIconBase& Guid(winrt::guid value);
	
	void Show();
	void Remove();

	void SetMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenu);

	void SetEvents(TaskbarIconXamlEvents& events);

	void SetTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme);


	


	friend class TaskbarIconMessageWindow;
};
