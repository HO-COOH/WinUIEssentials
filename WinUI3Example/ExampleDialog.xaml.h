#pragma once

#include "ExampleDialog.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ExampleDialog : ExampleDialogT<ExampleDialog>
    {
        ExampleDialog()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ExampleDialog : ExampleDialogT<ExampleDialog, implementation::ExampleDialog>
    {
    };
}
