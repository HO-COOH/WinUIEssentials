#pragma once

#include "DefaultWindowBrokenCaptionButton.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultWindowBrokenCaptionButton : DefaultWindowBrokenCaptionButtonT<DefaultWindowBrokenCaptionButton>
    {
        DefaultWindowBrokenCaptionButton();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DefaultWindowBrokenCaptionButton : DefaultWindowBrokenCaptionButtonT<DefaultWindowBrokenCaptionButton, implementation::DefaultWindowBrokenCaptionButton>
    {
    };
}
