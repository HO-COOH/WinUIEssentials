#pragma once

#include "LocalizedContentDialog.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct LocalizedContentDialog : LocalizedContentDialogT<LocalizedContentDialog>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct LocalizedContentDialog : LocalizedContentDialogT<LocalizedContentDialog, implementation::LocalizedContentDialog>
    {
    };
}
