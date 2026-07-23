#pragma once

#include "DefaultWindowBrokenCaptionButton.g.h"

namespace winrt::UWPExample::implementation
{
    struct DefaultWindowBrokenCaptionButton : DefaultWindowBrokenCaptionButtonT<DefaultWindowBrokenCaptionButton>
    {
        DefaultWindowBrokenCaptionButton();
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct DefaultWindowBrokenCaptionButton : DefaultWindowBrokenCaptionButtonT<DefaultWindowBrokenCaptionButton, implementation::DefaultWindowBrokenCaptionButton>
    {
    };
}
