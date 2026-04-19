#pragma once

#include "SampleWindowedContentDialog.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SampleWindowedContentDialog : SampleWindowedContentDialogT<SampleWindowedContentDialog>
    {
        SampleWindowedContentDialog() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SampleWindowedContentDialog : SampleWindowedContentDialogT<SampleWindowedContentDialog, implementation::SampleWindowedContentDialog>
    {
    };
}
