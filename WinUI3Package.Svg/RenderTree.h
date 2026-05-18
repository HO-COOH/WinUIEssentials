#pragma once
#include <resvg.h>

namespace resvg
{
	class RenderTree
	{
		resvg_render_tree* m_tree{};
	public:
		constexpr RenderTree() = default;

		RenderTree(RenderTree const&) = delete;
		RenderTree(RenderTree&&) = delete;
		RenderTree& operator=(RenderTree const&) = delete;
		RenderTree& operator=(RenderTree&&) = delete;

		[[nodiscard]] bool Parse(char const* data, uintptr_t length, resvg_options const* options) noexcept;
		[[nodiscard]] std::vector<uint8_t> Render(float scale, uint32_t width, uint32_t height);
		[[nodiscard]] resvg_size GetSize() const noexcept;

		constexpr operator bool() const noexcept
		{
			return static_cast<bool>(m_tree);
		}

		~RenderTree();
	};

}