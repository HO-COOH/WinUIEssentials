#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "MonacoEditor.g.h"

namespace winrt::UWPExample::implementation
{
    struct MonacoEditor : MonacoEditorT<MonacoEditor>
    {
        MonacoEditor()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        winrt::hstring XamlCode() { return {}; }
        void XamlCode(winrt::hstring const& value) {}

        winrt::hstring HeaderCode() { return {}; }
		void HeaderCode(winrt::hstring const& value) {}

		winrt::hstring CppCode() { return {}; }
		void CppCode(winrt::hstring const& value) {}
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct MonacoEditor : MonacoEditorT<MonacoEditor, implementation::MonacoEditor>
    {
    };
}
