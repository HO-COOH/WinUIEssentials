#pragma once

#include "ControlExampleSubstitution.g.h"
#include <functional>

namespace winrt::WinUI3Example::implementation
{
    struct ControlExampleSubstitution : ControlExampleSubstitutionT<ControlExampleSubstitution>
    {
        ControlExampleSubstitution() = default;
        
		winrt::hstring Key();
		void Key(winrt::hstring const& value);

		winrt::hstring Value();
		void Value(winrt::hstring const& value);

		bool IsEnabled();
		void IsEnabled(bool value);

		std::function<void(void)> ValueChanged;
    private:
		winrt::hstring m_key;
		winrt::hstring m_value;
		bool m_isEnabled = true;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ControlExampleSubstitution : ControlExampleSubstitutionT<ControlExampleSubstitution, implementation::ControlExampleSubstitution>
    {
    };
}
