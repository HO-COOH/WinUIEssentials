#pragma once

#include "ModalWindow.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct ModalWindow : ModalWindowT<ModalWindow>
	{
		ModalWindow() = default;
		ModalWindow(winrt::Microsoft::UI::Xaml::Window const& parent);

	private:
		void OnClosed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args);

		winrt::Microsoft::UI::Xaml::Window m_owner{ nullptr };
		winrt::Microsoft::UI::Xaml::Window::Closed_revoker m_closedRevoker{};
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
	struct ModalWindow : ModalWindowT<ModalWindow, implementation::ModalWindow>
	{
	};
}
