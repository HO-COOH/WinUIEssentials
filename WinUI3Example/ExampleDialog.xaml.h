#pragma once

#include "ExampleDialog.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ExampleDialog : ExampleDialogT<ExampleDialog>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ExampleDialog : ExampleDialogT<ExampleDialog, implementation::ExampleDialog>
    {
    };
}
