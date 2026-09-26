#include "pch.h"
#include "MicaBackdropWithFallback.h"
#if __has_include("MicaBackdropWithFallback.g.cpp")
#include "MicaBackdropWithFallback.g.cpp"
#endif


namespace winrt::WinUI3Package::implementation
{
	MicaBackdropWithFallback::MicaBackdropWithFallback(winrt::Microsoft::UI::Xaml::Media::SystemBackdrop const& fallback) :
		m_fallbackOverrides{ fallback ?
			fallback.as<winrt::Microsoft::UI::Xaml::Media::ISystemBackdropOverrides>() : nullptr }
	{
	}

	winrt::Microsoft::UI::Xaml::Media::SystemBackdrop MicaBackdropWithFallback::Fallback()
	{
		return m_fallbackOverrides.try_as<winrt::Microsoft::UI::Xaml::Media::SystemBackdrop>();
	}

	void MicaBackdropWithFallback::Fallback(winrt::Microsoft::UI::Xaml::Media::SystemBackdrop const& value)
	{
		m_fallbackOverrides = value ?
			value.as<winrt::Microsoft::UI::Xaml::Media::ISystemBackdropOverrides>() : 
			nullptr;
	}

	void MicaBackdropWithFallback::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		if (isMicaSupported())
			base_type::OnTargetConnected(connectedTarget, xamlRoot);
		else
			m_fallbackOverrides.OnTargetConnected(connectedTarget, xamlRoot);
	}

	void MicaBackdropWithFallback::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		if (isMicaSupported())
			base_type::OnTargetDisconnected(connectedTarget);
		else
			m_fallbackOverrides.OnTargetDisconnected(connectedTarget);
	}

	void MicaBackdropWithFallback::OnDefaultSystemBackdropConfigurationChanged(
		winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
		winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
	)
	{
		if (isMicaSupported())
			base_type::OnDefaultSystemBackdropConfigurationChanged(connectedTarget, xamlRoot);
		else
			m_fallbackOverrides.OnDefaultSystemBackdropConfigurationChanged(connectedTarget, xamlRoot);
	}

	bool MicaBackdropWithFallback::isMicaSupported()
	{
		static auto value = winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController::IsSupported();
		return value;
	}
}
