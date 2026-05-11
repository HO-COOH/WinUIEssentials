#pragma once
#include <atomic>
#include <mutex>
#include <utility>

template<typename T>
class SharedDataBase
{
    mutable std::mutex m_mutex;
    std::atomic_bool m_changed{ true };
    T& m_data_ref;
    void changed(bool value) noexcept
    {
        m_changed.store(value, std::memory_order_release);
    }
public:
    explicit SharedDataBase(T& data_ref) : m_data_ref{ data_ref } {}

    SharedDataBase(SharedDataBase const&) = delete;
    SharedDataBase& operator=(SharedDataBase const&) = delete;

    [[nodiscard]] bool ConsumeChanged() noexcept
    {
        return m_changed.exchange(false, std::memory_order_acquire);
    }

    template<typename F>
    void Update(F&& updaterCallable)
    {
        std::lock_guard lock{ m_mutex };
        updaterCallable(m_data_ref);
        changed(true);
    }

    [[nodiscard]] T GetCopy() const
    {
        std::lock_guard lock{ m_mutex };
        return m_data_ref;
    }
};
