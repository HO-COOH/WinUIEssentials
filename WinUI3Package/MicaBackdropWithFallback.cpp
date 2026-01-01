#include "pch.h"
#include "MicaBackdropWithFallback.h"
#if __has_include("MicaBackdropWithFallback.g.cpp")
#include "MicaBackdropWithFallback.g.cpp"
#endif


namespace winrt::WinUI3Package::implementation
{
	MicaBackdropWithFallback::MicaBackdropWithFallback(winrt::Microsoft::UI::Xaml::Media::SystemBackdrop const& fallback) : m_fallback{fallback}
	{
	}

	winrt::Microsoft::UI::Xaml::Media::SystemBackdrop MicaBackdropWithFallback::Fallback()
	{
		return m_fallback;
	}

	void MicaBackdropWithFallback::Fallback(winrt::Microsoft::UI::Xaml::Media::SystemBackdrop const& value)
	{
		m_fallback = value;
	}

	void MicaBackdropWithFallback::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		if (m_isMicaSupported)
			base_type::OnTargetConnected(connectedTarget, xamlRoot);
		else
			m_fallback.OnTargetConnected(connectedTarget, xamlRoot);
	}

	void MicaBackdropWithFallback::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		if (m_isMicaSupported)
			base_type::OnTargetDisconnected(connectedTarget);
		else
			m_fallback.OnTargetDisconnected(connectedTarget);
	}

	void MicaBackdropWithFallback::OnDefaultSystemBackdropConfigurationChanged(
		winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
		winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
	)
	{
		if (m_isMicaSupported)
			base_type::OnDefaultSystemBackdropConfigurationChanged(connectedTarget, xamlRoot);
		else
			m_fallback.OnDefaultSystemBackdropConfigurationChanged(connectedTarget, xamlRoot);
	}
}
