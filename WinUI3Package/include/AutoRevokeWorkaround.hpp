#pragma once
#include <winrt/base.h>

/*
* @brief This is a workaround "auto_revoker" for types that don't support IWeakReferenceSource
* @see https://github.com/microsoft/microsoft-ui-xaml/issues/10849
* @see https://github.com/microsoft/microsoft-ui-xaml/issues/10937
* @tparam RevokeFunc Should be a function that accepts a event_token to unregister an event handler
*/
template<typename RevokeFunc>
class AutoRevokeWorkaround
{
    winrt::event_token m_token;
    RevokeFunc m_revokeFunc;

    // Helper to revoke if valid
    void revoke() noexcept
    {
        if (m_token)
        {
            m_revokeFunc(m_token);
            m_token = {};
        }
    }

public:
    constexpr AutoRevokeWorkaround(RevokeFunc&& revoker, winrt::event_token token = {})
        : m_token{ token }
        , m_revokeFunc{ std::forward<RevokeFunc>(revoker) }
    {
    }

    ~AutoRevokeWorkaround()
    {
        revoke();
    }

    //Delete copy
    AutoRevokeWorkaround(const AutoRevokeWorkaround&) = delete;
    AutoRevokeWorkaround& operator=(const AutoRevokeWorkaround&) = delete;

    AutoRevokeWorkaround(AutoRevokeWorkaround&& other) noexcept
        : m_token{ std::exchange(other.m_token, {}) }
        , m_revokeFunc{ std::move(other.m_revokeFunc) }
    {
    }

    AutoRevokeWorkaround& operator=(AutoRevokeWorkaround&& other) noexcept
    {
        if (this != &other)
        {
            // 1. Clean up current resource
            revoke();

            // 2. Steal resources from other
            m_token = std::exchange(other.m_token, {});
            m_revokeFunc = std::move(other.m_revokeFunc);
        }
        return *this;
    }

    AutoRevokeWorkaround& operator=(winrt::event_token token)
    {
        revoke();
        m_token = token;
        return *this;
    }
};
