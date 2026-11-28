#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include <resvg.h>

namespace resvg
{
	class RenderTree
	{
		struct TreeDeleter
		{
			void operator()(resvg_render_tree* tree) const noexcept
			{
				resvg_tree_destroy(tree);
			}
		};

		std::unique_ptr<resvg_render_tree, TreeDeleter> m_tree;
	public:
		[[nodiscard]] bool Parse(char const* data, uintptr_t length, resvg_options const* options) noexcept;
		[[nodiscard]] std::vector<uint8_t> Render(float scale, uint32_t width, uint32_t height) const;
		[[nodiscard]] resvg_size GetSize() const noexcept;

		explicit operator bool() const noexcept
		{
			return static_cast<bool>(m_tree);
		}
	};
}
