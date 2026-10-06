#pragma once

#include "MediaPlayerElementWorkaroundPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MediaPlayerElementWorkaroundPage : MediaPlayerElementWorkaroundPageT<MediaPlayerElementWorkaroundPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MediaPlayerElementWorkaroundPage : MediaPlayerElementWorkaroundPageT<MediaPlayerElementWorkaroundPage, implementation::MediaPlayerElementWorkaroundPage>
    {
    };
}
