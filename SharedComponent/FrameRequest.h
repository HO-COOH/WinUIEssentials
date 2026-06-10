#pragma once
#include <atomic>
#include <cstdint>

class FrameRequest
{
	std::atomic<uint32_t> m_state;
public:
	enum class Flag : uint32_t
	{
		None            = 0,
		Draw            = 1u << 0,
		FullRedraw      = 1u << 1,
		HeaderDirty     = 1u << 2, //need renderHeaderBitmap(), Y-scroll does not redraw header
		SwapChainDirty  = 1u << 3, //Back buffers were resized
		Stop            = 1u << 4,
		HoverColorDirty = 1u << 5,
		VerticalLineColorDirty = 1u << 6, //vertical-line cached bitmap must be re-rendered (color or thickness changed)
		//scroll can't be used here because it persists after one draw call, so it has to be a separate flag
	};
	using Flags = uint32_t;

	explicit FrameRequest(Flags initial = 0) noexcept : m_state{ initial } 
	{
	}

	FrameRequest(FrameRequest const&) = delete;
	FrameRequest& operator=(FrameRequest const&) = delete;

	void Set(Flags bits) noexcept
	{
		m_state.fetch_or(bits, std::memory_order_release);
	}
	
	void Set(Flag bit) noexcept 
	{
		Set(static_cast<Flags>(bit)); 
	}

	Flags ClearAll() noexcept
	{
		return m_state.exchange(0, std::memory_order_acq_rel);
	}

	Flags Load(std::memory_order order = std::memory_order_acquire) const noexcept
	{
		return m_state.load(order);
	}

	void WaitForDraw() noexcept
	{
		m_state.wait(0, std::memory_order_acquire);
	}

	void WakeOne() noexcept 
	{ 
		m_state.notify_one(); 
	}
};

//Bitwise operators on Flag that produce a Flags value, so call sites can use | flag and flags in any order
constexpr FrameRequest::Flags operator|(FrameRequest::Flag a, FrameRequest::Flag b) noexcept
{
	return static_cast<FrameRequest::Flags>(a) | static_cast<FrameRequest::Flags>(b);
}
constexpr FrameRequest::Flags operator|(FrameRequest::Flags a, FrameRequest::Flag b) noexcept
{
	return a | static_cast<FrameRequest::Flags>(b);
}
constexpr FrameRequest::Flags operator|(FrameRequest::Flag a, FrameRequest::Flags b) noexcept
{
	return static_cast<FrameRequest::Flags>(a) | b;
}
constexpr FrameRequest::Flags& operator|=(FrameRequest::Flags& a, FrameRequest::Flag b) noexcept
{
	return a = a | static_cast<FrameRequest::Flags>(b);
}
constexpr FrameRequest::Flags operator&(FrameRequest::Flags a, FrameRequest::Flag b) noexcept
{
	return a & static_cast<FrameRequest::Flags>(b);
}
