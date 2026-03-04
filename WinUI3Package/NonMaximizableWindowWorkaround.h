#pragma once

#include "NonMaximizableWindowWorkaround.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct NonMaximizableWindowWorkaround : NonMaximizableWindowWorkaroundT<NonMaximizableWindowWorkaround>
    {
        NonMaximizableWindowWorkaround() = default;
        ~NonMaximizableWindowWorkaround();

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& value);

        bool IsMaximizable();
        void IsMaximizable(bool value);

    private:
        winrt::weak_ref<winrt::Microsoft::UI::Xaml::Window> m_window{ nullptr };
        std::optional<bool> m_isMaximizable;
		HWND m_hwnd{};

        bool m_registered{};

        constexpr static UINT SubClassId = 102;
        void setSubClassIfNeeded();
        static LRESULT CALLBACK subclassProc(
            HWND hwnd,
            UINT msg,
            WPARAM wparam,
            LPARAM lparam,
            UINT_PTR uIdSubclass,
            DWORD_PTR dwRefData
        );

        void set();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct NonMaximizableWindowWorkaround : NonMaximizableWindowWorkaroundT<NonMaximizableWindowWorkaround, implementation::NonMaximizableWindowWorkaround>
    {
    };
}
