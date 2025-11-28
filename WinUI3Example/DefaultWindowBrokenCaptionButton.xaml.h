#pragma once

#include "DefaultWindowBrokenCaptionButton.g.h"
#include "SupportThemeToggle.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultWindowBrokenCaptionButton : DefaultWindowBrokenCaptionButtonT<DefaultWindowBrokenCaptionButton>, public SupportThemeToggle<DefaultWindowBrokenCaptionButton>
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
