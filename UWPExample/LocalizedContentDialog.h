#pragma once

#include "LocalizedContentDialog.g.h"

namespace winrt::UWPExample::implementation
{
    struct LocalizedContentDialog : LocalizedContentDialogT<LocalizedContentDialog>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct LocalizedContentDialog : LocalizedContentDialogT<LocalizedContentDialog, implementation::LocalizedContentDialog>
    {
    };
}
