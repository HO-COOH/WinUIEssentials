#pragma once

#include <winrt/base.h>
#include <ShObjIdl_core.h>

struct ITaskbarList3;


/**
 * @brief Wrapper for controlling taskbar icon progress
 */
class Taskbar
{
	static ITaskbarList3* getPtr()
	{
		static winrt::com_ptr<ITaskbarList3> instance = []
			{
				winrt::com_ptr<ITaskbarList3> ptr;
				CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_ALL, __uuidof(ITaskbarList3), ptr.put_void());
				return ptr;
			}();
			return instance.get();
	}

public:
	enum class ProgressState : unsigned
	{
		NoProgress,
		Indeterminate,
		Normal,
		Error,
		Paused
	};


	/**
	 * @brief Set taskbar icon progress state of a window
	 *
	 * @param hwnd window handle
	 */
	static void SetProgressState(HWND hwnd, ProgressState state)
	{
		getPtr()->SetProgressState(hwnd, static_cast<TBPFLAG>(getRawState(state)));
	}

	/**
	 * @brief Set taskbar icon progress value
	 *
	 * @param hwnd window handle
	 * @param current current value, default to the number of percentage if `maximum` not specified
	 * @param maximum default = `100`'
	 */
	static void SetProgressValue(HWND hwnd, ULONGLONG current, ULONGLONG maximum = 100)
	{
		getPtr()->SetProgressValue(hwnd, current, maximum);
	}
private:
	static constexpr unsigned getRawState(ProgressState state)
	{
		switch (state)
		{
		case Taskbar::ProgressState::NoProgress:
			return TBPF_NOPROGRESS;
		case Taskbar::ProgressState::Indeterminate:
			return TBPF_INDETERMINATE;
		case Taskbar::ProgressState::Normal:
			return TBPF_NORMAL;
		case Taskbar::ProgressState::Error:
			return TBPF_ERROR;
		case Taskbar::ProgressState::Paused:
			return TBPF_PAUSED;
		}
	}
};
