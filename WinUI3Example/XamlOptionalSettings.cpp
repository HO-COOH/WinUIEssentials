#include "pch.h"
#include "XamlOptionalSettings.h"
#if __has_include("XamlOptionalSettings.g.cpp")
#include "XamlOptionalSettings.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void XamlOptionalSettings::DefaultStyleOptimizations(bool value)
	{
		setAndSave(Flag::DefaultStyleOptimizations, value);
	}

	void XamlOptionalSettings::DeferContextFlyoutInit(bool value)
	{
		setAndSave(Flag::DeferContextFlyoutInit, value);
	}

	void XamlOptionalSettings::IconNoGridOptimization(bool value)
	{
		setAndSave(Flag::IconNoGridOptimization, value);
	}

	void XamlOptionalSettings::OptimizeApplyStyles(bool value)
	{
		setAndSave(Flag::OptimizeApplyStyles, value);
	}

	void XamlOptionalSettings::requiresRestart()
	{
		m_requiresRestart = true;
		raisePropertyChange(L"RequiresRestart");
	}

	void XamlOptionalSettings::setAndSave(Flag value, bool set)
	{
		set ? setFlag(value) : removeFlag(value);
		raisePropertyChange(L"EnabledCount");
		save();
		requiresRestart();
	}
}
